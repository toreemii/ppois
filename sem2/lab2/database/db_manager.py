import sqlite3
from models.Student import Student
from models.Grade import Grade

class DatabaseManager:
    def __init__(self, db_path="students.db"):
        self.conn = sqlite3.connect(db_path)
        self.create_tables()

    def create_tables(self):
        cursor = self.conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                last_name TEXT,
                first_name TEXT,
                group_name TEXT,
                birth_date TEXT
            )
        """)
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS grades (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_id INTEGER,
                subject TEXT,
                grade INTEGER,
                FOREIGN KEY (student_id) REFERENCES students (id) ON DELETE CASCADE
            )
        """)
        self.conn.commit()

    def add_student(self, student):
        cursor = self.conn.cursor()
        cursor.execute("INSERT INTO students (last_name, first_name, group_name, birth_date) VALUES (?, ?, ?, ?)",
                       (student.last_name, student.first_name, student.group_name, student.birth_date))
        student_id = cursor.lastrowid
        for g in student.grades:
            cursor.execute("INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?)",
                           (student_id, g.subject, g.grade))
        self.conn.commit()

    def get_students_paged(self, limit, offset):
        cursor = self.conn.cursor()
        cursor.execute("SELECT id, last_name, first_name, group_name, birth_date FROM students LIMIT ? OFFSET ?",
                       (limit, offset))
        rows = cursor.fetchall()
        students = []
        for r in rows:
            s = Student(r[1], r[2], r[3], r[4], student_id=r[0])
            cursor.execute("SELECT subject, grade FROM grades WHERE student_id = ?", (s.id,))
            for g_row in cursor.fetchall():
                s.add_grade(g_row[0], g_row[1])
            students.append(s)
        return students

    def get_total_count(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT COUNT(*) FROM students")
        return cursor.fetchone()[0]

    def delete_by_group(self, group_name):
        cursor = self.conn.cursor()
        cursor.execute("DELETE FROM students WHERE group_name = ?", (group_name,))
        count = cursor.rowcount
        self.conn.commit()
        return count

    def delete_by_grade_and_subject(self, subject, min_g, max_g):
        cursor = self.conn.cursor()
        query = """
            DELETE FROM students WHERE id IN (
                SELECT student_id FROM grades 
                WHERE subject = ? AND grade BETWEEN ? AND ?
            )
        """
        cursor.execute(query, (subject, min_g, max_g))
        count = cursor.rowcount
        self.conn.commit()
        return count

    def delete_by_avg_and_subject(self, subject, min_avg, max_avg):
        cursor = self.conn.cursor()
        query = """
            SELECT s.id FROM students s
            JOIN grades g ON s.id = g.student_id
            WHERE g.subject = ?
            GROUP BY s.id
            HAVING AVG(g.grade) BETWEEN ? AND ?
        """
        cursor.execute(query, (subject, min_avg, max_avg))
        ids = [row[0] for row in cursor.fetchall()]
        if not ids: return 0

        placeholders = ', '.join(['?'] * len(ids))
        cursor.execute(f"DELETE FROM students WHERE id IN ({placeholders})", ids)
        self.conn.commit()
        return len(ids)

    def search_students_complex(self, group=None, subject=None, min_val=1, max_val=10):
        cursor = self.conn.cursor()
        query = "SELECT id, last_name, first_name, group_name, birth_date FROM students WHERE 1=1"
        params = []
        if group:
            query += " AND group_name = ?"
            params.append(group)

        cursor.execute(query, params)
        rows = cursor.fetchall()
        results = []
        for r in rows:
            s = Student(r[1], r[2], r[3], r[4], student_id=r[0])
            cursor.execute("SELECT subject, grade FROM grades WHERE student_id = ?", (s.id,))
            for gr in cursor.fetchall(): s.add_grade(gr[0], gr[1])

            if subject:
                if any(g.subject == subject and min_val <= g.grade <= max_val for g in s.grades):
                    results.append(s)
            else:
                if min_val <= s.average_grade <= max_val:
                    results.append(s)
        return results

    def get_unique_groups(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT DISTINCT group_name FROM students")
        return [r[0] for r in cursor.fetchall()]

    def get_unique_subjects(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT DISTINCT subject FROM grades")
        return [r[0] for r in cursor.fetchall()]