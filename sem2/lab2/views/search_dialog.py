from PyQt6.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QComboBox,
                             QSpinBox, QDoubleSpinBox, QPushButton, QLabel,
                             QTableWidget, QTableWidgetItem, QHeaderView)


class SearchDialog(QDialog):
    def __init__(self, groups, subjects, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Поиск студентов")
        self.resize(800, 500)

        layout = QVBoxLayout(self)
        filter_layout = QHBoxLayout()

        filter_layout.addWidget(QLabel("Группа:"))
        self.group_combo = QComboBox()
        self.group_combo.addItems(["Любая"] + groups)
        filter_layout.addWidget(self.group_combo)

        filter_layout.addWidget(QLabel("Предмет:"))
        self.subject_combo = QComboBox()
        self.subject_combo.addItems(["Любой"] + subjects)
        filter_layout.addWidget(self.subject_combo)

        filter_layout.addWidget(QLabel("Балл от:"))
        self.min_grade = QSpinBox()
        self.min_grade.setRange(0, 10)
        filter_layout.addWidget(self.min_grade)

        filter_layout.addWidget(QLabel("до:"))
        self.max_grade = QSpinBox()
        self.max_grade.setRange(0, 10)
        self.max_grade.setValue(10)
        filter_layout.addWidget(self.max_grade)
        layout.addLayout(filter_layout)

        avg_layout = QHBoxLayout()
        avg_layout.addWidget(QLabel("Средний балл от:"))
        self.min_avg = QDoubleSpinBox()
        self.min_avg.setRange(0, 10)
        avg_layout.addWidget(self.min_avg)

        avg_layout.addWidget(QLabel("до:"))
        self.max_avg = QDoubleSpinBox()
        self.max_avg.setRange(0, 10)
        self.max_avg.setValue(100)
        avg_layout.addWidget(self.max_avg)

        self.search_btn = QPushButton("Найти")
        avg_layout.addWidget(self.search_btn)
        layout.addLayout(avg_layout)

        self.result_table = QTableWidget()
        self.result_table.setColumnCount(5)
        self.result_table.setHorizontalHeaderLabels(["Фамилия", "Имя", "Группа", "Дата рожд.", "Ср. балл"])
        self.result_table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)
        layout.addWidget(self.result_table)

        # --- Пагинация внутри поиска ---
        nav_layout = QHBoxLayout()
        self.prev_btn = QPushButton("Пред.")
        self.next_btn = QPushButton("След.")
        self.page_label = QLabel("Страница 1")

        nav_layout.addStretch()
        nav_layout.addWidget(self.prev_btn)
        nav_layout.addWidget(self.page_label)
        nav_layout.addWidget(self.next_btn)
        nav_layout.addStretch()

        layout.addLayout(nav_layout)

    def display_results(self, students):
        self.result_table.setRowCount(len(students))
        for row, s in enumerate(students):
            self.result_table.setItem(row, 0, QTableWidgetItem(s.last_name))
            self.result_table.setItem(row, 1, QTableWidgetItem(s.first_name))
            self.result_table.setItem(row, 2, QTableWidgetItem(s.group_name))
            self.result_table.setItem(row, 3, QTableWidgetItem(str(s.birth_date)))
            self.result_table.setItem(row, 4, QTableWidgetItem(f"{s.average_grade:.2f}"))