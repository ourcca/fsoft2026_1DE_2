#include "gtest/gtest.h"
#include "model/Veterinarian.h"
#include "exceptions/InvalidDataException.h"

TEST(VeterinarianConstructorTest, ValidVeterinarian) {
    // Arrange + Act
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    // Assert
    EXPECT_EQ(veterinarian.getId(), 1);
    EXPECT_EQ(veterinarian.getName(), "Joao Silva");
    EXPECT_EQ(veterinarian.getAge(), 35);
    EXPECT_EQ(veterinarian.getSpecialty(), "Surgery");
}

TEST(VeterinarianOperatorEqualTest, EqualVeterinarians) {
    // Arrange
    Veterinarian veterinarian1(1, "Joao Silva", 35, "Surgery");
    Veterinarian veterinarian2(1, "Maria Costa", 40, "Dermatology");

    // Act
    bool result = veterinarian1 == veterinarian2;

    // Assert
    EXPECT_TRUE(result);
}

TEST(VeterinarianOperatorEqualTest, DifferentVeterinarians) {
    // Arrange
    Veterinarian veterinarian1(1, "Joao Silva", 35, "Surgery");
    Veterinarian veterinarian2(2, "Maria Costa", 40, "Dermatology");

    // Act
    bool result = veterinarian1 == veterinarian2;

    // Assert
    EXPECT_FALSE(result);
}

TEST(VeterinarianValidationTest, InvalidVeterinarianFieldsThrowException) {
    EXPECT_THROW(Veterinarian(0, "Joao", 35, "Surgery"), InvalidDataException);
    EXPECT_THROW(Veterinarian(1, " ", 35, "Surgery"), InvalidDataException);
    EXPECT_THROW(Veterinarian(1, "Joao", 17, "Surgery"), InvalidDataException);
    EXPECT_THROW(Veterinarian(1, "Joao", 71, "Surgery"), InvalidDataException);
}

TEST(VeterinarianValidationTest, TextFieldsAreTrimmed) {
    Veterinarian veterinarian(1, " Joao ", 35, " Surgery ");

    EXPECT_EQ(veterinarian.getName(), "Joao");
    EXPECT_EQ(veterinarian.getSpecialty(), "Surgery");
}