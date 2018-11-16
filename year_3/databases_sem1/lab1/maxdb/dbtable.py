from .utils import LRUCache
from .dbelement import DBElement, DBFKElement, DeletedFKException


class Table(object):
    def __init__(self, storage, name, columns, cache_size=10):
        """
        :param storage: StorageProxy
        :param name: Str
        :param columns: Dict of {name: type} as {str: int}
        :param cache_size: Int type
        """
        self._storage = storage
        self._query_cache = LRUCache(capacity=cache_size)
        self._name = name  # could be updated in _read()
        self._columns = columns  # could be updated in _read()
        self._metadata = {  # could be updated in _read()
            'name': self._name,
            'columns': self._columns,
            'query_cache_max_cnt': cache_size,
        }

        data = self._read()
        if data:
            self._last_id = max(i for i in data)
        else:
            self._last_id = 0

    @property
    def name(self):
        return self._name

    @property
    def columns(self):
        return self._metadata.get('columns', [])

    def get(self, row_id=None, column=None, cond=None):
        # Element specified by id or column.
        if row_id is not None:
            return self._read().get(row_id, None)
        # Element specified by condition.
        to_return_by_condition = []
        for table_row in self._read().values():
            for key, element in table_row.items():
                if key == column:
                    if cond(element):
                        to_return_by_condition.append(element)
        return to_return_by_condition

    def insert(self, raw_elements):
        """{col_name: DB(?FK)Element(value, type)}"""
        if len(raw_elements) != len(self._columns):
            raise ValueError('Not enough raw_elements to insert into {0}'.format(self.name))
        data = self._read()
        row = {}
        for col_name, element in raw_elements.items():
            el_value, el_type = element
            col_type = self._columns[col_name]
            if isinstance(el_value, dict) and el_type == 'fk':
                try:
                    fkid = str(el_value['fkid'])
                    fktable = el_value['table']
                    row_element = DBFKElement(data.raw_db, fktable, col_type, fkid)
                except KeyError:
                    raise ValueError('Cannot insert ForeignKey - incorrect format')
            else:
                row_element = DBElement(el_value, col_type, el_type)
            row.update({col_name: row_element})
        # Check for duplicates.
        for table_row in data.values():
            for table_column in self._columns:
                if table_row[table_column] == row[table_column]:
                    raise ValueError('Found duplicate: {0} in {1}'.format(row, self.name))

        row_id = self._get_next_id()
        data[row_id] = row
        self._write(data, data.raw_db)
        return row_id

    def insert_multiple(self, elements):
        row_ids = []
        for element in elements:
            inserted_id = self.insert(element)
            row_ids.append(inserted_id)
        return row_ids

    def delete(self, cond=None, row_ids=None):
        if cond is None and row_ids is None:
            raise ValueError('Missing condition or row id to remove')
        removed_rows = []
        data = self._read()
        if row_ids:
            for row_id in row_ids:
                row_to_remove = data.pop(row_id)
                removed_rows.append(row_to_remove)
            self._write(data, data.raw_db)
        elif cond:
            for row_id in row_ids:
                if cond(row_ids[row_id]):
                    deleted_item = data.pop(row_id)
                    removed_rows.append(deleted_item)
        return removed_rows

    def update(self, to_update, row_ids):
        data = self._read()
        for row_id in row_ids:
            for column_name in to_update.keys():
                if isinstance(to_update[column_name], dict) and 'fkid' in to_update[column_name].keys():
                    fk_to_update = to_update[column_name]
                    data[row_id][column_name] = DBFKElement(
                        data.raw_db, fk_to_update['table'], "fk", fk_to_update['fkid']
                    )
                else:
                    data[row_id][column_name].value = to_update[column_name]
        self._write(data, data.raw_db)

    def search(self, cond):
        if cond in self._query_cache:
            return self._query_cache[cond][:]
        rows = [row for row in self.all() if cond(row)]
        self._query_cache[cond] = rows
        return rows[:]

    def count(self, cond):
        return len(self.search(cond))

    def contains(self, cond=None, row_ids=None):
        if row_ids is not None:  # Rows specified by id.
            return any(self.get(row_id=row_id) for row_id in row_ids)
        if cond is not None:  # Rows specified by condition
            return self.get(cond) is not None
        raise ValueError('Trying to use contains without specifying condition or row_ids')

    def all(self):
        return list(self._read().values())

    def all_ids(self):
        return list(self._read().items())

    def purge(self):
        raw_db = self._read().raw_db
        self._write({
            'rows': {},
            'metadata': self._metadata
        }, raw_db)
        self._last_id = 0

    def clear_cache(self):
        self._query_cache.clear()

    def add_column(self, column, col_type):
        if column in self._columns:
            raise ValueError('{0} column already in {1} table'.format(column, self.name))
        self._columns.update({column: col_type})
        raw_data = self._read()
        for row in raw_data:
            raw_data[row][column] = DBElement('META:{0}.NoValue'.format(column), col_type, col_type)
        self._write(raw_data, raw_data.raw_db)
        self.clear_cache()

    def remove_column(self, column):
        if column not in self._columns:
            raise ValueError('No {0} column in {1} table'.format(column, self.name))
        deleted_column = {column: self._columns.pop(column)}
        raw_data = self._read()
        for row in raw_data:
            del raw_data[row][deleted_column]
        self._write(raw_data, raw_data.raw_db)
        self.clear_cache()
        return deleted_column

    def _create_columns(self, columns_names):
        for column_name, column_type in columns_names.items():
            self._columns.update({column_name: column_type})

    def _get_column_type(self, column):
        return self._columns.get(column, None)

    def _get_next_id(self):
        current_id = self._last_id + 1
        self._last_id = current_id
        return current_id

    def _read(self):
        content = self._storage.read()
        if not content.meta:  # not found table in the database, try to create a new one.
            self._write({
                'rows': {},
                'metadata': self._metadata
            }, content.raw_db)
            content = self._read()
        self._metadata = content.meta
        self._columns = self._metadata['columns']
        return content

    def _read_metadata(self):
        return self._storage.read().meta

    def _write(self, table, raw_db):
        self.clear_cache()
        self._storage.write(table, raw_db)

    def __len__(self):
        return len(self._read())

    def __iter__(self):
        for row in self._read().values():
            yield row


class DataProxy(dict):
    """proxy that remembers table data and data from whole storage"""

    def __init__(self, table_rows, table_meta, raw_db, **kw):
        super(DataProxy, self).__init__(**kw)
        self.update(table_rows)
        self.meta = table_meta
        self.raw_db = raw_db


class StorageProxy(object):
    """proxy that allows to read a single table from a storage"""

    def __init__(self, storage, table_name):
        self._storage = storage
        self._table_name = table_name

    def read(self):
        raw_data = self._storage.read() or {}
        try:
            table = raw_data[self._table_name]
        except KeyError:
            return DataProxy({}, {}, raw_data)

        table_meta = table['metadata']
        table_columns = table_meta['columns']

        rows = {}
        for idx, row in table['rows'].items():
            row_id = int(idx)
            row_items = {}
            try:
                for col_name, col_value in row.items():
                    col_type = table_columns[col_name]
                    if isinstance(col_value, dict):
                        fkmeta = col_value.get('fk', None)
                        if fkmeta:
                            fkid = str(fkmeta['fkid'])
                            fktable = str(fkmeta['table'])
                            element_to_add = DBFKElement(raw_data, fktable, col_type, fkid)
                        else:
                            el_type = col_value['type']
                            el_value = col_value['value']
                            element_to_add = DBElement(el_value, col_type, el_type)
                    else:
                        raise RuntimeError('Incorrect DBRow format')
                    row_items.update({col_name: element_to_add})
            except DeletedFKException:
                # why maxdb allows to leave garbage in local storage: tolerancy to other columns.
                print('Note, that FK DB.{0}.id{1} contained FKElement with missing referenec value'.format(
                    self._table_name, row_id
                ))
                continue
            rows[row_id] = row_items
        return DataProxy(rows, table_meta, raw_data)

    def write(self, data, raw_db):
        try:
            raw_db[self._table_name]['rows'] = data
        except KeyError:
            raw_db[self._table_name] = data
        self._storage.write(raw_db)

    def purge_table(self):
        try:
            data = self._storage.read() or {}
            del data[self._table_name]
            self._storage.write(data)
        except KeyError:
            pass
