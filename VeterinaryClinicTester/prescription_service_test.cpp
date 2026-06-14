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

namespace {
    void addAnimal(Clinic& clinic, int id = 1) {
        clinic.getAnimalContainer().add(
            Animal(id, "Rex", "Cão", "Labrador", 20.5f, 4)
        );
    }

    void addVeterinarian(Clinic& clinic, int id = 1) {
        clinic.getVeterinarianContainer().add(
            Veterinarian(id, "Joao", 35, "Cirurgia")
        );
    }

    PrescriptionInDTO makePrescriptionDTO(
        const std::string& medication,
        const std::string& quantity,
        const std::string& duration,
        int animalId,
        int veterinarianId
    ) {
        PrescriptionInDTO dto{};
        dto.medication = medication;
        dto.quantity = quantity;
        dto.duration = duration;
        dto.animalId = animalId;
        dto.veterinarianId = veterinarianId;
        return dto;
    }
}

TEST(PrescriptionServiceTest, AddValidPrescription) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "7 dias",
        1,
        1
    );

    prescriptionService.addPrescription(dto);

    EXPECT_EQ(clinic.getPrescriptionContainer().getAll().size(), 1);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithInvalidAnimalIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "7 dias",
        0,
        1
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), InvalidDataException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithNonExistingAnimalThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "7 dias",
        99,
        1
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), DataConsistencyException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithInvalidVeterinarianIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "7 dias",
        1,
        0
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), InvalidDataException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithNonExistingVeterinarianThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "7 dias",
        1,
        99
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), DataConsistencyException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithUnknownMedicationThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Medicamento Inventado",
        "2 comprimidos/dia",
        "7 dias",
        1,
        1
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), InvalidDataException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithMedicationIgnoringSpacesCaseAndAccentsSucceeds) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "  amoxicilina  ",
        "2 comprimidos/dia",
        "7 dias",
        1,
        1
    );

    EXPECT_NO_THROW(prescriptionService.addPrescription(dto));
}

TEST(PrescriptionServiceTest, AddPrescriptionWithEmptyQuantityThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "   ",
        "7 dias",
        1,
        1
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), InvalidDataException);
}

TEST(PrescriptionServiceTest, AddPrescriptionWithEmptyDurationThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Amoxicilina",
        "2 comprimidos/dia",
        "   ",
        1,
        1
    );

    EXPECT_THROW(prescriptionService.addPrescription(dto), InvalidDataException);
}

TEST(PrescriptionServiceTest, GetPrescriptionByExistingId) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

    PrescriptionOutDTO result = prescriptionService.getPrescriptionById(1);

    EXPECT_EQ(result.id, 1);
    EXPECT_EQ(result.medication, "Amoxicilina");
    EXPECT_EQ(result.quantity, "2 comprimidos/dia");
    EXPECT_EQ(result.duration, "7 dias");
    EXPECT_EQ(result.animalId, 1);
    EXPECT_EQ(result.veterinarianId, 1);
}

TEST(PrescriptionServiceTest, GetPrescriptionByInvalidIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(prescriptionService.getPrescriptionById(0), InvalidDataException);
}

TEST(PrescriptionServiceTest, GetPrescriptionByNonExistingIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(prescriptionService.getPrescriptionById(99), NoDataException);
}

TEST(PrescriptionServiceTest, GetPrescriptionsByAnimalId) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);

    clinic.getAnimalContainer().add(
        Animal(2, "Mia", "Gato", "Siamês", 5.0f, 2)
    );

    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

    prescriptionService.addPrescription(
        makePrescriptionDTO("Cefalexina", "1 comprimido/dia", "10 dias", 2, 1)
    );

    std::vector<PrescriptionOutDTO> result =
        prescriptionService.getPrescriptionsByAnimalId(1);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].animalId, 1);
    EXPECT_EQ(result[0].medication, "Amoxicilina");
}

TEST(PrescriptionServiceTest, GetPrescriptionsByInvalidAnimalIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(
        prescriptionService.getPrescriptionsByAnimalId(0),
        InvalidDataException
    );
}

TEST(PrescriptionServiceTest, GetPrescriptionsByNonExistingAnimalIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    EXPECT_THROW(
        prescriptionService.getPrescriptionsByAnimalId(99),
        NoDataException
    );
}

TEST(PrescriptionServiceRemoveTest, RemoveExistingPrescription) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

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

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

    PrescriptionInDTO editDto = makePrescriptionDTO(
        "Cefalexina",
        "1 comprimido/dia",
        "10 dias",
        1,
        1
    );

    prescriptionService.editPrescription(1, editDto);

    PrescriptionOutDTO result = prescriptionService.getPrescriptionById(1);

    EXPECT_EQ(result.medication, "Cefalexina");
    EXPECT_EQ(result.quantity, "1 comprimido/dia");
    EXPECT_EQ(result.duration, "10 dias");
}

TEST(PrescriptionServiceEditTest, EditPrescriptionInvalidIdThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    PrescriptionInDTO dto{};

    EXPECT_THROW(prescriptionService.editPrescription(0, dto), InvalidDataException);
}

TEST(PrescriptionServiceEditTest, EditPrescriptionNonExistingThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    PrescriptionInDTO dto = makePrescriptionDTO(
        "Cefalexina",
        "1 comprimido/dia",
        "10 dias",
        1,
        1
    );

    EXPECT_THROW(prescriptionService.editPrescription(99, dto), NoDataException);
}

TEST(PrescriptionServiceEditTest, EditPrescriptionWithNonExistingAnimalThrowsException) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

    PrescriptionInDTO editDto = makePrescriptionDTO(
        "Cefalexina",
        "1 comprimido/dia",
        "10 dias",
        99,
        1
    );

    EXPECT_THROW(
        prescriptionService.editPrescription(1, editDto),
        DataConsistencyException
    );
}

TEST(PrescriptionServiceEditTest, FailedEditDoesNotPartiallyModifyPrescription) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    addAnimal(clinic, 1);
    addVeterinarian(clinic, 1);

    prescriptionService.addPrescription(
        makePrescriptionDTO("Amoxicilina", "2 comprimidos/dia", "7 dias", 1, 1)
    );

    PrescriptionInDTO badDto = makePrescriptionDTO(
        "Cefalexina",
        "   ",
        "10 dias",
        1,
        1
    );

    EXPECT_THROW(
        prescriptionService.editPrescription(1, badDto),
        InvalidDataException
    );

    PrescriptionOutDTO result = prescriptionService.getPrescriptionById(1);

    EXPECT_EQ(result.medication, "Amoxicilina");
    EXPECT_EQ(result.quantity, "2 comprimidos/dia");
    EXPECT_EQ(result.duration, "7 dias");
}