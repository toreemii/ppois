import sys
import os
from PyQt6.QtWidgets import QApplication, QMessageBox, QFileDialog
#sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from models.Student import Student
from views.view import MainWindowView
from views.add_student_dialog import AddStudentDialog
from views.search_dialog import SearchDialog
from views.delete_dialog import DeleteDialog
from database.db_manager import DatabaseManager
from parsers.xml_writer import XMLWriter
from parsers.xml_reader import XMLReader


class Controller:
    def __init__(self):
        self.db = DatabaseManager()
        self.view = MainWindowView()
        self.current_page = 1
        self.records_per_page = 10
        self._connect_signals()
        self.update_display()

    def _connect_signals(self):
        self.view.add_action.triggered.connect(self.add_student)
        self.view.search_action.triggered.connect(self.open_search_dialog)
        self.view.delete_action.triggered.connect(self.open_delete_dialog)
        self.view.export_action.triggered.connect(self.export_to_xml)
        self.view.import_action.triggered.connect(self.import_from_xml)

        self.view.btn_first.clicked.connect(self.go_to_first)
        self.view.btn_prev.clicked.connect(self.prev_page)
        self.view.btn_next.clicked.connect(self.next_page)
        self.view.btn_last.clicked.connect(self.go_to_last)
        self.view.combo_per_page.currentTextChanged.connect(self.change_records_count)

    def update_display(self):
        offset = (self.current_page - 1) * self.records_per_page
        students = self.db.get_students_paged(self.records_per_page, offset)
        total = self.db.get_total_count()
        total_pages = (total + self.records_per_page - 1) // self.records_per_page

        self.view.display_students(students)
        self.view.display_tree(students)
        self.view.lbl_page_info.setText(f"Страница {self.current_page} из {max(1, total_pages)} (Всего: {total})")

    def go_to_first(self):
        self.current_page = 1; self.update_display()

    def go_to_last(self):
        total = self.db.get_total_count()
        self.current_page = max(1, (total + self.records_per_page - 1) // self.records_per_page)
        self.update_display()

    def next_page(self):
        if self.current_page * self.records_per_page < self.db.get_total_count():
            self.current_page += 1
            self.update_display()

    def prev_page(self):
        if self.current_page > 1:
            self.current_page -= 1
            self.update_display()

    def change_records_count(self, count):
        self.records_per_page = int(count)
        self.current_page = 1
        self.update_display()

    def add_student(self):
        dialog = AddStudentDialog(self.view)
        if dialog.exec():
            data = dialog.get_data()
            s = Student(data["last_name"], data["first_name"], data["group_name"], data["birth_date"])
            for g in data.get("grades", []): s.add_grade(g['subject'], g['grade'])
            self.db.add_student(s)
            self.update_display()

    def open_search_dialog(self):
        dialog = SearchDialog(self.db.get_unique_groups(), self.db.get_unique_subjects(), self.view)

        def handle_search():
            res = self.db.search_students_complex(
                group=dialog.group_combo.currentText() if dialog.group_combo.currentText() != "Любая" else None,
                subject=dialog.subject_combo.currentText() if dialog.subject_combo.currentText() != "Любой" else None,
                min_val=dialog.min_grade.value(), max_val=dialog.max_grade.value()
            )
            if not res: QMessageBox.information(dialog, "Поиск", "Ничего не найдено")
            dialog.display_results(res)

        dialog.search_btn.clicked.connect(handle_search)
        dialog.exec()

    def open_delete_dialog(self):
        dialog = DeleteDialog(self.db.get_unique_groups(), self.db.get_unique_subjects(), self.view)

        dialog.btn_del_avg.clicked.connect(lambda: self._del_and_refresh(
            self.db.delete_by_avg_and_subject(dialog.sub_avg_combo.currentText(), dialog.min_avg.value(),
                                              dialog.max_avg.value()), dialog))

        dialog.btn_del_group.clicked.connect(lambda: self._del_and_refresh(
            self.db.delete_by_group(dialog.group_combo.currentText()), dialog))

        dialog.btn_del_item.clicked.connect(lambda: self._del_and_refresh(
            self.db.delete_by_grade_and_subject(dialog.sub_item_combo.currentText(), dialog.min_item.value(),
                                                dialog.max_item.value()), dialog))

        dialog.exec()
        self.update_display()

    def _del_and_refresh(self, count, dialog):
        if count > 0:
            QMessageBox.information(dialog, "Успех", f"Удалено записей: {count}")
            dialog.accept()
        else:
            QMessageBox.warning(dialog, "Внимание", "Записи не найдены")

    def export_to_xml(self):
        path, _ = QFileDialog.getSaveFileName(self.view, "Экспорт", "", "XML Files (*.xml)")
        if path:
            XMLWriter.write(path, self.db.get_students_paged(10000, 0))
            QMessageBox.information(self.view, "XML", "Данные экспортированы (DOM)")

    def import_from_xml(self):
        path, _ = QFileDialog.getOpenFileName(self.view, "Импорт", "", "XML Files (*.xml)")
        if path:
            try:
                for s in XMLReader.read(path): self.db.add_student(s)
                self.update_display()
                QMessageBox.information(self.view, "XML", "Данные импортированы (SAX)")
            except Exception as e:
                QMessageBox.critical(self.view, "Ошибка", str(e))

    def run(self):
        self.view.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    controller = Controller()
    controller.run()
    sys.exit(app.exec())