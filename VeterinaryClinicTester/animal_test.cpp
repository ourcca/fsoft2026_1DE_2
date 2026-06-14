#include "gtest/gtest.h"
#include "model/Animal.h"
#include "exceptions/InvalidDataException.h"

TEST(AnimalConstructorTest, ValidAnimal) {
    // Arrange + Act
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);

    // Assert
    EXPECT_EQ(animal.getId(), 1);
    EXPECT_EQ(animal.getName(), "Rex");
    EXPECT_EQ(animal.getSpecies(), "Dog");
    EXPECT_EQ(animal.getBreed(), "Labrador");
    EXPECT_EQ(animal.getWeight(), 20.5f);
    EXPECT_EQ(animal.getAge(), 4);
}

TEST(AnimalOperatorEqualTest, EqualAnimals) {
    // Arrange
    Animal animal1(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Animal animal2(1, "Luna", "Cat", "Siamese", 5.0, 2);

    // Act
    bool result = animal1 == animal2;

    // Assert
    EXPECT_TRUE(result);
}

TEST(AnimalOperatorEqualTest, DifferentAnimals) {
    // Arrange
    Animal animal1(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Animal animal2(2, "Luna", "Cat", "Siamese", 5.0, 2);

    // Act
    bool result = animal1 == animal2;

    // Assert
    EXPECT_FALSE(result);
}

TEST(AnimalValidationTest, InvalidAnimalFieldsThrowException) {
    EXPECT_THROW(Animal(0, "Rex", "Dog", "Labrador", 20.5f, 4), InvalidDataException);
    EXPECT_THROW(Animal(1, " ", "Dog", "Labrador", 20.5f, 4), InvalidDataException);
    EXPECT_THROW(Animal(1, "Rex", " ", "Labrador", 20.5f, 4), InvalidDataException);
    EXPECT_THROW(Animal(1, "Rex", "Dog", "Labrador", 0.0f, 4), InvalidDataException);
    EXPECT_THROW(Animal(1, "Rex", "Dog", "Labrador", 20.5f, -1), InvalidDataException);
}

TEST(AnimalValidationTest, TextFieldsAreTrimmed) {
    Animal animal(1, " Rex ", " Dog ", " Labrador ", 20.5f, 4);

    EXPECT_EQ(animal.getName(), "Rex");
    EXPECT_EQ(animal.getSpecies(), "Dog");
    EXPECT_EQ(animal.getBreed(), "Labrador");
}