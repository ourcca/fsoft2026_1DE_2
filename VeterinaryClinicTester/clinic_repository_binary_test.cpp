#include "gtest/gtest.h"

#include <cstdio>

#include "repo/ClinicRepositoryBinary.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

TEST(ClinicRepositoryBinaryTest, SaveAndLoadAnimalAndVeterinarian) {
    std::string fileName = "test_clinic.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        Animal animal(1, "Rex", "Dog", "Labrador", 20.5f, 4);
        Veterinarian vet(1, "Joao", 35, "Surgery");

        repo.getClinic().getAnimalContainer().add(animal);
        repo.getClinic().getVeterinarianContainer().add(vet);

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* vet = repo.getClinic().getVeterinarianContainer().get(1);

        ASSERT_NE(animal, nullptr);
        ASSERT_NE(vet, nullptr);

        EXPECT_EQ(animal->getName(), "Rex");
        EXPECT_EQ(vet->getName(), "Joao");
        EXPECT_EQ(vet->getSpecialty(), "Surgery");
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, SaveAndLoadServiceWithPointers) {
    std::string fileName = "test_clinic_service.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Surgery")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* vet = repo.getClinic().getVeterinarianContainer().get(1);

        Service service(1, "Surgery", 50.0f, Date(20, 5, 2026), Time(14, 30), animal, vet);
        repo.getClinic().getServiceContainer().add(service);

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Service* service = repo.getClinic().getServiceContainer().get(1);

        ASSERT_NE(service, nullptr);
        ASSERT_NE(service->getAnimal(), nullptr);
        ASSERT_NE(service->getVeterinarian(), nullptr);

        EXPECT_EQ(service->getType(), "Surgery");
        EXPECT_EQ(service->getAnimal()->getName(), "Rex");
        EXPECT_EQ(service->getVeterinarian()->getName(), "Joao");
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, SaveAndLoadPrescriptionWithPointers) {
    std::string fileName = "test_clinic_prescription.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Dog", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Surgery")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* vet = repo.getClinic().getVeterinarianContainer().get(1);

        Prescription prescription(1, "Antibiotic", "2 pills/day", "7 days", animal, vet);
        repo.getClinic().getPrescriptionContainer().add(prescription);

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Prescription* prescription = repo.getClinic().getPrescriptionContainer().get(1);

        ASSERT_NE(prescription, nullptr);
        ASSERT_NE(prescription->getAnimal(), nullptr);
        ASSERT_NE(prescription->getVeterinarian(), nullptr);

        EXPECT_EQ(prescription->getMedication(), "Antibiotic");
        EXPECT_EQ(prescription->getAnimal()->getName(), "Rex");
        EXPECT_EQ(prescription->getVeterinarian()->getName(), "Joao");
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadNonExistingFileDoesNotCrash) {
    std::string fileName = "file_that_does_not_exist.dat";
    std::remove(fileName.c_str());

    ClinicRepositoryBinary repo(fileName);

    EXPECT_NO_THROW(repo.load());
    EXPECT_EQ(repo.getClinic().getAnimalContainer().getAll().size(), 0);
    EXPECT_EQ(repo.getClinic().getVeterinarianContainer().getAll().size(), 0);
    EXPECT_EQ(repo.getClinic().getServiceContainer().getAll().size(), 0);
    EXPECT_EQ(repo.getClinic().getPrescriptionContainer().getAll().size(), 0);
}

