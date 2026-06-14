#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

#include "services/AnimalService.h"

#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"

#include "exceptions/NoDataException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/DataConsistencyException.h"

namespace {
    AnimalInDTO makeAnimalDTO(
        const std::string& name,
        const std::string& species,
        const std::string& breed,
        float weight,
        int age
    ) {
        AnimalInDTO dto{};
        dto.name = name;
        dto.species = species;
        dto.breed = breed;
        dto.weight = weight;
        dto.age = age;
        return dto;
    }
}

TEST(AnimalServiceTest, AddValidCommonAnimal) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        4
    );

    animalService.addAnimal(dto);

    EXPECT_EQ(clinic.getAnimalContainer().getAll().size(), 1);

    Animal* animal = clinic.getAnimalContainer().get(1);

    ASSERT_NE(animal, nullptr);
    EXPECT_EQ(animal->getName(), "Rex");
    EXPECT_EQ(animal->getSpecies(), "Cão");
    EXPECT_EQ(animal->getBreed(), "Labrador");
}

TEST(AnimalServiceTest, AddValidExoticAnimalWithoutBreed) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Kaa",
        "Cobra",
        "",
        3.0f,
        2
    );

    animalService.addAnimal(dto);

    EXPECT_EQ(clinic.getAnimalContainer().getAll().size(), 1);

    Animal* animal = clinic.getAnimalContainer().get(1);

    ASSERT_NE(animal, nullptr);
    EXPECT_EQ(animal->getSpecies(), "Cobra");
    EXPECT_EQ(animal->getBreed(), "");
}

TEST(AnimalServiceTest, AddAnimalWithInvalidSpeciesThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Dinossauro",
        "",
        20.5f,
        4
    );

    EXPECT_THROW(animalService.addAnimal(dto), InvalidDataException);
}

TEST(AnimalServiceTest, AddCommonAnimalWithoutBreedThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "",
        20.5f,
        4
    );

    EXPECT_THROW(animalService.addAnimal(dto), InvalidDataException);
}

TEST(AnimalServiceTest, AddExoticAnimalWithBreedThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Kaa",
        "Cobra",
        "Píton",
        3.0f,
        2
    );

    EXPECT_THROW(animalService.addAnimal(dto), InvalidDataException);
}

TEST(AnimalServiceTest, AddAnimalWithInvalidWeightThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        0.0f,
        4
    );

    EXPECT_THROW(animalService.addAnimal(dto), InvalidDataException);
}

TEST(AnimalServiceTest, AddAnimalWithInvalidAgeThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        -1
    );

    EXPECT_THROW(animalService.addAnimal(dto), InvalidDataException);
}

TEST(AnimalServiceTest, GetAnimalByExistingId) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        4
    );

    animalService.addAnimal(dto);

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.id, 1);
    EXPECT_EQ(result.name, "Rex");
    EXPECT_EQ(result.species, "Cão");
    EXPECT_EQ(result.breed, "Labrador");
    EXPECT_EQ(result.weight, 20.5f);
    EXPECT_EQ(result.age, 4);
}

TEST(AnimalServiceTest, GetAnimalByInvalidIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.getAnimalById(0), InvalidDataException);
}

TEST(AnimalServiceTest, GetAnimalByNonExistingIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.getAnimalById(99), NoDataException);
}

TEST(AnimalServiceTest, GetAllAnimalsReturnsAllAnimals) {
    Clinic clinic;
    AnimalService animalService(clinic);

    animalService.addAnimal(
        makeAnimalDTO("Rex", "Cão", "Labrador", 20.5f, 4)
    );

    animalService.addAnimal(
        makeAnimalDTO("Mia", "Gato", "Siamês", 5.0f, 2)
    );

    std::vector<AnimalOutDTO> result = animalService.getAllAnimals();

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].name, "Rex");
    EXPECT_EQ(result[1].name, "Mia");
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithoutAssociatedRecordsSucceeds) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
    );

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

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(
        Service(
            1,
            "Consulta Geral",
            30.0f,
            Date(20, 5, 2026),
            Time(14, 30),
            animal,
            vet
        )
    );

    EXPECT_THROW(
        animalService.removeAnimal(1, false),
        DataConsistencyException
    );

    EXPECT_NE(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithAssociatedPrescriptionAndKeepRecordsThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getPrescriptionContainer().add(
        Prescription(
            1,
            "Amoxicilina",
            "2 comprimidos/dia",
            "7 dias",
            animal,
            vet
        )
    );

    EXPECT_THROW(
        animalService.removeAnimal(1, false),
        DataConsistencyException
    );

    EXPECT_NE(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 1);
}

TEST(AnimalServiceRemoveTest, RemoveAnimalWithAssociatedRecordsTrueRemovesEverything) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(
        Service(
            1,
            "Consulta Geral",
            30.0f,
            Date(20, 5, 2026),
            Time(14, 30),
            animal,
            vet
        )
    );

    clinic.getPrescriptionContainer().add(
        Prescription(
            1,
            "Amoxicilina",
            "2 comprimidos/dia",
            "7 dias",
            animal,
            vet
        )
    );

    EXPECT_NO_THROW(animalService.removeAnimal(1, true));

    EXPECT_EQ(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 0);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 0);
}

TEST(AnimalServiceEditTest, EditExistingAnimalUpdatesData) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        4
    );

    animalService.addAnimal(dto);

    AnimalInDTO editDto = makeAnimalDTO(
        "Mia",
        "Gato",
        "Siamês",
        5.0f,
        2
    );

    animalService.editAnimal(1, editDto);

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.name, "Mia");
    EXPECT_EQ(result.species, "Gato");
    EXPECT_EQ(result.breed, "Siamês");
    EXPECT_EQ(result.weight, 5.0f);
    EXPECT_EQ(result.age, 2);
}

TEST(AnimalServiceEditTest, EditAnimalInvalidIdThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Mia",
        "Gato",
        "Siamês",
        5.0f,
        2
    );

    EXPECT_THROW(animalService.editAnimal(0, dto), InvalidDataException);
}

TEST(AnimalServiceEditTest, EditAnimalNonExistingThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Mia",
        "Gato",
        "Siamês",
        5.0f,
        2
    );

    EXPECT_THROW(animalService.editAnimal(99, dto), NoDataException);
}

TEST(AnimalServiceEditTest, FailedEditDoesNotPartiallyModifyAnimal) {
    Clinic clinic;
    AnimalService animalService(clinic);

    AnimalInDTO dto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        4
    );

    animalService.addAnimal(dto);

    AnimalInDTO badDto = makeAnimalDTO(
        "Mia",
        "Gato",
        "Siamês",
        -1.0f,
        2
    );

    EXPECT_THROW(
        animalService.editAnimal(1, badDto),
        InvalidDataException
    );

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.name, "Rex");
    EXPECT_EQ(result.species, "Cão");
    EXPECT_EQ(result.breed, "Labrador");
    EXPECT_EQ(result.weight, 20.5f);
    EXPECT_EQ(result.age, 4);
}

TEST(AnimalServiceEditTest, EditExoticAnimalWithExoticServiceToCommonAnimalThrowsException) {
    Clinic clinic;
    AnimalService animalService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Kaa", "Cobra", "", 3.0f, 2)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Maria", 40, "Animais Exóticos")
    );

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(
        Service(
            1,
            "Consulta de Animais Exóticos",
            60.0f,
            Date(20, 5, 2026),
            Time(14, 30),
            animal,
            vet
        )
    );

    AnimalInDTO editDto = makeAnimalDTO(
        "Rex",
        "Cão",
        "Labrador",
        20.5f,
        4
    );

    EXPECT_THROW(
        animalService.editAnimal(1, editDto),
        DataConsistencyException
    );

    AnimalOutDTO result = animalService.getAnimalById(1);

    EXPECT_EQ(result.species, "Cobra");
    EXPECT_EQ(result.breed, "");
}