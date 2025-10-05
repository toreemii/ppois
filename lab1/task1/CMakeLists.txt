cmake_minimum_required(VERSION 3.10)
project(CantorovoSetTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building with coverage flags")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -lgcov")
endif()

find_package(GTest)
if(NOT GTest_FOUND)
    message(STATUS "Google Test not found, fetching it...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
endif()

set(SRC_FILES CantorovoSet.cpp InputCheck.cpp)
set(TEST_FILES tests.cpp)
set(INCLUDE_DIRS ${CMAKE_SOURCE_DIR})

add_executable(tests ${SRC_FILES} ${TEST_FILES})

target_link_libraries(tests GTest::gtest GTest::gtest_main pthread)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(tests gcov)
endif()

add_test(NAME AllTests COMMAND tests)

find_program(GCOVR gcovr)
if(GCOVR AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "gcovr found, enabling coverage report generation")
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests to generate coverage data..."
        COMMAND ${CMAKE_CTEST_COMMAND}
        COMMAND ${GCOVR} --root "${CMAKE_SOURCE_DIR}" --filter "${CMAKE_SOURCE_DIR}/CantorovoSet.cpp" --filter "${CMAKE_SOURCE_DIR}/InputCheck.cpp" --gcov-ignore-errors no_working_dir_found --gcov-ignore-errors source_not_found --print-summary
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage summary for CantorovoSet.cpp and InputCheck.cpp in console"
    )
else()
    message(WARNING "gcovr not found or not Debug build, coverage report generation disabled")
endif()