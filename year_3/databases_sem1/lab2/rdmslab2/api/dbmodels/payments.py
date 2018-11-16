from api.models import Payment


class Payments(object):
    def __init__(self, cursor):
        """
        :param cursor: MySQLdb.cursor.Cursor
        """
        self.cursor = cursor
        cursor.execute('SET NAMES utf8;')
        cursor.execute('SET CHARACTER SET utf8;')
        cursor.execute('SET character_set_connection=utf8;')

    @staticmethod
    def _map_payment(payment_db_data):
        return Payment(*payment_db_data)

    def readall(self):
        self.cursor.execute(
            """
            SELECT
            Id, Method, RawSalary, TaxRate
            FROM
            payments
            """
        )
        payments = self.cursor.fetchall()
        mapped = map(self._map_payment, payments)
        return list(mapped)

    def add(self, payment):
        params = (
            payment.method,
            payment.raw_salary,
            payment.tax_rate
        )
        self.cursor.execute(
            """
            INSERT 
            INTO payments
            (Method, RawSalary, TaxRate)
            VALUES 
            (%s, %s, %s)
            """,
            params
        )

    def remove(self, payment_id):
        self.cursor.execute(
            """
            DELETE
            FROM payments
            WHERE Id=%s
            """,
            [payment_id]
        )

    def update(self, payment, payment_id):
        params = (
            payment.method,
            payment.raw_salary,
            payment.tax_rate,
            payment_id
        )
        self.cursor.execute(
            """
            UPDATE
            payments
            SET 
            Method=%s,
            RawSalary=%s,
            TaxRate=%s
            WHERE
            payments.Id=%s
            """,
            params
        )

    def search(self, salarymax, salarymin):
        """
        Search for salary in between of max and min args
        """
        if salarymax is None or salarymin is None:
            raise RuntimeError('Error in DBPayments.search: missing max or min argument')

        salarymin = float(salarymin)
        salarymax = float(salarymax)

        if salarymin > salarymax:
            raise RuntimeError('Error in DBPayments.search: min > max, {0}>{1}'.format(salarymin, salarymax))
        self.cursor.execute(
            """
            SELECT
            Id, Method, RawSalary, TaxRate
            FROM
            payments
            WHERE
            RawSalary
            BETWEEN %s AND %s
            """,
            (salarymin, salarymax)
        )
        payments = self.cursor.fetchall()
        mapped = map(self._map_payment, payments)
        return list(mapped)

    def importall(self, payments):
        self.cursor.execute(
            """
            DELETE
            FROM payments
            """
        )
        for payment in payments:
            self.add(payment)
