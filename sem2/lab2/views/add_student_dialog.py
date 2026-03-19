from PyQt6.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLineEdit, 
                             QDateEdit, QPushButton, QLabel, QSpinBox, 
                             QListWidget, QFormLayout)
from PyQt6.QtCore import QDate

class AddStudentDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Добавить нового студента")
        self.setMinimumWidth(400)
        
        layout = QVBoxLayout(self)
        form = QFormLayout()

        self.last_name_input = QLineEdit()
        self.first_name_input = QLineEdit()
        self.group_input = QLineEdit()

        self.birth_date_input = QDateEdit()
        self.birth_date_input.setCalendarPopup(True)
        self.birth_date_input.setDate(QDate.currentDate().addYears(-18))

        form.addRow("Фамилия:", self.last_name_input)
        form.addRow("Имя:", self.first_name_input)
        form.addRow("Группа:", self.group_input)
        form.addRow("Дата рождения:", self.birth_date_input)

        layout.addLayout(form)

        layout.addWidget(QLabel("<b>Оценки по предметам:</b>"))
        self.grades_list = QListWidget()
        layout.addWidget(self.grades_list)

        grade_tool_layout = QHBoxLayout()
        self.subject_input = QLineEdit()
        self.subject_input.setPlaceholderText("Предмет")
        self.grade_input = QSpinBox()
        self.grade_input.setRange(1, 10)
        
        add_grade_btn = QPushButton("Добавить предмет")
        add_grade_btn.clicked.connect(self.add_grade_to_list)
        
        grade_tool_layout.addWidget(self.subject_input)
        grade_tool_layout.addWidget(self.grade_input)
        grade_tool_layout.addWidget(add_grade_btn)
        layout.addLayout(grade_tool_layout)

        buttons = QHBoxLayout()
        save_btn = QPushButton("Сохранить студента")
        save_btn.clicked.connect(self.accept)
        cancel_btn = QPushButton("Отмена")
        cancel_btn.clicked.connect(self.reject)
        
        buttons.addWidget(save_btn)
        buttons.addWidget(cancel_btn)
        layout.addLayout(buttons)

    def add_grade_to_list(self):
        subject = self.subject_input.text()
        grade = self.grade_input.value()
        if subject:
            self.grades_list.addItem(f"{subject}: {grade}")
            self.subject_input.clear()

    def get_data(self):
        grades = []
        for i in range(self.grades_list.count()):
            text = self.grades_list.item(i).text()
            sub, gr = text.split(": ")
            grades.append({"subject": sub, "grade": int(gr)})

        return {
            "last_name": self.last_name_input.text(),
            "first_name": self.first_name_input.text(),
            "group_name": self.group_input.text(),
            "birth_date": self.birth_date_input.date().toPyDate(),
            "grades": grades
        }