#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/AnimalService.h"
#include "exceptions/NoDataException.h"

TEST(AnimalServiceExceptionTest, GetAnimalByInvalidId) {
    Clinic clinic;
    AnimalService animalService(clinic);

    EXPECT_THROW(animalService.getAnimalById(99), NoDataException);
}