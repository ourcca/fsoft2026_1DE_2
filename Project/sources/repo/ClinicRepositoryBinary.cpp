#include "repo/ClinicRepositoryBinary.h"

#include <fstream>
#include <string>

#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Service.h"
#include "model/Prescription.h"
#include "model/Date.h"
#include "model/Time.h"
#include "exceptions/DataConsistencyException.h"
#include "exceptions/InvalidDataException.h"
#include "services/ServiceCatalog.h"
#include "services/AnimalCatalog.h"

namespace {
    constexpr int MAX_STRING_SIZE = 10000;
    constexpr int MAX_RECORD_COUNT = 100000;

    template <typename T>
    void readValue(std::ifstream& file, T& value, const std::string& fieldName) {
        if (!file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw InvalidDataException("Erro ao ler " + fieldName + " do ficheiro binário.");
        }
    }

    void validateCount(int count, const std::string& fieldName) {
        if (count < 0 || count > MAX_RECORD_COUNT) {
            throw InvalidDataException("Número inválido de " + fieldName + " no ficheiro binário.");
        }
    }

    static void writeString(std::ofstream& file, const std::string& value) {
        if (value.size() > MAX_STRING_SIZE) {
            throw InvalidDataException("String demasiado grande para guardar no ficheiro binário.");
        }

        int size = static_cast<int>(value.size());
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        file.write(value.c_str(), size);
    }

    static std::string readString(std::ifstream& file) {
        int size = 0;
        readValue(file, size, "tamanho da string");

        if (size < 0 || size > MAX_STRING_SIZE) {
            throw InvalidDataException("Tamanho de string inválido no ficheiro binário.");
        }

        std::string value(size, ' ');

        if (size > 0 && !file.read(&value[0], size)) {
            throw InvalidDataException("Erro ao ler string do ficheiro binário.");
        }

        return value;
    }

    void validateLoadedServiceCatalogRule(const std::string& serviceType, const Animal* animal,
                                      const Veterinarian* veterinarian) {
        if (!ServiceCatalog::isValidServiceType(serviceType)) {
            throw InvalidDataException("Tipo de Serviço inválido no ficheiro binário.");
        }

        if (animal == nullptr) {
            throw DataConsistencyException("Serviço no ficheiro binário tem Animal inválido.");
        }

        if (veterinarian == nullptr) {
            throw DataConsistencyException("Serviço no ficheiro binário tem Veterinário inválido.");
        }

        if (ServiceCatalog::requiresExoticAnimal(serviceType) &&
            !AnimalCatalog::isExoticSpecies(animal->getSpecies())) {
            throw DataConsistencyException("Serviço de animais exóticos no ficheiro binário está associado a Animal não exótico.");
            }

        const std::string veterinarianSpecialtyKey =
            ServiceCatalog::normalizeKey(veterinarian->getSpecialty());

        const std::string requiredSpecialty =
            ServiceCatalog::requiredSpecialtyForService(serviceType);

        const std::string requiredSpecialtyKey =
            ServiceCatalog::normalizeKey(requiredSpecialty);

        if (requiredSpecialtyKey.empty()) {
            if (!veterinarianSpecialtyKey.empty()) {
                throw DataConsistencyException("Serviço sem especialidade no ficheiro binário está associado a Veterinário com especialidade.");
            }

            return;
        }

        if (veterinarianSpecialtyKey.empty()) {
            throw DataConsistencyException("Serviço com especialidade no ficheiro binário está associado a Veterinário sem especialidade.");
        }

        if (veterinarianSpecialtyKey != requiredSpecialtyKey) {
            throw DataConsistencyException("Serviço no ficheiro binário está associado a Veterinário com especialidade errada.");
        }
    }
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

    Clinic loadedClinic;

    int animalCount = 0;
    readValue(file, animalCount, "número de animais");
    validateCount(animalCount, "animais");

    for (int i = 0; i < animalCount; i++) {
        int id;
        int age;
        float weight;

        readValue(file, id, "ID do animal");
        std::string name = readString(file);
        std::string species = readString(file);
        std::string breed = readString(file);
        readValue(file, weight, "peso do animal");
        readValue(file, age, "idade do animal");

        if (!AnimalCatalog::isValidSpecies(species)) {
            throw InvalidDataException("Espécie de Animal inválida no ficheiro binário.");
        }

        if (!AnimalCatalog::isValidBreedForSpecies(species, breed)) {
            throw InvalidDataException("Raça de Animal inválida para a espécie no ficheiro binário.");
        }

        Animal animal(id, name, species, breed, weight, age);
        loadedClinic.getAnimalContainer().add(animal);
    }

    int veterinarianCount = 0;
    readValue(file, veterinarianCount, "número de veterinários");
    validateCount(veterinarianCount, "veterinários");

    for (int i = 0; i < veterinarianCount; i++) {
        int id;
        int age;

        readValue(file, id, "ID do veterinário");
        std::string name = readString(file);
        readValue(file, age, "idade do veterinário");
        std::string specialty = readString(file);

        if (!ServiceCatalog::isValidSpecialty(specialty)) {
            throw InvalidDataException("Especialidade de Veterinário inválida no ficheiro binário.");
        }

        Veterinarian veterinarian(id, name, age, specialty);
        loadedClinic.getVeterinarianContainer().add(veterinarian);
    }

    int serviceCount = 0;
    readValue(file, serviceCount, "número de serviços");
    validateCount(serviceCount, "serviços");

    for (int i = 0; i < serviceCount; i++) {
        int id;
        float cost;
        int day;
        int month;
        int year;
        int hour;
        int minute;
        int animalId;
        int veterinarianId;

        readValue(file, id, "ID do serviço");
        std::string type = readString(file);
        readValue(file, cost, "custo do serviço");

        readValue(file, day, "dia do serviço");
        readValue(file, month, "mês do serviço");
        readValue(file, year, "ano do serviço");

        readValue(file, hour, "hora do serviço");
        readValue(file, minute, "minuto do serviço");

        readValue(file, animalId, "ID do animal do serviço");
        readValue(file, veterinarianId, "ID do veterinário do serviço");

        Animal* animal = loadedClinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = loadedClinic.getVeterinarianContainer().get(veterinarianId);

        if (animal == nullptr || veterinarian == nullptr) {
            throw DataConsistencyException("Serviço no ficheiro binário referencia Animal ou Veterinário inexistente.");
        }

        validateLoadedServiceCatalogRule(type, animal, veterinarian);

        Date date(day, month, year);
        Time time(hour, minute);

        Service service(id, type, cost, date, time, animal, veterinarian);
        loadedClinic.getServiceContainer().add(service);
    }

    int prescriptionCount = 0;
    readValue(file, prescriptionCount, "número de prescrições");
    validateCount(prescriptionCount, "prescrições");

    for (int i = 0; i < prescriptionCount; i++) {
        int id;
        int animalId;
        int veterinarianId;

        readValue(file, id, "ID da prescrição");
        std::string medication = readString(file);
        std::string quantity = readString(file);
        std::string duration = readString(file);

        readValue(file, animalId, "ID do animal da prescrição");
        readValue(file, veterinarianId, "ID do veterinário da prescrição");

        Animal* animal = loadedClinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = loadedClinic.getVeterinarianContainer().get(veterinarianId);

        if (animal == nullptr || veterinarian == nullptr) {
            throw DataConsistencyException("Prescrição no ficheiro binário referencia Animal ou Veterinário inexistente.");
        }

        Prescription prescription(id, medication, quantity, duration, animal, veterinarian);
        loadedClinic.getPrescriptionContainer().add(prescription);
    }

    clinic = loadedClinic;

    for (Service& service : clinic.getServiceContainer().getAll()) {
        int animalId = service.getAnimal()->getId();
        int veterinarianId = service.getVeterinarian()->getId();

        Animal* animal = clinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

        if (animal == nullptr || veterinarian == nullptr) {
            throw DataConsistencyException("Erro ao corrigir referências de Serviço após carregar ficheiro binário.");
        }

        service.setAnimal(animal);
        service.setVeterinarian(veterinarian);
    }

    for (Prescription& prescription : clinic.getPrescriptionContainer().getAll()) {
        int animalId = prescription.getAnimal()->getId();
        int veterinarianId = prescription.getVeterinarian()->getId();

        Animal* animal = clinic.getAnimalContainer().get(animalId);
        Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

        if (animal == nullptr || veterinarian == nullptr) {
            throw DataConsistencyException("Erro ao corrigir referências de Prescrição após carregar ficheiro binário.");
        }

        prescription.setAnimal(animal);
        prescription.setVeterinarian(veterinarian);

    }
}