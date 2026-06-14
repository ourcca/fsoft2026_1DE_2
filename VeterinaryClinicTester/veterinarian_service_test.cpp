#include "gtest/gtest.h"

#include "model/Clinic.h"
#include "services/VeterinarianService.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"

TEST(VeterinarianServiceTest, AddVeterinarian) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto{};
    dto.name = "Joao";
    dto.age = 35;
    dto.specialty = "Surgery";

    veterinarianService.addVeterinarian(dto);

    EXPECT_EQ(clinic.getVeterinarianContainer().getAll().size(), 1);
}

TEST(VeterinarianServiceTest, GetAllVeterinarians) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto1{};
    dto1.name = "Joao";
    dto1.age = 35;
    dto1.specialty = "Surgery";

    VeterinarianInDTO dto2{};
    dto2.name = "Maria";
    dto2.age = 40;
    dto2.specialty = "Dental";

    veterinarianService.addVeterinarian(dto1);
    veterinarianService.addVeterinarian(dto2);

    std::vector<VeterinarianOutDTO> result = veterinarianService.getAllVeterinarians();

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0].id, 1);
    EXPECT_EQ(result[0].name, "Joao");
    EXPECT_EQ(result[0].age, 35);
    EXPECT_EQ(result[0].specialty, "Surgery");

    EXPECT_EQ(result[1].id, 2);
    EXPECT_EQ(result[1].name, "Maria");
    EXPECT_EQ(result[1].age, 40);
    EXPECT_EQ(result[1].specialty, "Dental");
}

TEST(VeterinarianServiceEditTest, EditExistingVeterinarianUpdatesData) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto{};
    dto.name = "Joao";
    dto.age = 35;
    dto.specialty = "Surgery";

    veterinarianService.addVeterinarian(dto);

    VeterinarianInDTO editDto{};
    editDto.name = "Maria";
    editDto.age = 40;
    editDto.specialty = "Dental";

    veterinarianService.editVeterinarian(1, editDto);

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.name, "Maria");
    EXPECT_EQ(result.age, 40);
    EXPECT_EQ(result.specialty, "Dental");
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

    VeterinarianInDTO dto{};
    dto.name = "Maria";
    dto.age = 40;
    dto.specialty = "Dental";

    EXPECT_THROW(veterinarianService.editVeterinarian(99, dto), NoDataException);
}

TEST(VeterinarianServiceEditTest, FailedEditDoesNotPartiallyModifyVeterinarian) {
    Clinic clinic;
    VeterinarianService veterinarianService(clinic);

    VeterinarianInDTO dto{};
    dto.name = "Joao";
    dto.age = 35;
    dto.specialty = "Surgery";

    veterinarianService.addVeterinarian(dto);

    VeterinarianInDTO badDto{};
    badDto.name = "Maria";
    badDto.age = 17;
    badDto.specialty = "Dental";

    EXPECT_THROW(veterinarianService.editVeterinarian(1, badDto), InvalidDataException);

    VeterinarianOutDTO result = veterinarianService.getVeterinarianById(1);

    EXPECT_EQ(result.name, "Joao");
    EXPECT_EQ(result.age, 35);
    EXPECT_EQ(result.specialty, "Surgery");
}