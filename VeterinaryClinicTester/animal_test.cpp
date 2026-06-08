#include "gtest/gtest.h"
#include "model/Animal.h"

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