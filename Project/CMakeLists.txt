cmake_minimum_required(VERSION 3.26)
project(VeterinaryClinic)

if (MSVC)
    add_compile_options(/utf-8)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)

file(GLOB_RECURSE SOURCES
        "sources/*.cpp"
        "main.cpp"
)

add_executable(VeterinaryClinic ${SOURCES}
        headers/services/ServiceCatalog.h
        sources/services/ServiceCatalog.cpp)