#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "services/PrescriptionService.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"
#include "exceptions/DataConsistencyException.h"

TEST(PrescriptionServiceTest, AddValidPrescription) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    PrescriptionInDTO dto{};
    dto.medication = "Antibiotic";
    dto.quantity = "2 pills/day";
    dto.duration = "7 days";
    dto.animalId = 1;
    dto.veterinarianId = 1;

    prescriptionService.addPrescription(dto);

    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 1);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithInvalidAnimalThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    PrescriptionInDTO dto{};
    dto.medication = "Antibiotic";
    dto.quantity = "2 pills/day";
    dto.duration = "7 days";
    dto.animalId = 99;
    dto.veterinarianId = 1;

    EXPECT_THROW(prescriptionService.addPrescription(dto), DataConsistencyException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithInvalidVeterinarianThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    PrescriptionInDTO dto{};
    dto.medication = "Antibiotic";
    dto.quantity = "2 pills/day";
    dto.duration = "7 days";
    dto.animalId = 1;
    dto.veterinarianId = 99;

    EXPECT_THROW(prescriptionService.addPrescription(dto), DataConsistencyException);
}

TEST(PrescriptionServiceTest, GetPrescriptionsByAnimalId) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    clinic.getAnimalContainer().add(
        Animal(2, "Mia", "Cat", "Persian", 5.0f, 2)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    PrescriptionInDTO dto1{};
    dto1.medication = "Antibiotic";
    dto1.quantity = "2 pills/day";
    dto1.duration = "7 days";
    dto1.animalId = 1;
    dto1.veterinarianId = 1;

    PrescriptionInDTO dto2{};
    dto2.medication = "Vitamin";
    dto2.quantity = "1 pill/day";
    dto2.duration = "10 days";
    dto2.animalId = 2;
    dto2.veterinarianId = 1;

    prescriptionService.addPrescription(dto1);
    prescriptionService.addPrescription(dto2);

    std::vector<PrescriptionOutDTO> result = prescriptionService.getPrescriptionsByAnimalId(1);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].animalId, 1);
    EXPECT_EQ(result[0].medication, "Antibiotic");
}