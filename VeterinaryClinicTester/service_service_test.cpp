#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/ServiceService.h"
#include "dto/ServiceInDTO.h"
#include "exceptions/DataConsistencyException.h"

TEST(ServiceServiceExceptionTest, AddServiceWithInvalidAnimalOrVeterinarian) {
    Clinic clinic;
    ServiceService serviceService(clinic);

    ServiceInDTO dto{};
    dto.type = "Consultation";
    dto.cost = 30.0f;
    dto.date = "20/05/2026";
    dto.time = "14:30";
    dto.animalId = 99;
    dto.veterinarianId = 99;

    EXPECT_THROW(serviceService.addService(dto), DataConsistencyException);
}