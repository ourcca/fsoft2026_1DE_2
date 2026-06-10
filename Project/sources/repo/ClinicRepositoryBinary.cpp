#include "repo/ClinicRepositoryBinary.h"

#include <fstream>
#include <string>

#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"

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

    auto& services = clinic.getServiceContainer().getAll();
    int serviceCount = services.size();
    file.write(reinterpret_cast<const char*>(&serviceCount), sizeof(serviceCount));

    for (const Service& service : services) {
        int id = service.getId();
        float cost = service.getCost();

        int day;
        int month;
        int year;
        service.getDate().getDate(day, month, year);

        int hour;
        int minute;
        service.getTime().getTime(hour, minute);

        int animalId = service.getAnimal()->getId();
        int veterinarianId = service.getVeterinarian()->getId();

        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(file, service.getType());
        file.write(reinterpret_cast<const char*>(&cost), sizeof(cost));

        file.write(reinterpret_cast<const char*>(&day), sizeof(day));
        file.write(reinterpret_cast<const char*>(&month), sizeof(month));
        file.write(reinterpret_cast<const char*>(&year), sizeof(year));

        file.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
        file.write(reinterpret_cast<const char*>(&minute), sizeof(minute));

        file.write(reinterpret_cast<const char*>(&animalId), sizeof(animalId));
        file.write(reinterpret_cast<const char*>(&veterinarianId), sizeof(veterinarianId));
    }
    auto& prescriptions = clinic.getPrescriptionContainer().getAll();
    int prescriptionCount = prescriptions.size();
    file.write(reinterpret_cast<const char*>(&prescriptionCount), sizeof(prescriptionCount));

    for (const Prescription& prescription : prescriptions) {
        int id = prescription.getId();

        int animalId = prescription.getAnimal()->getId();
        int veterinarianId = prescription.getVeterinarian()->getId();

        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(file, prescription.getMedication());
        writeString(file, prescription.getQuantity());
        writeString(file, prescription.getDuration());

        file.write(reinterpret_cast<const char*>(&animalId), sizeof(animalId));
        file.write(reinterpret_cast<const char*>(&veterinarianId), sizeof(veterinarianId));
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

    int serviceCount;
    file.read(reinterpret_cast<char*>(&serviceCount), sizeof(serviceCount));

    for (int i = 0; i < serviceCount; i++) {
        int id;
        float cost;
        std::string type;

        int day;
        int month;
        int year;

        int hour;
        int minute;

        int animalId;
        int veterinarianId;

        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        type = readString(file);
        file.read(reinterpret_cast<char*>(&cost), sizeof(cost));

        file.read(reinterpret_cast<char*>(&day), sizeof(day));
        file.read(reinterpret_cast<char*>(&month), sizeof(month));
        file.read(reinterpret_cast<char*>(&year), sizeof(year));

        file.read(reinterpret_cast<char*>(&hour), sizeof(hour));
        file.read(reinterpret_cast<char*>(&minute), sizeof(minute));

        file.read(reinterpret_cast<char*>(&animalId), sizeof(animalId));
        file.read(reinterpret_cast<char*>(&veterinarianId), sizeof(veterinarianId));

        Animal* animal = clinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

        if (animal != nullptr && veterinarian != nullptr) {
            Date date(day, month, year);
            Time time(hour, minute);

            Service service(id, type, cost, date, time, animal, veterinarian);
            clinic.getServiceContainer().add(service);
        }
    }

    int prescriptionCount;
    file.read(reinterpret_cast<char*>(&prescriptionCount), sizeof(prescriptionCount));

    for (int i = 0; i < prescriptionCount; i++) {
        int id;
        std::string medication;
        std::string quantity;
        std::string duration;

        int animalId;
        int veterinarianId;

        file.read(reinterpret_cast<char*>(&id), sizeof(id));
        medication = readString(file);
        quantity = readString(file);
        duration = readString(file);

        file.read(reinterpret_cast<char*>(&animalId), sizeof(animalId));
        file.read(reinterpret_cast<char*>(&veterinarianId), sizeof(veterinarianId));

        Animal* animal = clinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

        if (animal != nullptr && veterinarian != nullptr) {
            Prescription prescription(id, medication, quantity, duration, animal, veterinarian);
            clinic.getPrescriptionContainer().add(prescription);
        }
    }

    file.close();
}