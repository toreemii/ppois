cmake_minimum_required(VERSION 3.14)
project(BubbleSortTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# === Покрытие ===
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# === Google Test ===
find_package(GTest REQUIRED)

# === Заголовки в корне ===
include_directories(${CMAKE_SOURCE_DIR})

# === Тесты ===
enable_testing()

add_executable(test_runner
    tests.cpp
)

target_link_libraries(test_runner
    GTest::gtest
    GTest::gtest_main
    pthread
)

add_test(NAME BubbleSortTests COMMAND test_runner)

# === GCOVR ===
find_program(GCOVR gcovr)

if(GCOVR)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Running tests to collect coverage..."
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Generating coverage report..."
        COMMAND ${GCOVR}
            --root=${CMAKE_SOURCE_DIR}
            --object-directory=${CMAKE_BINARY_DIR}
            --exclude=${CMAKE_SOURCE_DIR}/tests
            --exclude=${CMAKE_SOURCE_DIR}/googletest
            --exclude-unreachable-branches
            --print-summary
            --output=${CMAKE_BINARY_DIR}/coverage_report.txt
        COMMAND ${CMAKE_COMMAND} -E cat ${CMAKE_BINARY_DIR}/coverage_report.txt
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Code coverage with gcovr"
    )

    add_custom_target(coverage-html
        COMMAND ${CMAKE_COMMAND} -E echo "(INFO) Generating HTML coverage report..."
        COMMAND ${GCOVR}
            --root=${CMAKE_SOURCE_DIR}
            --object-directory=${CMAKE_BINARY_DIR}
            --exclude=${CMAKE_SOURCE_DIR}/tests
            --exclude=${CMAKE_SOURCE_DIR}/googletest
            --html --html-details
            --output=${CMAKE_BINARY_DIR}/coverage/html/index.html
        COMMAND ${CMAKE_COMMAND} -E echo "HTML report: file://${CMAKE_BINARY_DIR}/coverage/html/index.html"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "HTML coverage report"
        DEPENDS coverage
    )
else()
    message(WARNING "gcovr not found — coverage targets disabled")
endif()