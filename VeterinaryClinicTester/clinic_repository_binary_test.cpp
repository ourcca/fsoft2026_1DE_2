#include "gtest/gtest.h"

#include <cstdio>
#include <fstream>
#include <string>

#include "repo/ClinicRepositoryBinary.h"

#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

#include "exceptions/InvalidDataException.h"
#include "exceptions/DataConsistencyException.h"

TEST(ClinicRepositoryBinaryTest, SaveAndLoadAnimalAndVeterinarian) {
    std::string fileName = "test_clinic.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Cirurgia")
        );

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        ASSERT_NE(animal, nullptr);
        ASSERT_NE(veterinarian, nullptr);

        EXPECT_EQ(animal->getName(), "Rex");
        EXPECT_EQ(animal->getSpecies(), "Cão");
        EXPECT_EQ(animal->getBreed(), "Labrador");

        EXPECT_EQ(veterinarian->getName(), "Joao");
        EXPECT_EQ(veterinarian->getSpecialty(), "Cirurgia");
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, SaveAndLoadServiceWithPointers) {
    std::string fileName = "test_clinic_service.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        repo.getClinic().getServiceContainer().add(
            Service(
                1,
                "Consulta Geral",
                30.0f,
                Date(20, 5, 2026),
                Time(14, 30),
                animal,
                veterinarian
            )
        );

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Service* service = repo.getClinic().getServiceContainer().get(1);

        ASSERT_NE(service, nullptr);
        ASSERT_NE(service->getAnimal(), nullptr);
        ASSERT_NE(service->getVeterinarian(), nullptr);

        EXPECT_EQ(service->getType(), "Consulta Geral");
        EXPECT_EQ(service->getAnimal()->getName(), "Rex");
        EXPECT_EQ(service->getVeterinarian()->getName(), "Joao");

        Animal* loadedAnimal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* loadedVeterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        EXPECT_EQ(service->getAnimal(), loadedAnimal);
        EXPECT_EQ(service->getVeterinarian(), loadedVeterinarian);
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, SaveAndLoadSpecialtyServiceWithPointers) {
    std::string fileName = "test_clinic_specialty_service.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Cirurgia")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        repo.getClinic().getServiceContainer().add(
            Service(
                1,
                "Cirurgia",
                50.0f,
                Date(20, 5, 2026),
                Time(14, 30),
                animal,
                veterinarian
            )
        );

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Service* service = repo.getClinic().getServiceContainer().get(1);

        ASSERT_NE(service, nullptr);
        ASSERT_NE(service->getAnimal(), nullptr);
        ASSERT_NE(service->getVeterinarian(), nullptr);

        EXPECT_EQ(service->getType(), "Cirurgia");
        EXPECT_EQ(service->getVeterinarian()->getSpecialty(), "Cirurgia");
    }

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, SaveAndLoadPrescriptionWithPointers) {
    std::string fileName = "test_clinic_prescription.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Cirurgia")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        repo.getClinic().getPrescriptionContainer().add(
            Prescription(
                1,
                "Amoxicilina",
                "2 comprimidos/dia",
                "7 dias",
                animal,
                veterinarian
            )
        );

        repo.save();
    }

    {
        ClinicRepositoryBinary repo(fileName);
        repo.load();

        Prescription* prescription = repo.getClinic().getPrescriptionContainer().get(1);

        ASSERT_NE(prescription, nullptr);
        ASSERT_NE(prescription->getAnimal(), nullptr);
        ASSERT_NE(prescription->getVeterinarian(), nullptr);

        EXPECT_EQ(prescription->getMedication(), "Amoxicilina");
        EXPECT_EQ(prescription->getQuantity(), "2 comprimidos/dia");
        EXPECT_EQ(prescription->getDuration(), "7 dias");
        EXPECT_EQ(prescription->getAnimal()->getName(), "Rex");
        EXPECT_EQ(prescription->getVeterinarian()->getName(), "Joao");

        Animal* loadedAnimal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* loadedVeterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        EXPECT_EQ(prescription->getAnimal(), loadedAnimal);
        EXPECT_EQ(prescription->getVeterinarian(), loadedVeterinarian);
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

TEST(ClinicRepositoryBinaryTest, LoadNegativeAnimalCountThrowsException) {
    std::string fileName = "corrupted_negative_count.dat";
    std::remove(fileName.c_str());

    {
        std::ofstream file(fileName, std::ios::binary);

        int animalCount = -1;
        file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), InvalidDataException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadHugeAnimalCountThrowsException) {
    std::string fileName = "corrupted_huge_count.dat";
    std::remove(fileName.c_str());

    {
        std::ofstream file(fileName, std::ios::binary);

        int animalCount = 100001;
        file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), InvalidDataException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadTruncatedFileThrowsException) {
    std::string fileName = "corrupted_truncated.dat";
    std::remove(fileName.c_str());

    {
        std::ofstream file(fileName, std::ios::binary);

        int animalCount = 1;
        file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), InvalidDataException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadInvalidStringSizeThrowsException) {
    std::string fileName = "corrupted_string_size.dat";
    std::remove(fileName.c_str());

    {
        std::ofstream file(fileName, std::ios::binary);

        int animalCount = 1;
        int animalId = 1;
        int invalidStringSize = -5;

        file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));
        file.write(reinterpret_cast<const char*>(&animalId), sizeof(animalId));
        file.write(reinterpret_cast<const char*>(&invalidStringSize), sizeof(invalidStringSize));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), InvalidDataException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadServiceWithMissingAnimalOrVeterinarianThrowsException) {
    std::string fileName = "corrupted_service_reference.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        repo.getClinic().getServiceContainer().add(
            Service(
                1,
                "Consulta Geral",
                30.0f,
                Date(20, 5, 2026),
                Time(14, 30),
                animal,
                veterinarian
            )
        );

        repo.save();
    }

    {
        std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

        file.seekp(-2 * static_cast<int>(sizeof(int)), std::ios::end);

        int missingVeterinarianId = 99;
        file.write(reinterpret_cast<const char*>(&missingVeterinarianId), sizeof(missingVeterinarianId));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), DataConsistencyException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadPrescriptionWithMissingAnimalOrVeterinarianThrowsException) {
    std::string fileName = "corrupted_prescription_reference.dat";
    std::remove(fileName.c_str());

    {
        ClinicRepositoryBinary repo(fileName);

        repo.getClinic().getAnimalContainer().add(
            Animal(1, "Rex", "Cão", "Labrador", 20.5f, 4)
        );

        repo.getClinic().getVeterinarianContainer().add(
            Veterinarian(1, "Joao", 35, "Cirurgia")
        );

        Animal* animal = repo.getClinic().getAnimalContainer().get(1);
        Veterinarian* veterinarian = repo.getClinic().getVeterinarianContainer().get(1);

        repo.getClinic().getPrescriptionContainer().add(
            Prescription(
                1,
                "Amoxicilina",
                "2 comprimidos/dia",
                "7 dias",
                animal,
                veterinarian
            )
        );

        repo.save();
    }

    {
        std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

        file.seekp(-2 * static_cast<int>(sizeof(int)), std::ios::end);

        int missingAnimalId = 99;
        file.write(reinterpret_cast<const char*>(&missingAnimalId), sizeof(missingAnimalId));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), DataConsistencyException);

    std::remove(fileName.c_str());
}

TEST(ClinicRepositoryBinaryTest, LoadServiceWithInvalidCatalogTypeThrowsException) {
    std::string fileName = "corrupted_invalid_service_type.dat";
    std::remove(fileName.c_str());

    {
        std::ofstream file(fileName, std::ios::binary);

        int animalCount = 1;
        file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));

        int animalId = 1;
        float weight = 20.5f;
        int age = 4;

        file.write(reinterpret_cast<const char*>(&animalId), sizeof(animalId));

        int nameSize = 3;
        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write("Rex", nameSize);

        std::string species = "Cão";
        int speciesSize = static_cast<int>(species.size());
        file.write(reinterpret_cast<const char*>(&speciesSize), sizeof(speciesSize));
        file.write(species.c_str(), speciesSize);

        std::string breed = "Labrador";
        int breedSize = static_cast<int>(breed.size());
        file.write(reinterpret_cast<const char*>(&breedSize), sizeof(breedSize));
        file.write(breed.c_str(), breedSize);

        file.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
        file.write(reinterpret_cast<const char*>(&age), sizeof(age));

        int veterinarianCount = 1;
        file.write(reinterpret_cast<const char*>(&veterinarianCount), sizeof(veterinarianCount));

        int veterinarianId = 1;
        int veterinarianAge = 35;

        file.write(reinterpret_cast<const char*>(&veterinarianId), sizeof(veterinarianId));

        std::string vetName = "Joao";
        int vetNameSize = static_cast<int>(vetName.size());
        file.write(reinterpret_cast<const char*>(&vetNameSize), sizeof(vetNameSize));
        file.write(vetName.c_str(), vetNameSize);

        file.write(reinterpret_cast<const char*>(&veterinarianAge), sizeof(veterinarianAge));

        std::string specialty = "";
        int specialtySize = static_cast<int>(specialty.size());
        file.write(reinterpret_cast<const char*>(&specialtySize), sizeof(specialtySize));

        int serviceCount = 1;
        file.write(reinterpret_cast<const char*>(&serviceCount), sizeof(serviceCount));

        int serviceId = 1;
        float cost = 30.0f;
        int day = 20;
        int month = 5;
        int year = 2026;
        int hour = 14;
        int minute = 30;

        file.write(reinterpret_cast<const char*>(&serviceId), sizeof(serviceId));

        std::string invalidType = "Banho";
        int invalidTypeSize = static_cast<int>(invalidType.size());
        file.write(reinterpret_cast<const char*>(&invalidTypeSize), sizeof(invalidTypeSize));
        file.write(invalidType.c_str(), invalidTypeSize);

        file.write(reinterpret_cast<const char*>(&cost), sizeof(cost));
        file.write(reinterpret_cast<const char*>(&day), sizeof(day));
        file.write(reinterpret_cast<const char*>(&month), sizeof(month));
        file.write(reinterpret_cast<const char*>(&year), sizeof(year));
        file.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
        file.write(reinterpret_cast<const char*>(&minute), sizeof(minute));
        file.write(reinterpret_cast<const char*>(&animalId), sizeof(animalId));
        file.write(reinterpret_cast<const char*>(&veterinarianId), sizeof(veterinarianId));

        int prescriptionCount = 0;
        file.write(reinterpret_cast<const char*>(&prescriptionCount), sizeof(prescriptionCount));
    }

    ClinicRepositoryBinary repo(fileName);

    EXPECT_THROW(repo.load(), InvalidDataException);

    std::remove(fileName.c_str());
}