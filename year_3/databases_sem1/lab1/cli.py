from maxdb import DB


def runtime_on_any_exception(func):
    def decorate(*args, **kwargs):
        try:
            func(*args, **kwargs)
        except:
            raise RuntimeError
    return decorate


class CLIUtils(object):
    DEFAULT_PATH = 'storage.json'

    def __init__(self):
        self._db = None
        self._path = self.DEFAULT_PATH

    def run(self, rawcmd):
        cmd, *args = rawcmd.split(' ')
        if cmd:
            try:
                self._cmds_cache[cmd](args)
            except KeyError:
                print('Lab1 does not have command <{0}>'.format(cmd))
            except RuntimeError:
                print('Incorrect arguments for DB.{0}: <{1}>'.format(cmd, args))

    @property
    def _cmds_cache(self):
        return {
            'tables': self._tables,
            'all': self._all,
            'insert': self._insert,
            'get': self._get,
            'update': self._update,
            'delete': self._delete,
            'help': lambda _: print(self._help_msg),
            'path': lambda _: print(self._path),
            'exit': self._close,
        }

    @property
    def _help_msg(self):
        return """LAB1 HELP: 
        | tables
        |       print list of tables from current storage.
        | all <table> (<table> ...)
        |       display _all values from specific table.
        | all labcondition
        |       display _all products with price more than 100UAH. 
        | insert <table> <cnt>
        |       insert N items to the table. 
        |       is followed by >>>column_name <value>
        | get <table> <id>
        |       get single row specified by id from table. 
        | update <table> <id> 
        |       udpate table with a new single value. 
        |       is followed by 
        |           >>>with <column> <value> (<column> <value> (...))
        | delete <table> <id>
        |       delete row specified by id from table.
        | save <filepath>
        |       save database using current storage type to specified filepath.
        | load <filepath>
        |       load specific database from file using current storage type.
        | help
        |       display current message.
        | path
        |       display storage file path. 
        | exit
        |       exit the program.
        """

    def _tables(self, _):
        print(self._db.tables())

    @runtime_on_any_exception
    def _all(self, args):
        if 'labcondition' == args[0]:
            found_rows = self._db.get(
                'Products',
                column='price',
                cond=lambda p: int(p.value) > 100
            )
            print('Rows from DB.Products with price>100:')
            print('\n'.join(map(str, found_rows)))
        else:
            for table_name in args:
                table_rows = self._db.table(table_name).all_ids()
                table_pretty_rows = '\n'.join(map(lambda i: 'ID {0} {1}'.format(*i), table_rows))
                print('DB.{0}:\n{1}'.format(table_name, table_pretty_rows))

    @runtime_on_any_exception
    def _insert(self, args):
        table_name, cnt = args
        table_to_insert = self._db.table(table_name)
        for cur_cnt in range(int(cnt)):
            print('Please, enter values for DB.{0} row:'.format(table_name))
            row_to_insert = {}
            for column_name, column_type in table_to_insert.columns.items():
                if column_type == 'fk':
                    print('Enter Table for FK: fktable=', end='')
                    fktable = input()
                    print('Enter Id for FK: fkid=', end='')
                    fkid = input()
                    row_to_insert[column_name] = (
                        {'table': fktable, 'fkid': fkid},
                        column_type
                    )
                else:
                    print('Enter {0}, type={1}: {0}='.format(column_name, column_type), end='')
                    column_value = input()
                    row_to_insert[column_name] = (column_value, column_type)
            table_to_insert.insert(row_to_insert)

    @runtime_on_any_exception
    def _get(self, args):
        table_name, row_idx = args
        print('DB.{0} id={1}:'.format(*args))
        print(self._db.get(table_name, doc_id=int(row_idx)) or 'Not Found DB.{0}.{1}'.format(*args))

    @runtime_on_any_exception
    def _update(self, args):
        table_name, row_idx = args
        table_to_update = self._db.table(table_name)
        row_to_update = table_to_update.get(row_id=int(row_idx))
        colval_to_update = {}
        print('Updating DB.{0}.{1}: {2}'.format(table_name, row_idx, row_to_update))
        for column_name, column_type in table_to_update.columns.items():
            if column_type == 'fk':
                current_fktable = row_to_update[column_name].table
                print('Change FKTable from <{0}> to value='.format(current_fktable), end='')
                after_fktable = input()
                current_fkid = row_to_update[column_name].fk_id
                print('Change FKId from <{0}> to value='.format(current_fkid), end='')
                after_fkid = input()
                colval_to_update[column_name] = {
                    'table': after_fktable,
                    'fkid': after_fkid
                }
            else:
                print('Enter value for column {0}, type={1}: {0}='.format(column_name, column_type), end='')
                column_value = input()
                colval_to_update[column_name] = column_value
        table_to_update.update(colval_to_update, [int(row_idx)])

    @runtime_on_any_exception
    def _delete(self, args):
        table_name, row_id = args
        print('Deleted item DB.{0}.{1}'.format(*args))
        print(self._db.delete(table_name, row_ids=[int(row_id)]) or 'Not Found DB.{0}.{1}'.format(*args))

    def _open(self):
        """Create DB instance and preload default models."""
        self._db = DB(self._path)
        products = self._db.table(
            'Products',
            columns={'name': 'str', 'price': 'int'}
        )
        orders = self._db.table(
            'Orders',
            columns={'product': 'fk', 'client': 'str', 'destination': 'addr'}
        )
        try:
            products.insert_multiple([
                {"name": ("product1", "str"), "price": ("50", "int")},
                {"name": ("product2", "str"), "price": ("100", "int")},
                {"name": ("product3", "str"), "price": ("200", "int")},
            ])
        except:
            pass
        try:
            orders.insert_multiple([
                {
                    "product": ({'table': 'Products', 'fkid': '1'}, 'fk'),
                    "client": ("honchar", "str"), "destination": ("Kyiv", "addr")
                },
                {
                    "product": ({'table': 'Products', 'fkid': '2'}, 'fk'),
                    "client": ("honchar2", "str"), "destination": ("Kyiv2", "addr")
                },
                {
                    "product": ({'table': 'Products', 'fkid': '3'}, 'fk'),
                    "client": ("honchar3", "str"), "destination": ("Kyiv3", "addr")
                },
            ])
        except:
            pass
        self.run('help', *())

    def _close(self, _):
        """Close DB instance routine."""
        self._db.close()

    def __enter__(self):
        self._open()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self._close(None)
