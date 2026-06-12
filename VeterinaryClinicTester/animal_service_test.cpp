#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/AnimalService.h"
#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"
#include "exceptions/NoDataException.h"

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