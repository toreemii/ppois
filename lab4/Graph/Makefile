BUILD_DIR = build
CMAKE = cmake
MAKE = make
CTEST = ctest
GCOVR = gcovr

.PHONY: all test coverage coverage-html clean help

all: test

$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) -DCMAKE_BUILD_TYPE=Coverage ..

$(BUILD_DIR)/GraphTests: $(BUILD_DIR)/Makefile
	@cd $(BUILD_DIR) && $(MAKE)

test: $(BUILD_DIR)/GraphTests
	@echo "=== Запуск тестов ==="
	@cd $(BUILD_DIR) && $(CTEST) --output-on-failure

coverage: $(BUILD_DIR)/GraphTests
	@echo "=== Запуск тестов с покрытием ==="
	@cd $(BUILD_DIR) && ./GraphTests
	@echo ""
	@echo "(INFO) Генерация отчёта покрытия..."
	@$(GCOVR) \
		--root=. \
		--object-directory=$(BUILD_DIR) \
		--exclude=$(BUILD_DIR)/ \
		--exclude=googletest/ \
		--exclude-unreachable-branches \
		--print-summary \
		--output=$(BUILD_DIR)/coverage_report.txt
	@echo "------------------------------------------------------------------------------"
	@echo "                           GCC Code Coverage Report"
	@echo "Directory: .."
	@echo "------------------------------------------------------------------------------"
	@cat $(BUILD_DIR)/coverage_report.txt
	@echo "------------------------------------------------------------------------------"

coverage-html: $(BUILD_DIR)/GraphTests
	@echo "=== Запуск тестов с покрытием ==="
	@cd $(BUILD_DIR) && ./GraphTests
	@echo ""
	@echo "(INFO) Генерация HTML-отчёта..."
	@mkdir -p $(BUILD_DIR)/coverage/html
	@$(GCOVR) \
		--root=. \
		--object-directory=$(BUILD_DIR) \
		--exclude=$(BUILD_DIR)/ \
		--exclude=googletest/ \
		--exclude-unreachable-branches \
		--html --html-details \
		--output=$(BUILD_DIR)/coverage/html/index.html
	@echo "HTML-отчёт: file://$(PWD)/$(BUILD_DIR)/coverage/html/index.html"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Сборка очищена"

help:
	@echo "Доступные цели:"
	@echo "  all           - запустить тесты"
	@echo "  test          - собрать и запустить тесты"
	@echo "  coverage      - отчет покрытия в консоли"
	@echo "  coverage-html - HTML отчет покрытия"
	@echo "  clean         - очистить сборку"
	@echo "  help          - эта справка"