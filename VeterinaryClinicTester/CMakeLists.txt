cmake_minimum_required(VERSION 3.22)
project(VeterinaryClinicTester)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_HEADERS_DIR
        ../Project/headers
)

set(PROJECT_SOURCES_DIR
        ../Project/sources
)

include_directories(
        ${PROJECT_HEADERS_DIR}
)

set(PROJECT_SOURCE_FILES
        ${PROJECT_SOURCES_DIR}/model/Animal.cpp
        ${PROJECT_SOURCES_DIR}/model/AnimalContainer.cpp

        ${PROJECT_SOURCES_DIR}/model/Veterinarian.cpp
        ${PROJECT_SOURCES_DIR}/model/VeterinarianContainer.cpp

        ${PROJECT_SOURCES_DIR}/exceptions/InvalidDataException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/DataConsistencyException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/DuplicatedDataException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/NoDataException.cpp

        main.cpp
)

set(GOOGLE_TEST_LIB
        ${PROJECT_SOURCE_DIR}/googleTestLib/googletest-main
)

add_subdirectory(${GOOGLE_TEST_LIB})

add_executable(
        VeterinaryClinicTester
        ${PROJECT_SOURCE_FILES}
)

target_link_libraries(VeterinaryClinicTester gtest)