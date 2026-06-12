#include <iostream>
#include <gtest/gtest.h>

#include "animal_test.cpp"
#include "animal_container_test.cpp"
#include "veterinarian_test.cpp"
#include "veterinarian_container_test.cpp"
#include "service_test.cpp"
#include "service_container_test.cpp"
#include "prescription_test.cpp"
#include "prescription_container_test.cpp"
#include "date_test.cpp"
#include "time_test.cpp"
#include "service_service_test.cpp"
#include "prescription_service_test.cpp"
#include "animal_service_test.cpp"
#include "clinic_repository_binary_test.cpp"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}