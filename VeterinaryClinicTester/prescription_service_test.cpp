#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "services/PrescriptionService.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"
#include "exceptions/DataConsistencyException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"

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

TEST(PrescriptionServiceRemoveTest, RemoveExistingPrescription) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, "Surgery"));

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getPrescriptionContainer().add(Prescription(
        1,
        "Antibiotic",
        "2 pills/day",
        "7 days",
        animal,
        vet
    ));

    EXPECT_NO_THROW(prescriptionService.removePrescription(1));
    EXPECT_EQ(clinic.getPrescriptionContainer().get(1), nullptr);
}

TEST(PrescriptionServiceRemoveTest, RemovePrescriptionInvalidIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(prescriptionService.removePrescription(0), InvalidDataException);
}

TEST(PrescriptionServiceRemoveTest, RemovePrescriptionNonExistingThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(prescriptionService.removePrescription(99), NoDataException);
}

TEST(PrescriptionServiceEditTest, EditExistingPrescriptionUpdatesData) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, "Surgery"));

    PrescriptionInDTO dto{};
    dto.medication = "Antibiotic";
    dto.quantity = "2 pills/day";
    dto.duration = "7 days";
    dto.animalId = 1;
    dto.veterinarianId = 1;

    prescriptionService.addPrescription(dto);

    PrescriptionInDTO editDto{};
    editDto.medication = "Vitamin";
    editDto.quantity = "1 pill/day";
    editDto.duration = "10 days";
    editDto.animalId = 1;
    editDto.veterinarianId = 1;

    prescriptionService.editPrescription(1, editDto);

    PrescriptionOutDTO result = prescriptionService.getPrescriptionById(1);

    EXPECT_EQ(result.medication, "Vitamin");
    EXPECT_EQ(result.quantity, "1 pill/day");
    EXPECT_EQ(result.duration, "10 days");
}