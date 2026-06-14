#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

#include "services/VeterinarianService.h"

#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"

#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"
#include "exceptions/DataConsistencyException.h"

namespace {
    VeterinarianInDTO makeVeterinarianDTO(
        const std::string& name,
        int age,
        const std::string& specialty
    ) {
        VeterinarianInDTO dto{};
        dto.name = name;
        dto.age = age;
        dto.specialty = specialty;
        return dto;
    }
}

TEST(VeterinarianServiceTest, AddVeterinarianWithSpecialty) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        35,
        "Cirurgia"
    );

    veterinarianService.addVeterinarian(dto);

    EXPECT_EQ(clinic.getVeterinarianContainer().getAll().size(), 1);

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(1);

    ASSERT_NE(veterinarian, nullptr);
    EXPECT_EQ(veterinarian->getName(), "Joao");
    EXPECT_EQ(veterinarian->getSpecialty(), "Cirurgia");
}

TEST(VeterinarianServiceTest, AddVeterinarianWithoutSpecialty) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        35,
        ""
    );

    EXPECT_NO_THROW(veterinarianService.addVeterinarian(dto));
    EXPECT_EQ(clinic.getVeterinarianContainer().getAll().size(), 1);
}

TEST(VeterinarianServiceTest, AddVeterinarianWithInvalidNameThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "   ",
        35,
        "Cirurgia"
    );

    EXPECT_THROW(veterinarianService.addVeterinarian(dto), InvalidDataException);
}

TEST(VeterinarianServiceTest, AddVeterinarianWithTooLowAgeThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        17,
        "Cirurgia"
    );

    EXPECT_THROW(veterinarianService.addVeterinarian(dto), InvalidDataException);
}

TEST(VeterinarianServiceTest, AddVeterinarianWithTooHighAgeThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        71,
        "Cirurgia"
    );

    EXPECT_THROW(veterinarianService.addVeterinarian(dto), InvalidDataException);
}

TEST(VeterinarianServiceTest, AddVeterinarianWithInvalidSpecialtyThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        35,
        "Neurologia"
    );

    EXPECT_THROW(veterinarianService.addVeterinarian(dto), InvalidDataException);
}

TEST(VeterinarianServiceTest, AddVeterinarianSpecialtyIgnoresSpacesCaseAndAccents) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Joao",
        35,
        "  cirurgia  "
    );

    EXPECT_NO_THROW(veterinarianService.addVeterinarian(dto));

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.specialty, "cirurgia");
}

TEST(VeterinarianServiceTest, GetAllVeterinarians) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    veterinarianService.addVeterinarian(
        makeVeterinarianDTO("Joao", 35, "Cirurgia")
    );

    veterinarianService.addVeterinarian(
        makeVeterinarianDTO("Maria", 40, "Odontologia")
    );

    std::vector<VeterinarianOutDTO> result =
        veterinarianService.getAllVeterinarians();

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].name, "Joao");
    EXPECT_EQ(result[1].name, "Maria");
}

TEST(VeterinarianServiceTest, GetVeterinarianByExistingId) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    veterinarianService.addVeterinarian(
        makeVeterinarianDTO("Joao", 35, "Cirurgia")
    );

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.id, 1);
    EXPECT_EQ(result.name, "Joao");
    EXPECT_EQ(result.age, 35);
    EXPECT_EQ(result.specialty, "Cirurgia");
}

TEST(VeterinarianServiceTest, GetVeterinarianByInvalidIdThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    EXPECT_THROW(veterinarianService.getVeterinarianById(0), InvalidDataException);
}

TEST(VeterinarianServiceTest, GetVeterinarianByNonExistingIdThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    EXPECT_THROW(veterinarianService.getVeterinarianById(99), NoDataException);
}

TEST(VeterinarianServiceEditTest, EditExistingVeterinarianUpdatesData) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    veterinarianService.addVeterinarian(
        makeVeterinarianDTO("Joao", 35, "Cirurgia")
    );

    VeterinarianInDTO editDto = makeVeterinarianDTO(
        "Maria",
        40,
        "Odontologia"
    );

    veterinarianService.editVeterinarian(1, editDto);

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.name, "Maria");
    EXPECT_EQ(result.age, 40);
    EXPECT_EQ(result.specialty, "Odontologia");
}

TEST(VeterinarianServiceEditTest, EditVeterinarianInvalidIdThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto{};

    EXPECT_THROW(veterinarianService.editVeterinarian(0, dto), InvalidDataException);
}

TEST(VeterinarianServiceEditTest, EditVeterinarianNonExistingThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto = makeVeterinarianDTO(
        "Maria",
        40,
        "Odontologia"
    );

    EXPECT_THROW(veterinarianService.editVeterinarian(99, dto), NoDataException);
}

TEST(VeterinarianServiceEditTest, FailedEditDoesNotPartiallyModifyVeterinarian) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    veterinarianService.addVeterinarian(
        makeVeterinarianDTO("Joao", 35, "Cirurgia")
    );

    VeterinarianInDTO badDto = makeVeterinarianDTO(
        "Maria",
        17,
        "Odontologia"
    );

    EXPECT_THROW(
        veterinarianService.editVeterinarian(1, badDto),
        InvalidDataException
    );

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.name, "Joao");
    EXPECT_EQ(result.age, 35);
    EXPECT_EQ(result.specialty, "Cirurgia");
}

TEST(VeterinarianServiceEditTest, EditVeterinarianWithGeneralServiceToSpecializedThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

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

    VeterinarianInDTO editDto = makeVeterinarianDTO(
        "Joao",
        35,
        "Cirurgia"
    );

    EXPECT_THROW(
        veterinarianService.editVeterinarian(1, editDto),
        DataConsistencyException
    );
}

TEST(VeterinarianServiceEditTest, EditVeterinarianWithSpecialtyServiceToWrongSpecialtyThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    Animal* animal = clinic.getAnimalContainer().get(1);
    Veterinarian* vet = clinic.getVeterinarianContainer().get(1);

    clinic.getServiceContainer().add(
        Service(
            1,
            "Cirurgia",
            50.0f,
            Date(20, 5, 2026),
            Time(14, 30),
            animal,
            vet
        )
    );

    VeterinarianInDTO editDto = makeVeterinarianDTO(
        "Joao",
        35,
        "Odontologia"
    );

    EXPECT_THROW(
        veterinarianService.editVeterinarian(1, editDto),
        DataConsistencyException
    );
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianWithoutAssociatedRecordsSucceeds) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    EXPECT_NO_THROW(veterinarianService.removeVeterinarian(1, false));
    EXPECT_EQ(clinic.getVeterinarianContainer().get(1), nullptr);
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianInvalidIdThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    EXPECT_THROW(veterinarianService.removeVeterinarian(0, false), InvalidDataException);
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianNonExistingThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    EXPECT_THROW(veterinarianService.removeVeterinarian(99, false), NoDataException);
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianWithAssociatedServiceAndKeepRecordsThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

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
        veterinarianService.removeVeterinarian(1, false),
        DataConsistencyException
    );

    EXPECT_NE(clinic.getVeterinarianContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianWithAssociatedPrescriptionAndKeepRecordsThrowsException) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

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
        veterinarianService.removeVeterinarian(1, false),
        DataConsistencyException
    );

    EXPECT_NE(clinic.getVeterinarianContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 1);
}

TEST(VeterinarianServiceRemoveTest, RemoveVeterinarianWithAssociatedRecordsTrueRemovesEverything) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

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

    EXPECT_NO_THROW(veterinarianService.removeVeterinarian(1, true));

    EXPECT_EQ(clinic.getVeterinarianContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 0);
    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 0);
}