BUILD_DIR = build
CMAKE = cmake
CTEST = ctest
GCOVR = gcovr

.PHONY: all test coverage coverage-html clean

all: test

$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE) ..

$(BUILD_DIR)/test_runner: $(BUILD_DIR)/Makefile
	@$(CMAKE) --build $(BUILD_DIR)

test: $(BUILD_DIR)/test_runner
	@echo "=== Запуск тестов ==="
	@cd $(BUILD_DIR) && $(CTEST) --output-on-failure

coverage: test
	@echo "(INFO) Генерация отчёта покрытия..."
	@$(GCOVR) \
		--root=. \
		--object-directory=$(BUILD_DIR) \
		--exclude=build/ \
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

coverage-html: coverage
	@echo "(INFO) Генерация HTML-отчёта..."
	@mkdir -p $(BUILD_DIR)/coverage/html
	@$(GCOVR) \
		--root=. \
		--object-directory=$(BUILD_DIR) \
		--exclude=build/ \
		--exclude=googletest/ \
		--html --html-details \
		--output=$(BUILD_DIR)/coverage/html/index.html
	@echo "HTML-отчёт: file://$(PWD)/$(BUILD_DIR)/coverage/html/index.html"

clean:
	@rm -rf $(BUILD_DIR)