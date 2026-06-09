#include "gtest/gtest.h"

#include "model/PrescriptionContainer.h"
#include "model/Prescription.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"

TEST(PrescriptionContainerAddTest, AddPrescription) {
    PrescriptionContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Prescription prescription(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian);

    container.add(prescription);

    EXPECT_EQ(container.getAll().size(), 1);
}

TEST(PrescriptionContainerGetTest, GetExistingPrescription) {
    PrescriptionContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Prescription prescription(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian);
    container.add(prescription);

    Prescription* result = container.get(1);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getMedication(), "Antibiotic");
    EXPECT_EQ(result->getAnimal(), &animal);
    EXPECT_EQ(result->getVeterinarian(), &veterinarian);
}

TEST(PrescriptionContainerGetTest, GetNonExistingPrescription) {
    PrescriptionContainer container;

    Prescription* result = container.get(99);

    EXPECT_EQ(result, nullptr);
}

TEST(PrescriptionContainerNextIdTest, EmptyContainer) {
    PrescriptionContainer container;

    int nextId = container.getNextId();

    EXPECT_EQ(nextId, 1);
}

TEST(PrescriptionContainerNextIdTest, NonEmptyContainer) {
    PrescriptionContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    container.add(Prescription(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian));
    container.add(Prescription(2, "Vitamin", "1 pill/day", "10 days", &animal, &veterinarian));

    int nextId = container.getNextId();

    EXPECT_EQ(nextId, 3);
}
