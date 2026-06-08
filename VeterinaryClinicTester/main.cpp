#include <iostream>
#include <gtest/gtest.h>

#include "animal_test.cpp"
#include "animal_container_test.cpp"
#include "veterinarian_test.cpp"
#include "veterinarian_container_test.cpp"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}