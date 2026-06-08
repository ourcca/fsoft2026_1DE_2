cmake_minimum_required(VERSION 3.26)
project(VeterinaryClinic)

set(CMAKE_CXX_STANDARD 17)

include_directories(headers)

file(GLOB_RECURSE SOURCES
        "sources/*.cpp"
        "main.cpp"
)

add_executable(VeterinaryClinic ${SOURCES}
        headers/exceptions/DataConsistencyException.h
        sources/exceptions/DataConsistencyException.cpp
<<<<<<< HEAD
        headers/repo/ClinicRepositoryBinary.h
        sources/repo/ClinicRepositoryBinary.cpp)
=======
        headers/model/Date.h
        headers/model/Time.h
        sources/model/Time.cpp)
>>>>>>> d0342425380dce8895d0189688b536e6e9544763
