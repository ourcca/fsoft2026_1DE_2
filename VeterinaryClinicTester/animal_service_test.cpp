#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/AnimalService.h"
#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"
#include "exceptions/NoDataException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/DataConsistencyException.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

TEST(AnimalServiceTest, AddAnimal) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{};
    dto.name = "Rex";
    dto.species = "Dog";
    dto.breed = "Labrador";
    dto.weight = 20.5f;
    dto.age = 4;

    animalService.addAnimal(dto);

    EXPECT_EQ(clinic.getAnimalContainer().getAll().size(), 1);
}

TEST(AnimalServiceTest, GetAnimalByExistingId) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{};
    dto.name = "Rex";
    dto.species = "Dog";
    dto.breed = "Labrador";
    dto.weight = 20.5f;
    dto.age = 4;

    animalService.addAnimal(dto);

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.id, 1);
    EXPECT_EQ(result.name, "Rex");
    EXPECT_EQ(result.species, "Dog");
    EXPECT_EQ(result.breed, "Labrador");
    EXPECT_EQ(result.weight, 20.5f);
    EXPECT_EQ(result.age, 4);
}

TEST(AnimalServiceTest, GetAnimalByInvalidIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.getAnimalById(99), NoDataException);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithoutAssociatedRecordsSucceeds) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));

    EXPECT_NO_THROW(animalService.removeAnimal(1, false));
    EXPECT_EQ(clinic.getAnimalContainer().get(1), nullptr);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalInvalidIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.removeAnimal(0, false), InvalidDataException);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalNonExistingThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.removeAnimal(99, false), NoDataException);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithAssociatedServiceAndKeepRecordsThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, "Surgery"));

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(Service(
        1,
        "Surgery",
        50.0f,
        Date(20, 5, 2026),
        Time(14, 30),
        animal,
        vet
    ));

    EXPECT_THROW(animalService.removeAnimal(1, false), DataConsistencyException);
    EXPECT_NE(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithAssociatedPrescriptionAndKeepRecordsThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

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

    EXPECT_THROW(animalService.removeAnimal(1, false), DataConsistencyException);
    EXPECT_NE(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 1);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithAssociatedRecordsTrueRemovesEverything) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, "Surgery"));

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(Service(
        1,
        "Surgery",
        50.0f,
        Date(20, 5, 2026),
        Time(14, 30),
        animal,
        vet
    ));

    clinic.getPrescriptionContainer().add(Prescription(
        1,
        "Antibiotic",
        "2 pills/day",
        "7 days",
        animal,
        vet
    ));

    EXPECT_NO_THROW(animalService.removeAnimal(1, true));
    EXPECT_EQ(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 0);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 0);
}

TEST(AnimalServiceEditTest, EditExistingAnimalUpdatesData) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{"Rex", "Dog", "Labrador", 20.5f, 4};
    animalService.addAnimal(dto);

    AnimalInDTO editDto{"Luna", "Cat", "Siamese", 5.0f, 2};
    animalService.editAnimal(1, editDto);

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.name, "Luna");
    EXPECT_EQ(result.species, "Cat");
    EXPECT_EQ(result.breed, "Siamese");
    EXPECT_EQ(result.weight, 5.0f);
    EXPECT_EQ(result.age, 2);
}

TEST(AnimalServiceEditTest, EditAnimalInvalidIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{"Luna", "Cat", "Siamese", 5.0f, 2};

    EXPECT_THROW(animalService.editAnimal(0, dto), InvalidDataException);
}

TEST(AnimalServiceEditTest, EditAnimalNonExistingThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{"Luna", "Cat", "Siamese", 5.0f, 2};

    EXPECT_THROW(animalService.editAnimal(99, dto), NoDataException);
}

TEST(AnimalServiceEditTest, FailedEditDoesNotPartiallyModifyAnimal) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto{"Rex", "Dog", "Labrador", 20.5f, 4};
    animalService.addAnimal(dto);

    AnimalInDTO badDto{"Luna", "Cat", "Siamese", -1.0f, 2};

    EXPECT_THROW(animalService.editAnimal(1, badDto), InvalidDataException);

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.name, "Rex");
    EXPECT_EQ(result.species, "Dog");
    EXPECT_EQ(result.breed, "Labrador");
    EXPECT_EQ(result.weight, 20.5f);
    EXPECT_EQ(result.age, 4);
}