#include "gtest/gtest.h"
#include "model/VeterinarianContainer.h"

TEST(VeterinarianContainerAddTest, AddVeterinarian) {
    // Arrange
    VeterinarianContainer container;
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    // Act
    container.add(veterinarian);

    // Assert
    EXPECT_EQ(container.getAll().size(), 1);
}

TEST(VeterinarianContainerGetTest, GetExistingVeterinarian) {
    // Arrange
    VeterinarianContainer container;
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");
    container.add(veterinarian);

    // Act
    Veterinarian* result = container.get(1);

    // Assert
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getName(), "Joao Silva");
}

TEST(VeterinarianContainerNextIdTest, EmptyContainer) {
    // Arrange
    VeterinarianContainer container;

    // Act
    int nextId = container.getNextId();

    // Assert
    EXPECT_EQ(nextId, 1);
}

TEST(VeterinarianContainerNextIdTest, NonEmptyContainer) {
    // Arrange
    VeterinarianContainer container;
    container.add(Veterinarian(1, "Joao Silva", 35, "Surgery"));
    container.add(Veterinarian(2, "Maria Costa", 40, "Dermatology"));

    // Act
    int nextId = container.getNextId();

    // Assert
    EXPECT_EQ(nextId, 3);
}