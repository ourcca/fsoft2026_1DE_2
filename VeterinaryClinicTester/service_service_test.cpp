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

TEST(ServiceServiceTest, AddValidService) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 1;
    dto.veterinarianId = 1;
    dto.requiresVeterinarianSpecialty = true;
    dto.requiredVeterinarianSpecialty = "Surgery";

    serviceService.addService(dto);

    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(ServiceServiceTest, AddServiceWithInvalidAnimalThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 99;
    dto.veterinarianId = 1;

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceTest, AddServiceWithInvalidVeterinarianThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 1;
    dto.veterinarianId = 99;

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}

TEST(ServiceServiceTest, GetServicesByVeterinarianId) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getAnimalContainer().add(
        Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(1, "Joao", 35, "Surgery")
    );

    clinic.getVeterinarianContainer().add(
        Veterinarian(2, "Maria", 40, "Dental")
    );

    ServiceInDTO dto1{};
    dto1.type = "Consultation";
    dto1.cost = 30.0f;
    dto1.date = "20/05/2026";
    dto1.time = "14:30";
    dto1.animalId = 1;
    dto1.veterinarianId = 1;
    dto1.requiresVeterinarianSpecialty = true;
    dto1.requiredVeterinarianSpecialty = "Surgery";

    ServiceInDTO dto2{};
    dto2.type = "Dental";
    dto2.cost = 40.0f;
    dto2.date = "21/05/2026";
    dto2.time = "15:00";
    dto2.animalId = 1;
    dto2.veterinarianId = 2;
    dto2.requiresVeterinarianSpecialty = true;
    dto2.requiredVeterinarianSpecialty = "Dental";

    serviceService.addService(dto1);
    serviceService.addService(dto2);

    std::vector<ServiceOutDTO> result = serviceService.getServicesByVeterinarianId(1);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].veterinarianId, 1);
    EXPECT_EQ(result[0].type, "Consultation");
}

TEST(ServiceServiceSpecialtyTest, AddServiceWithoutRequiredSpecialtyAndWithoutVetSpecialtySucceeds) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, ""));

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 1;
    dto.veterinarianId = 1;
    dto.requiresVeterinarianSpecialty = false;
    dto.requiredVeterinarianSpecialty = "";

    EXPECT_NO_THROW(serviceService.addService(dto));
    EXPECT_EQ(clinic.getServiceContainer().getAll().size(), 1);
}

TEST(ServiceServiceSpecialtyTest, AddServiceWithoutRequiredSpecialtyButWithSpecializedVetThrowsException) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    clinic.getAnimalContainer().add(Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4));
    clinic.getVeterinarianContainer().add(Veterinarian(1, "Joao", 35, "Surgery"));

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 1;
    dto.veterinarianId = 1;
    dto.requiresVeterinarianSpecialty = false;
    dto.requiredVeterinarianSpecialty = "";

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}