cmake_minimum_required(VERSION 3.14)
project(Graph LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === Покрытие кода ===
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# === Добавить поддиректорию googletest ===
add_subdirectory(googletest)

# === Основное приложение ===
add_executable(GraphApp main.cpp)

# === Тестовое приложение ===
add_executable(GraphTests tests.cpp)

# === Подключение Google Test к тестам ===
target_link_libraries(GraphTests
    gtest_main
    gtest
)

# === Включение директив компилятора для тестов ===
target_compile_definitions(GraphTests PRIVATE GTEST_HAS_TR1_TUPLE=0)

# === Добавление тестов в CTest ===
include(GoogleTest)
gtest_discover_tests(GraphTests)

# === GCOVR для покрытия кода ===
find_program(GCOVR gcovr)

if(GCOVR)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Running tests to collect coverage..."
        COMMAND ./GraphTests
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Generating coverage report..."
        COMMAND ${GCOVR}
            --root=${CMAKE_SOURCE_DIR}
            --object-directory=${CMAKE_BINARY_DIR}
            --exclude=${CMAKE_BINARY_DIR}/
            --exclude=${CMAKE_SOURCE_DIR}/googletest
            --exclude-unreachable-branches
            --print-summary
            --output=${CMAKE_BINARY_DIR}/coverage_report.txt
        COMMAND ${CMAKE_COMMAND} -E cat ${CMAKE_BINARY_DIR}/coverage_report.txt
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Code coverage with gcovr"
        DEPENDS GraphTests
    )

    add_custom_target(coverage-html
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Generating HTML coverage report..."
        COMMAND ${GCOVR}
            --root=${CMAKE_SOURCE_DIR}
            --object-directory=${CMAKE_BINARY_DIR}
            --exclude=${CMAKE_BINARY_DIR}/
            --exclude=${CMAKE_SOURCE_DIR}/googletest
            --exclude-unreachable-branches
            --html --html-details
            --output=${CMAKE_BINARY_DIR}/coverage/html/index.html
        COMMAND ${CMAKE_COMMAND} -E echo "HTML report: file://${CMAKE_BINARY_DIR}/coverage/html/index.html"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "HTML coverage report"
        DEPENDS GraphTests
    )
else()
    message(WARNING "gcovr not found — coverage targets disabled")
endif()