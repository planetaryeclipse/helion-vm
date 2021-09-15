cmake_minimum_required(VERSION 3.14)
project(helion-lang VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER /usr/bin/gcc-11)
set(CMAKE_CXX_COMPILER /usr/bin/g++-11)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)

add_executable(instr_inter src/apps/instr_inter.cpp)
target_include_directories(instr_inter
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(instr_inter PRIVATE helion_src)

add_executable(prog_inter src/apps/prog_inter.cpp)
target_include_directories(prog_inter
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
)
target_link_libraries(prog_inter PRIVATE helion_src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
