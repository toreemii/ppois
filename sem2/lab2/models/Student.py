import datetime
from models.Grade import Grade

class Student:
    def __init__(self, last_name, first_name, group_name, birth_date, student_id = None):
        self.id = student_id
        self.last_name = last_name
        self.first_name = first_name
        self.group_name = group_name
        self.birth_date = birth_date
        self.grades = []

    @property
    def average_grade(self) -> float:
        if not self.grades:
            return 0.0
        total_sum = sum(g.grade for g in self.grades)
        return round(total_sum / len(self.grades), 2)
    
    def add_grade(self, subject: str, grade: int):
        self.grades.append(Grade(subject, grade))

    def __repr__(self):
        return f"Student({self.last_name} {self.first_name}, {self.group_name})"