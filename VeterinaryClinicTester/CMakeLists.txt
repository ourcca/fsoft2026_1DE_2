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
        ${PROJECT_SOURCES_DIR}/model/Service.cpp
        ${PROJECT_SOURCES_DIR}/model/ServiceContainer.cpp
        ${PROJECT_SOURCES_DIR}/model/Prescription.cpp
        ${PROJECT_SOURCES_DIR}/model/PrescriptionContainer.cpp
        ${PROJECT_SOURCES_DIR}/model/Date.cpp
        ${PROJECT_SOURCES_DIR}/model/Time.cpp
        ${PROJECT_SOURCES_DIR}/model/Clinic.cpp

        ${PROJECT_SOURCES_DIR}/services/AnimalService.cpp
        ${PROJECT_SOURCES_DIR}/services/ServiceService.cpp
        ${PROJECT_SOURCES_DIR}/services/PrescriptionService.cpp
        ${PROJECT_SOURCES_DIR}/services/VeterinarianService.cpp

        ${PROJECT_SOURCES_DIR}/mappers/AnimalMapper.cpp
        ${PROJECT_SOURCES_DIR}/mappers/ServiceMapper.cpp
        ${PROJECT_SOURCES_DIR}/mappers/PrescriptionMapper.cpp
        ${PROJECT_SOURCES_DIR}/mappers/VeterinarianMapper.cpp

        ${PROJECT_SOURCES_DIR}/exceptions/InvalidDataException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/DataConsistencyException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/DuplicatedDataException.cpp
        ${PROJECT_SOURCES_DIR}/exceptions/NoDataException.cpp

        ${PROJECT_SOURCES_DIR}/repo/ClinicRepositoryBinary.cpp
        ${PROJECT_SOURCES_DIR}/repo/ClinicRepositoryMemory.cpp

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