cmake_minimum_required(VERSION 3.13)
project(libblowfish C)

set(CMAKE_C_STANDARD 99)

add_library(libblowfish
        src/blowfish.c
        src/boxes.c
)

target_include_directories(libblowfish PUBLIC inc)

if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
    include(CTest)
    add_subdirectory(examples)
    add_subdirectory(test)
endif ()
