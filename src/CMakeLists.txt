cmake_minimum_required(VERSION 3.14)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(helion_src
    interpreter/script/invokable.cpp
    interpreter/script/linker.cpp
    interpreter/script/script_parser.cpp
    interpreter/script/script.cpp

    interpreter/instr_func.cpp
    interpreter/instr_type.cpp
    interpreter/instr_parser.cpp
    interpreter/instr_runner.cpp

    memory/mem_mapping.cpp
    memory/mem_types.cpp
    
    util/env_util.cpp
    util/mem_util.cpp
    util/string_util.cpp
    util/value_util.cpp
)

# ensures that the files needed to debug the instruction runner are present
# set(TEST_FILES
#     test_scripts/test_allocate.helios
#     test_files/test_json.json

#     test_program/instrs_1.heli
# )

foreach(test_file ${TEST_FILES})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${test_file} ${CMAKE_CURRENT_BINARY_DIR}/${test_file} COPYONLY)
endforeach()

target_include_directories(helion_src
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)

add_executable(helion_test_main test_main.cpp)
target_include_directories(helion_test_main
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(helion_test_main PRIVATE helion_src nlohmann_json::nlohmann_json)