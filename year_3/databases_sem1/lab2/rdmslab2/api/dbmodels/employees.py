from api.models import Employee


class Employees(object):
    def __init__(self, cursor):
        """
        :param cursor: MySQLdb.cursor.Cursor
        """
        self.cursor = cursor
        cursor.execute('SET NAMES utf8;')
        cursor.execute('SET CHARACTER SET utf8;')
        cursor.execute('SET character_set_connection=utf8;')

    @staticmethod
    def _map_employee(employee_db_data):
        return Employee(*employee_db_data)

    def readall(self):
        self.cursor.execute(
            """
            SELECT
            Id, FullName, Characteristics, IsIntern
            FROM
            employees
            """
        )
        employees = self.cursor.fetchall()
        mapped = map(self._map_employee, employees)
        return list(mapped)

    def add(self, employee):
        params = (
            employee.full_name,
            employee.characteristics,
            employee.is_intern
        )
        self.cursor.execute(
            """
            INSERT 
            INTO employees
            (FullName, Characteristics, IsIntern)
            VALUES 
            (%s, %s, %s)
            """,
            params
        )

    def remove(self, employee_id):
        self.cursor.execute(
            """
            DELETE
            FROM employees
            WHERE Id=%s
            """,
            [employee_id]
        )

    def update(self, employee, employee_id):
        params = (
            employee.full_name,
            employee.characteristics,
            employee.is_intern,
            employee_id
        )
        self.cursor.execute(
            """
            UPDATE
            employees
            SET 
            FullName=%s,
            Characteristics=%s,
            IsIntern=%s
            WHERE
            employees.Id=%s
            """,
            params
        )

    def search(self, characteristics_args, fullname_args, isintern_args):
        """
        Search by:
        1. characteristics: MATCH AGAINST IN BOOLEAN MODE. Note, that only + is allowed.
        2. fullname: LIKE
        3. isintern: simple search

        Input params are lists with values to search for.
        """
        if characteristics_args:
            characteristics_args = characteristics_args.split(' ')
            against_words_str = ''
            for word in characteristics_args:
                against_words_str += '+%s ' % word
            against_words_str = against_words_str.rstrip(' ')
            against_words_str = "'%s'" % against_words_str
            self.cursor.execute(
                """
                SELECT 
                Id, FullName, Characteristics, IsIntern
                FROM
                employees
                WHERE
                match(Characteristics)
                AGAINST (%s IN BOOLEAN MODE) 
                """,
                [against_words_str]
            )
        elif fullname_args:
            self.cursor.execute(
                """
                SELECT
                Id, FullName, Characteristics, IsIntern
                FROM 
                employees
                WHERE
                FullName LIKE %s
                """,
                ['%%%s%%' % fullname_args]
            )
        elif isintern_args:
            self.cursor.execute(
                """
                SELECT
                Id, FullName, Characteristics, IsIntern
                FROM
                employees
                WHERE
                IsIntern=%s
                """,
                isintern_args
            )
        else:
            raise RuntimeError('search error exception: incorrect arguments')
        employees = self.cursor.fetchall()
        mapped = map(self._map_employee, employees)
        return list(mapped)

    def importall(self, employees):
        self.cursor.execute(
            """
            DELETE
            FROM employees
            """
        )
        for employee in employees:
            self.add(employee)
