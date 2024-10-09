cmake_minimum_required(VERSION 3.10)

# For Clang to do parsing
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(System2Cpp)

option(SYSTEM2_CPP_USE_SOURCE "Build System2 as source" OFF)

set(SYSTEM2_USE_SOURCE OFF CACHE BOOL "")
if(SYSTEM2_CPP_USE_SOURCE)
    add_library(System2Cpp "${CMAKE_CURRENT_LIST_DIR}/System2.cpp")
    target_compile_definitions(System2Cpp PUBLIC SYSTEM2_CPP_USE_SOURCE=1)
else()
    set(SYSTEM2_USE_SOURCE OFF CACHE BOOL "")
    add_library(System2Cpp INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/External/System2")

if(SYSTEM2_CPP_USE_SOURCE)
    target_link_libraries(System2Cpp PUBLIC System2)
else()
    target_link_libraries(System2Cpp INTERFACE System2)
endif()

add_executable(System2CppExample "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
target_link_libraries(System2CppExample System2Cpp)

