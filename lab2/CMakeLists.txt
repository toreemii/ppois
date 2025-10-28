cmake_minimum_required(VERSION 3.10)
project(TransportProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(TransportTests
    tests.cpp
    Client.cpp
    Order.cpp
    Fuel.cpp
    Truck.cpp
    Passenger.cpp
    Depot.cpp
    Shipment.cpp
    Feedback.cpp
    DispatchCenter.cpp
    Notification.cpp
    Hub.cpp
    Invoice.cpp
    InventoryManager.cpp
    PaymentProcessor.cpp
    Menu.cpp
    Driver.cpp
    Analytics.cpp
    Logistics.cpp
    ClientActivityLogger.cpp
    LoyaltyManager.cpp
    PaymentManager.cpp
    VehicleStatus.cpp
    Vehicle.cpp
    AuditManager.cpp
    Billing.cpp
    Delivery.cpp
    RoutePlanner.cpp
    ManagerCoordinator.cpp
    RevenueCalculator.cpp
    OperationsMonitor.cpp
    CargoInspector.cpp
    License.cpp
    GPS.cpp
    Route.cpp
    Security.cpp
    Warehouse.cpp
    Freight.cpp
    Ship.cpp
    Train.cpp
    Van.cpp
    Employee.cpp
    Maintenance.cpp
    TransportCompany.cpp
    Manager.cpp
    Ticket.cpp
    Feedback.cpp
    PaymentProcessor.cpp
    Menu.cpp
    DispatchCenter.cpp
)
target_link_libraries(TransportTests GTest::gtest GTest::gtest_main pthread)

if(ENABLE_COVERAGE)
    find_program(GCOVR_PATH gcovr)
    
    if(GCOVR_PATH)
        add_custom_target(coverage
            COMMAND ./TransportTests
            COMMAND ${GCOVR_PATH} -r .. --object-directory . --exclude='.*googletest.*' --exclude='.*tests.*' --exclude='.*_deps.*' --print-summary
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS TransportTests
            COMMENT "Running tests and generating coverage report"
        )

        add_custom_target(coverage-detailed
            COMMAND ./TransportTests
            COMMAND ${GCOVR_PATH} -r .. --object-directory . --exclude='.*googletest.*' --exclude='.*tests.*' --exclude='.*_deps.*'
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS TransportTests
        )
        
        add_custom_target(coverage-html
            COMMAND ./TransportTests
            COMMAND ${GCOVR_PATH} -r .. --object-directory . --exclude='.*googletest.*' --exclude='.*tests.*' --exclude='.*_deps.*' --html --html-details -o coverage_report.html
            COMMAND echo "HTML coverage report: ${CMAKE_BINARY_DIR}/coverage_report.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS TransportTests
        )
        
    else()
        message(WARNING "gcovr not found. Install with: sudo apt-get install gcovr")
        
        find_program(LCOV_PATH lcov)
        find_program(GENHTML_PATH genhtml)
        
        if(LCOV_PATH AND GENHTML_PATH)
            add_custom_target(coverage
                COMMAND ./TransportTests
                COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info --ignore-errors mismatch,gcov,empty
                COMMAND ${LCOV_PATH} --remove coverage.info '*/googletest/*' '*/tests/*' '/usr/*' '*/_deps/*' --output-file coverage.info
                COMMAND ${LCOV_PATH} --summary coverage.info
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                DEPENDS TransportTests
            )
        endif()
    endif()
endif()