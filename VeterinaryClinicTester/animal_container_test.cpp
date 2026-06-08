#include "gtest/gtest.h"
#include "model/AnimalContainer.h"

TEST(AnimalContainerAddTest, AddAnimal) {
    // Arrange
    AnimalContainer container;
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);

    // Act
    container.add(animal);

    // Assert
    EXPECT_EQ(container.getAll().size(), 1);
}

TEST(AnimalContainerGetTest, GetExistingAnimal) {
    // Arrange
    AnimalContainer container;
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    container.add(animal);

    // Act
    Animal* result = container.get(1);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getName(), "Rex");
}

TEST(AnimalContainerGetTest, GetNonExistingAnimal) {
    // Arrange
    AnimalContainer container;

    // Act
    Animal* result = container.get(99);

    // Assert
    EXPECT_EQ(result, nullptr);
}

TEST(AnimalContainerNextIdTest, EmptyContainer) {
    // Arrange
    AnimalContainer container;

    // Act
    int nextId = container.getNextId();

    // Assert
    EXPECT_EQ(nextId, 1);
}

TEST(AnimalContainerNextIdTest, NonEmptyContainer) {
    // Arrange
    AnimalContainer container;
    container.add(Animal(1, "Rex", "Dog", "Labrador", 20.5, 4));
    container.add(Animal(2, "Luna", "Cat", "Siamese", 5.0, 2));

    // Act
    int nextId = container.getNextId();

    // Assert
    EXPECT_EQ(nextId, 3);
}