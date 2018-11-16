from api.models import Payroll


class Payrolls(object):
    def __init__(self, cursor):
        """
        :param cursor: MySQLdb.cursor.Cursor
        """
        self.cursor = cursor
        cursor.execute('SET NAMES utf8;')
        cursor.execute('SET CHARACTER SET utf8;')
        cursor.execute('SET character_set_connection=utf8;')

    @staticmethod
    def _map_payroll(payroll_db_data):
        return Payroll(*payroll_db_data)

    def readall(self):
        self.cursor.execute(
            """
            SELECT
            Id, EmployeeId, PaymentId, ProjectId, PayrollDate
            FROM
            payrolls
            """
        )
        payrolls = self.cursor.fetchall()
        mapped = map(self._map_payroll, payrolls)
        return list(mapped)

    def add(self, payroll):
        params = (
            payroll.employee_id,
            payroll.payment_id,
            payroll.project_id,
            payroll.payroll_date,
        )
        self.cursor.execute(
            """
            INSERT 
            INTO payrolls
            (EmployeeId, PaymentId, ProjectId, PayrollDate)
            VALUES 
            (%s, %s, %s, %s)
            """,
            params
        )

    def remove(self, payroll_id):
        self.cursor.execute(
            """
            DELETE
            FROM payrolls
            WHERE Id=%s
            """,
            [payroll_id]
        )

    def update(self, payroll, payroll_id):
        params = (
            payroll.employee_id,
            payroll.payment_id,
            payroll.project_id,
            payroll.payroll_date,
            payroll_id
        )
        self.cursor.execute(
            """
            UPDATE
            payrolls
            SET 
            EmployeeId=%s,
            PaymentId=%s,
            ProjectId=%s,
            PayrollDate=%s
            WHERE
            payrolls.Id=%s
            """,
            params
        )
