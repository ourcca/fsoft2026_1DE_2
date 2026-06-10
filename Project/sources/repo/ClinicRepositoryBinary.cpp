#include "repo/ClinicRepositoryBinary.h"

#include <fstream>
#include <string>

static void writeString(std::ofstream& file, const std::string& value) {
    int size = value.size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(value.c_str(), size);
}

static std::string readString(std::ifstream& file) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::string value(size, ' ');
    file.read(&value[0], size);

    return value;
}

ClinicRepositoryBinary::ClinicRepositoryBinary(const std::string& fileName) {
    this->fileName = fileName;
}

Clinic& ClinicRepositoryBinary::getClinic() {
    return clinic;
}

void ClinicRepositoryBinary::save() {
    std::ofstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        return;
    }

    auto& animals = clinic.getAnimalContainer().getAll();
    int animalCount = animals.size();
    file.write(reinterpret_cast<const char*>(&animalCount), sizeof(animalCount));

    for (const Animal& animal : animals) {
        int id = animal.getId();
        int age = animal.getAge();
        float weight = animal.getWeight();

        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(file, animal.getName());
        writeString(file, animal.getSpecies());
        writeString(file, animal.getBreed());
        file.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
        file.write(reinterpret_cast<const char*>(&age), sizeof(age));
    }

    auto& veterinarians = clinic.getVeterinarianContainer().getAll();
    int veterinarianCount = veterinarians.size();
    file.write(reinterpret_cast<const char*>(&veterinarianCount), sizeof(veterinarianCount));

    for (const Veterinarian& veterinarian : veterinarians) {
        int id = veterinarian.getId();
        int age = veterinarian.getAge();

        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(file, veterinarian.getName());
        file.write(reinterpret_cast<const char*>(&age), sizeof(age));
        writeString(file, veterinarian.getSpecialty());
    }

    file.close();
}

void ClinicRepositoryBinary::load() {
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        return;
    }

    int animalCount;
    file.read(reinterpret_cast<char*>(&animalCount), sizeof(animalCount));

    for (int i = 0; i < animalCount; i++) {
        int id;
        int age;
        float weight;
        std::string name;
        std::string species;
        std::string breed;

        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        name = readString(file);
        species = readString(file);
        breed = readString(file);
        file.read(reinterpret_cast<char*>(&weight), sizeof(weight));
        file.read(reinterpret_cast<char*>(&age), sizeof(age));

        Animal animal(id, name, species, breed, weight, age);
        clinic.getAnimalContainer().add(animal);
    }

    int veterinarianCount;
    file.read(reinterpret_cast<char*>(&veterinarianCount), sizeof(veterinarianCount));

    for (int i = 0; i < veterinarianCount; i++) {
        int id;
        int age;
        std::string name;
        std::string specialty;

        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        name = readString(file);
        file.read(reinterpret_cast<char*>(&age), sizeof(age));
        specialty = readString(file);

        Veterinarian veterinarian(id, name, age, specialty);
        clinic.getVeterinarianContainer().add(veterinarian);
    }

    file.close();
}