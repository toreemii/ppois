import xml.dom.minidom as minidom

class XMLWriter:
    @staticmethod
    def write(file_path, students):
        doc = minidom.Document()
        root = doc.createElement('students_database')
        doc.appendChild(root)

        for s in students:
            student_node = doc.createElement('student')
            student_node.setAttribute('last_name', s.last_name)
            student_node.setAttribute('first_name', s.first_name)
            student_node.setAttribute('group', s.group_name)
            student_node.setAttribute('birth_date', str(s.birth_date))

            grades_node = doc.createElement('grades')
            for g in s.grades:
                grade_node = doc.createElement('grade')
                grade_node.setAttribute('subject', g.subject)
                grade_node.setAttribute('value', str(g.grade))
                grades_node.appendChild(grade_node)

            student_node.appendChild(grades_node)
            root.appendChild(student_node)

        with open(file_path, "w", encoding="utf-8") as f:
            f.write(doc.toprettyxml(indent="    "))