cmake_minimum_required(VERSION 3.14)

find_package(Catch2 REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(TEST_SRC
    interpreter/test_instr_parser.cpp
    memory/test_mem_types.cpp
    memory/test_mem_util.cpp
    memory/test_mem_mapping.cpp
    util/test_string_util.cpp
    util/test_value_util.cpp
)

# ensures that tthe files needed to run the test cases are included in the build environment
set(TEST_FILES
    interpreter/validation_scripts/test_valid.heli
    interpreter/validation_scripts/test_invalid_1.heli
    interpreter/validation_scripts/test_invalid_2.heli
    interpreter/validation_scripts/test_invalid_3.heli
    interpreter/validation_scripts/test_invalid_4.heli
)

foreach(test_file ${TEST_FILES})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${test_file} ${CMAKE_CURRENT_BINARY_DIR}/${test_file} COPYONLY)
endforeach()

add_executable(catch_testing ${TEST_SRC})

target_include_directories(catch_testing
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(catch_testing PRIVATE helion_src Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

include(CTest)
include(Catch)
catch_discover_tests(catch_testing)