class Grade:
    def __init__(self, subject: str, grade: int):
        self.subject = subject
        self.grade = grade

    def __repr__(self):
        return f"{self.subject}: {self.grade}"