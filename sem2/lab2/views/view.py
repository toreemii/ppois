from PyQt6.QtWidgets import (QMainWindow, QTableWidget, QTableWidgetItem,
                             QVBoxLayout, QWidget, QToolBar, QHBoxLayout,
                             QPushButton, QLabel, QComboBox, QTabWidget, QTreeWidget, QTreeWidgetItem)
from PyQt6.QtGui import QAction


class MainWindowView(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Студенческая База (MVC)")
        self.resize(1000, 600)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QVBoxLayout(self.central_widget)

        self.tabs = QTabWidget()
        self.layout.addWidget(self.tabs)

        self.table_container = QWidget()
        self.table_layout = QVBoxLayout(self.table_container)
        self.table = QTableWidget()
        self.table_layout.addWidget(self.table)
        self.tabs.addTab(self.table_container, "Таблица")

        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["Параметр", "Значение"])
        self.tabs.addTab(self.tree, "Дерево")

        pagination_layout = QHBoxLayout()

        self.btn_first = QPushButton("<<")
        self.btn_prev = QPushButton("<")
        self.lbl_page_info = QLabel("Страница 1 из ?")
        self.btn_next = QPushButton(">")
        self.btn_last = QPushButton(">>")

        self.combo_per_page = QComboBox()
        self.combo_per_page.addItems(["5", "10", "20", "50"])
        self.combo_per_page.setCurrentText("10")

        pagination_layout.addWidget(self.btn_first)
        pagination_layout.addWidget(self.btn_prev)
        pagination_layout.addStretch()
        pagination_layout.addWidget(self.lbl_page_info)
        pagination_layout.addStretch()
        pagination_layout.addWidget(self.btn_next)
        pagination_layout.addWidget(self.btn_last)
        pagination_layout.addWidget(QLabel("Показывать по:"))
        pagination_layout.addWidget(self.combo_per_page)

        self.layout.addLayout(pagination_layout)

        self._create_menu_and_toolbar()

    def _create_menu_and_toolbar(self):
        self.menu = self.menuBar()
        self.file_menu = self.menu.addMenu("Меню")
        self.toolbar = QToolBar("Main Toolbar")
        self.addToolBar(self.toolbar)

        self.add_action = QAction("Добавить", self)
        self.search_action = QAction("Поиск", self)
        self.delete_action = QAction("Удалить", self)
        self.export_action = QAction("Экспорт XML", self)
        self.import_action = QAction("Импорт XML", self)

        for action in [self.add_action, self.search_action, self.delete_action, self.export_action, self.import_action]:
            self.file_menu.addAction(action)
            self.toolbar.addAction(action)

    def display_students(self, students):
        if not students:
            self.table.setRowCount(0)
            return

        max_exams = max((len(s.grades) for s in students), default=0)
        self.table.setColumnCount(3 + max_exams * 2)

        headers = ["ФИО", "Группа", "Дата рожд."]
        for i in range(1, max_exams + 1):
            headers.extend([f"Предмет {i}", f"Балл {i}"])
        self.table.setHorizontalHeaderLabels(headers)

        self.table.setRowCount(len(students))
        for row, s in enumerate(students):
            self.table.setItem(row, 0, QTableWidgetItem(f"{s.last_name} {s.first_name}"))
            self.table.setItem(row, 1, QTableWidgetItem(s.group_name))
            self.table.setItem(row, 2, QTableWidgetItem(str(s.birth_date)))

            for i, g in enumerate(s.grades):
                self.table.setItem(row, 3 + i * 2, QTableWidgetItem(g.subject))
                self.table.setItem(row, 4 + i * 2, QTableWidgetItem(str(g.grade)))

    def display_tree(self, students):
        self.tree.clear()
        for s in students:
            student_node = QTreeWidgetItem(self.tree, [f"{s.last_name} {s.first_name}", "Студент"])
            QTreeWidgetItem(student_node, ["Группа", s.group_name])
            QTreeWidgetItem(student_node, ["Дата рождения", str(s.birth_date)])

            if s.grades:
                exams_node = QTreeWidgetItem(student_node, ["Экзамены", f"Ср. балл: {s.average_grade:.2f}"])
                for g in s.grades:
                    QTreeWidgetItem(exams_node, [g.subject, str(g.grade)])
        self.tree.expandAll()