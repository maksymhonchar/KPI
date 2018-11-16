from api.models import Project


class Projects(object):
    def __init__(self, cursor):
        """
        :param cursor: MySQLdb.cursor.Cursor
        """
        self.cursor = cursor
        cursor.execute('SET NAMES utf8;')
        cursor.execute('SET CHARACTER SET utf8;')
        cursor.execute('SET character_set_connection=utf8;')

    @staticmethod
    def _map_project(project_db_data):
        return Project(*project_db_data)

    def readall(self):
        self.cursor.execute(
            """
            SELECT
            Id, Name, Description
            FROM
            projects
            """
        )
        projects = self.cursor.fetchall()
        mapped = map(self._map_project, projects)
        return list(mapped)

    def add(self, project):
        params = (
            project.name,
            project.description
        )
        self.cursor.execute(
            """
            INSERT 
            INTO projects
            (Name, Description)
            VALUES 
            (%s, %s)
            """,
            params
        )

    def remove(self, project_id):
        self.cursor.execute(
            """
            DELETE
            FROM projects
            WHERE Id=%s
            """,
            [project_id]
        )

    def update(self, project, project_id):
        params = (
            project.name,
            project.description,
            project_id
        )
        self.cursor.execute(
            """
            UPDATE
            projects
            SET 
            Name=%s,
            Description=%s
            WHERE
            projects.Id=%s
            """,
            params
        )

    def search(self, description_like):
        """
        LIKE search in description column.
        """
        if description_like is None:
            raise RuntimeError('Error in DBProjects.search: missing description_like arg')
        self.cursor.execute(
            """
            SELECT
            Id, Name, Description
            FROM
            projects
            WHERE
            Description LIKE %s
            """,
            ['%%%s%%' % description_like]
        )
        projects = self.cursor.fetchall()
        mapped = map(self._map_project, projects)
        return list(mapped)

    def importall(self, projects):
        self.cursor.execute(
            """
            DELETE
            FROM projects
            """
        )
        for project in projects:
            self.add(project)
