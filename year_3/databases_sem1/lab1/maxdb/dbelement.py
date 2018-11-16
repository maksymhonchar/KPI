"""
Database element and Database foreign key element classes.

Both DBElement and DBFKElement are json-serializable.

DBElement and DBFKelement are objects with certain value and its type.
Note, that type field is a string.
Note, that type field has to match a column type in DBTable.

DBFKElement has type and value of element to which we refer.
Deleting referred element wont affect DBFKElement value.
Columns with foreign keys have to be 'fk'
"""

class DeletedFKException(Exception):
    pass


class DBElement(object):
    def __init__(self, el_value, el_column_type, el_type, **kw):
        if el_column_type != el_type:
            raise ValueError('Column and element types mismatch.')
        self.value = el_value
        self.type = el_type

    def __repr__(self):
        return 'DBElement<value={0}, type={1}>'.format(
            self.value, self.type
        )

    def __eq__(self, other):
        return (self.value == other.value) and (self.type == other.type)

    def __dict__(self):
        return {
            'value': self.value,
            'type': self.type,
        }

    def __getitem__(self, item):
        if item is 'value':  # todo: too silly.
            return self.value
        elif item is 'type':
            return self.type
        raise KeyError('DBElement does not have item {0}'.format(item))


class DBFKElement(DBElement):
    """
    Note, that in storage files DBFKElement will be displayed as Table.Idx element,
        but in memory it has it is a DBRow without index - dict of DBElements, ie:
        {col1:val1, ... }

    Note, that columns with foreign keys have to be type of 'fk'.
    """
    def __init__(self, dbraw, dbtable, tcoltype, fkid):
        self._rawdb = dbraw
        self.table = dbtable
        self.fk_id = fkid
        fkrow = self._find_fk_value()
        if fkrow is None:  # FK was deleted.
            raise DeletedFKException
        fk_const_coltype = "fk"
        super(DBFKElement, self).__init__(fkrow, tcoltype, fk_const_coltype)

    def _find_fk_value(self):
        try:
            table = self._rawdb[self.table]
            fkrow = table.get('rows', {}).get(self.fk_id, None)
        except KeyError:
            raise RuntimeError("Cannot add DB FK row {0}.{1}".format(self.table, self.fk_id))
        return fkrow

    def __eq__(self, other):
        return (self.table == other.table) and (self.fk_id == other.fk_id)

    def __repr__(self):
        return 'DBFKElement<{0}.{1} value={2}, type={3}>'.format(
            self.table, self.fk_id, self.value, self.type
        )

    def __getitem__(self, item):
        if item is 'value':  # todo: too silly.
            return self.value
        elif item is 'type':
            return self.type
        elif item is 'table':
            return self.table
        elif item is 'fkid':
            return self.fk_id
        elif item is 'type':
            return "fk"  # column_type
        raise KeyError('DBFKElement does not have item {0}'.format(item))
