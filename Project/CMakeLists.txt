cmake_minimum_required(VERSION 3.26)
project(VeterinaryClinic)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)

file(GLOB_RECURSE SOURCES
        "sources/*.cpp"
        "main.cpp"
)

add_executable(VeterinaryClinic ${SOURCES})