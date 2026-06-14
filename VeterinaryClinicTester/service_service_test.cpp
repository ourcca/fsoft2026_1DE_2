#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "services/ServiceService.h"
#include "dto/ServiceInDTO.h"
#include "dto/ServiceOutDTO.h"
#include "exceptions/DataConsistencyException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"

namespace {
    void addDog(Clinic& clinic, int id = 1) {
        clinic.getAnimalContainer().add(
            Animal(id, "Rex", "Cão", "Labrador", 20.5f, 4)
        );
    }

    void addCat(Clinic& clinic, int id = 2) {
        clinic.getAnimalContainer().add(
            Animal(id, "Mia", "Gato", "Siamês", 5.0f, 2)
        );
    }

    void addExoticAnimal(Clinic& clinic, int id = 3) {
        clinic.getAnimalContainer().add(
            Animal(id, "Kaa", "Cobra", "", 3.0f, 2)
        );
    }

    ServiceInDTO makeServiceDTO(
        const std::string& type,
        float cost,
        const std::string& date,
        const std::string& time,
        int animalId,
        int veterinarianId
    ) {
        ServiceInDTO dto{};
        dto.type = type;
        dto.cost = cost;
        dto.date = date;
        dto.time = time;
        dto.animalId = animalId;
        dto.veterinarianId = veterinarianId;
        return dto;
    }
}

TEST(ServiceServiceTest, AddValidServiceWithoutRequiredSpecialty) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(ServiceServiceTest, AddValidServiceWithRequiredSpecialty) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Cirurgia",
        50.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(ServiceServiceTest, AddServiceWithInvalidAnimalThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        99,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceTest, AddServiceWithInvalidVeterinarianThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        99
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceTest, AddServiceWithInvalidAnimalIdThrowsInvalidDataException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        0,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceTest, AddServiceWithInvalidVeterinarianIdThrowsInvalidDataException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        0
    );

    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceTest, GetServiceByExistingId) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    serviceService.addService(
        makeServiceDTO("Consulta Geral", 30.0f, "20/05/2026", "14:30", 1, 1)
    );

    ServiceOutDTO result = serviceService.getServiceById(1);

    EXPECT_EQ(result.id, 1);
    EXPECT_EQ(result.type, "Consulta Geral");
    EXPECT_EQ(result.cost, 30.0f);
    EXPECT_EQ(result.date, "20/5/2026");
    EXPECT_EQ(result.time, "14:30");
    EXPECT_EQ(result.animalId, 1);
    EXPECT_EQ(result.veterinarianId, 1);
}

TEST(ServiceServiceTest, GetServiceByInvalidIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(serviceService.getServiceById(0), InvalidDataException);
}

TEST(ServiceServiceTest, GetServiceByNonExistingIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(serviceService.getServiceById(99), NoDataException);
}

TEST(ServiceServiceTest, GetServicesByVeterinarianId) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);
    addCat(clinic, 2);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(2, "Maria", 40, "Odontologia")
    );

    ServiceInDTO dto1 = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    ServiceInDTO dto2 = makeServiceDTO(
        "Destartarização",
        40.0f,
        "21/05/2026",
        "15:00",
        2,
        2
    );

    serviceService.addService(dto1);
    serviceService.addService(dto2);

    std::vector<ServiceOutDTO> result =
        serviceService.getServicesByVeterinarianId(1);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].veterinarianId, 1);
    EXPECT_EQ(result[0].type, "Consulta Geral");
}

TEST(ServiceServiceTest, GetServicesByInvalidVeterinarianIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(
        serviceService.getServicesByVeterinarianId(0),
        InvalidDataException
    );
}

TEST(ServiceServiceTest, GetServicesByNonExistingVeterinarianIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(
        serviceService.getServicesByVeterinarianId(99),
        NoDataException
    );
}

TEST(ServiceServiceSpecialtyTest, ServiceWithoutRequiredSpecialtyAndWithoutVetSpecialtySucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Vacinação",
        20.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
}

TEST(ServiceServiceSpecialtyTest, ServiceWithoutRequiredSpecialtyButWithSpecializedVetThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceSpecialtyTest, ServiceWithMatchingRequiredSpecialtySucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Cirurgia",
        50.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
}

TEST(ServiceServiceSpecialtyTest, ServiceWithDifferentRequiredSpecialtyThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Cirurgia")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Destartarização",
        40.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceSpecialtyTest, RequiredSpecialtyComparisonIgnoresSpacesCaseAndAccents) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "  cirurgia  ")
    );

    ServiceInDTO dto = makeServiceDTO(
        "  cirurgia  ",
        50.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
}

TEST(ServiceServiceSpecialtyTest, ServiceThatRequiresSpecialtyWithVetWithoutSpecialtyThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Cirurgia",
        50.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceAnimalRuleTest, ExoticServiceWithExoticAnimalSucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addExoticAnimal(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Maria", 40, "Animais Exóticos")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta de Animais Exóticos",
        60.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
}

TEST(ServiceServiceAnimalRuleTest, ExoticServiceWithCommonPetThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Maria", 40, "Animais Exóticos")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta de Animais Exóticos",
        60.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceValidationTest, EmptyServiceTypeThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "   ",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceValidationTest, UnknownServiceTypeThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Banho",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceValidationTest, InvalidCostThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        0.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceParsingTest, ValidDateAndTimeWithSpacesSucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        " 20/05/2026 ",
        " 14:30 ",
        1,
        1
    );

    EXPECT_NO_THROW(serviceService.addService(dto));
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(ServiceServiceParsingTest, InvalidDateOrTimeFormatThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20-05-2026",
        "14:30",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026abc",
        "14:30",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "31/02/2026",
        "14:30",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14h30",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30abc",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "25:00",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);

    dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "10:99",
        1,
        1
    );
    EXPECT_THROW(serviceService.addService(dto), InvalidDataException);
}

TEST(ServiceServiceGetAllTest, GetAllServicesOnEmptyClinicReturnsEmptyVector) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    std::vector<ServiceOutDTO> result = serviceService.getAllServices();

    EXPECT_TRUE(result.empty());
}

TEST(ServiceServiceGetAllTest, GetAllServicesReturnsAllServices) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);
    addCat(clinic, 2);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(2, "Maria", 40, "Cirurgia")
    );

    ServiceInDTO dto1 = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    ServiceInDTO dto2 = makeServiceDTO(
        "Cirurgia",
        50.0f,
        "21/05/2026",
        "15:30",
        2,
        2
    );

    serviceService.addService(dto1);
    serviceService.addService(dto2);

    std::vector<ServiceOutDTO> result = serviceService.getAllServices();

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0].id, 1);
    EXPECT_EQ(result[0].type, "Consulta Geral");
    EXPECT_EQ(result[0].cost, 30.0f);
    EXPECT_EQ(result[0].animalId, 1);
    EXPECT_EQ(result[0].veterinarianId, 1);

    EXPECT_EQ(result[1].id, 2);
    EXPECT_EQ(result[1].type, "Cirurgia");
    EXPECT_EQ(result[1].cost, 50.0f);
    EXPECT_EQ(result[1].animalId, 2);
    EXPECT_EQ(result[1].veterinarianId, 2);
}

TEST(ServiceServiceRemoveTest, RemoveExistingServiceSucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    serviceService.addService(dto);

    EXPECT_NO_THROW(serviceService.removeService(1));

    EXPECT_EQ(clinic.getServiceContainer().get(1), nullptr);
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 0);
}

TEST(ServiceServiceRemoveTest, RemoveServiceInvalidIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(
        serviceService.removeService(0),
        InvalidDataException
    );
}

TEST(ServiceServiceRemoveTest, RemoveServiceNonExistingIdThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    EXPECT_THROW(
        serviceService.removeService(99),
        NoDataException
    );
}

TEST(ServiceServiceRemoveTest, RemoveServiceDoesNotRemoveAnimalOrVeterinarian) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    addDog(clinic, 1);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "")
    );

    ServiceInDTO dto = makeServiceDTO(
        "Consulta Geral",
        30.0f,
        "20/05/2026",
        "14:30",
        1,
        1
    );

    serviceService.addService(dto);

    EXPECT_NO_THROW(serviceService.removeService(1));

    EXPECT_EQ(clinic.getServiceContainer().get(1), nullptr);

    EXPECT_NE(clinic.getAnimalContainer().get(1), nullptr);
    EXPECT_NE(clinic.getVeterinarianContainer().get(1), nullptr);

    EXPECT_EQ(clinic.getAnimalContainer().getAll().size(), 1);
    EXPECT_EQ(clinic.getVeterinarianContainer().getAll().size(), 1);
}