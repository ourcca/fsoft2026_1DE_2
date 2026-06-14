#include "gtest/gtest.h"

#include "model/Prescription.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "exceptions/InvalidDataException.h"

TEST(PrescriptionConstructorTest, ValidPrescription) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Prescription prescription(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian);

    EXPECT_EQ(prescription.getId(), 1);
    EXPECT_EQ(prescription.getMedication(), "Antibiotic");
    EXPECT_EQ(prescription.getQuantity(), "2 pills/day");
    EXPECT_EQ(prescription.getDuration(), "7 days");
    EXPECT_EQ(prescription.getAnimal(), &animal);
    EXPECT_EQ(prescription.getVeterinarian(), &veterinarian);
}

TEST(PrescriptionOperatorEqualTest, EqualPrescriptions) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Prescription prescription1(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian);
    Prescription prescription2(1, "Vitamin", "1 pill/day", "10 days", &animal, &veterinarian);

    EXPECT_TRUE(prescription1 == prescription2);
}

TEST(PrescriptionOperatorEqualTest, DifferentPrescriptions) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Prescription prescription1(1, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian);
    Prescription prescription2(2, "Vitamin", "1 pill/day", "10 days", &animal, &veterinarian);

    EXPECT_FALSE(prescription1 == prescription2);
}

TEST(PrescriptionValidationTest, InvalidPrescriptionFieldsThrowException) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5f, 4);
    Veterinarian veterinarian(1, "Joao", 35, "Surgery");

    EXPECT_THROW(Prescription(0, "Antibiotic", "2 pills/day", "7 days", &animal, &veterinarian), InvalidDataException);
    EXPECT_THROW(Prescription(1, " ", "2 pills/day", "7 days", &animal, &veterinarian), InvalidDataException);
    EXPECT_THROW(Prescription(1, "Antibiotic", " ", "7 days", &animal, &veterinarian), InvalidDataException);
    EXPECT_THROW(Prescription(1, "Antibiotic", "2 pills/day", " ", &animal, &veterinarian), InvalidDataException);
    EXPECT_THROW(Prescription(1, "Antibiotic", "2 pills/day", "7 days", nullptr, &veterinarian), InvalidDataException);
    EXPECT_THROW(Prescription(1, "Antibiotic", "2 pills/day", "7 days", &animal, nullptr), InvalidDataException);
}

TEST(PrescriptionValidationTest, TextFieldsAreTrimmed) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5f, 4);
    Veterinarian veterinarian(1, "Joao", 35, "Surgery");

    Prescription prescription(
        1,
        " Antibiotic ",
        " 2 pills/day ",
        " 7 days ",
        &animal,
        &veterinarian
    );

    EXPECT_EQ(prescription.getMedication(), "Antibiotic");
    EXPECT_EQ(prescription.getQuantity(), "2 pills/day");
    EXPECT_EQ(prescription.getDuration(), "7 days");
}