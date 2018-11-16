"""
Main class for the MaxDB.
Gives access managing DB and his tables.
"""

from .storages import JSONStorage
from .dbtable import Table, StorageProxy


class DB(object):
    DEFAULT_STORAGE = JSONStorage

    def __init__(self, *args, **kwargs):
        storage = kwargs.pop('storage', self.DEFAULT_STORAGE)
        self._storage = storage(*args, **kwargs)
        self._opened = True
        self._table_cache = {}

    def table(self, name, **options):
        if name in self._table_cache:
            return self._table_cache[name]
        table_storage = StorageProxy(self._storage, name)
        table = Table(table_storage, name, **options)
        self._table_cache[name] = table
        return table

    def tables(self):
        return set(self._storage.read())

    def purge_tables(self):
        self._storage.write({})
        self._table_cache.clear()

    def purge_table(self, name):
        if name in self._table_cache:
            del self._table_cache[name]
        proxy = StorageProxy(self._storage, name)
        proxy.purge_table()

    def get(self, table_name, doc_id=None, column=None, cond=None):
        table_to_get = self.table(table_name)
        return table_to_get.get(doc_id, column, cond)

    def insert(self, table_name, elements):
        table_to_insert = self.table(table_name)
        new_elements = table_to_insert.insert_multiple(elements)
        return new_elements

    def delete(self, table_name, cond=None, row_ids=None):
        table_to_delete = self.table(table_name)
        deleted_row = table_to_delete.delete(cond, row_ids)
        return deleted_row

    def update(self, table_name, fields_to_update, row_ids):
        table_to_update = self.table(table_name)
        table_to_update.update(fields_to_update, row_ids)

    def close(self):
        self._opened = False
        self._storage.close()

    def __enter__(self):
        return self

    def __exit__(self, *args):
        if self._opened:
            self.close()
