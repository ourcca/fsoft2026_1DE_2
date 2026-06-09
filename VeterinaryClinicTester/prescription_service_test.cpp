#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/PrescriptionService.h"
#include "dto/PrescriptionInDTO.h"
#include "exceptions/DataConsistencyException.h"

TEST(PrescriptionServiceExceptionTest, AddPrescriptionWithInvalidAnimalOrVeterinarian) {
    Clinic clinic;
    PrescriptionService prescriptionService(clinic);

    PrescriptionInDTO dto{};
    dto.medication = "Antibiotic";
    dto.quantity = "2 pills/day";
    dto.duration = "7 days";
    dto.animalId = 99;
    dto.veterinarianId = 99;

    EXPECT_THROW(prescriptionService.addPrescription(dto), DataConsistencyException);
}