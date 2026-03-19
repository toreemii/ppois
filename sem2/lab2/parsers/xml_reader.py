import xml.sax as sax
from models.Student import Student

class StudentSAXHandler(sax.ContentHandler):
    def __init__(self):
        self.students = []
        self.current_student = None

    def startElement(self, name, attrs):
        if name == "student":
            self.current_student = Student(
                last_name=attrs['last_name'],
                first_name=attrs['first_name'],
                group_name=attrs['group'],
                birth_date=attrs['birth_date']
            )
        elif name == "grade" and self.current_student:
            self.current_student.add_grade(
                attrs['subject'],
                int(attrs['value'])
            )

    def endElement(self, name):
        if name == "student" and self.current_student:
            self.students.append(self.current_student)
            self.current_student = None

class XMLReader:
    @staticmethod
    def read(file_path):
        handler = StudentSAXHandler()
        sax.parse(file_path, handler)
        return handler.students