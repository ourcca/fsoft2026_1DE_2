/*
AnimalService.cpp

Created on: 15/05/2026
*/
#include "services/AnimalService.h"
#include "mappers/AnimalMapper.h"
#include "model/Animal.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"
#include "exceptions/DataConsistencyException.h"
#include "model/Prescription.h"
#include "model/Service.h"
#include "services/ServiceCatalog.h"
#include "services/AnimalCatalog.h"


AnimalService::AnimalService(Clinic& clinic) : clinic(clinic) {}

void AnimalService::addAnimal(const AnimalInDTO& dto) const {
    validateName(dto.name);
    validateSpecies(dto.species);
    validateBreedForSpecies(dto.species, dto.breed);
    validateWeight(dto.weight);
    validateAge(dto.age);

    int id = clinic.getAnimalContainer().getNextId();

    Animal animal(id, dto.name, dto.species, dto.breed, dto.weight, dto.age);
    clinic.getAnimalContainer().add(animal);
}

std::vector<AnimalOutDTO> AnimalService::getAllAnimals() const {
    auto& animals = clinic.getAnimalContainer().getAll();
    return AnimalMapper::toDTOList(animals);
}

AnimalOutDTO AnimalService::getAnimalById(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(id);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    return AnimalMapper::toDTO(*animal);
}

void AnimalService::editAnimal(int id, const AnimalInDTO& dto) {
    if (id <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    validateName(dto.name);
    validateSpecies(dto.species);
    validateBreedForSpecies(dto.species, dto.breed);
    validateWeight(dto.weight);
    validateAge(dto.age);

    Animal* animal = clinic.getAnimalContainer().get(id);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    if (!AnimalCatalog::isExoticSpecies(dto.species)) {
        for (const Service& service : clinic.getServiceContainer().getAll()) {
            if (service.getAnimal() == animal &&
                ServiceCatalog::requiresExoticAnimal(service.getType())) {
                throw DataConsistencyException("Não é possível alterar este animal para não exótico porque tem serviços de animais exóticos associados.");
                }
        }
    }

    clinic.getAnimalContainer().edit(
        id,
        dto.name,
        dto.species,
        dto.breed,
        dto.weight,
        dto.age
    );
}

int AnimalService::countPrescriptionsByAnimalId(int animalId) const {
    if (animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(animalId);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    int count = 0;

    for (const Prescription& prescription : clinic.getPrescriptionContainer().getAll()) {
        if (prescription.getAnimal() == animal) {
            count++;
        }
    }

    return count;
}

int AnimalService::countServicesByAnimalId(int animalId) const {
    if (animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(animalId);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    int count = 0;

    for (const Service& service : clinic.getServiceContainer().getAll()) {
        if (service.getAnimal() == animal) {
            count++;
        }
    }

    return count;
}

bool AnimalService::hasAssociatedRecords(int animalId) const {
    return countPrescriptionsByAnimalId(animalId) > 0 || countServicesByAnimalId(animalId) > 0;
}

void AnimalService::removeAnimal(int id, bool removeAssociatedRecords) {
    if (id <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(id);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    std::vector<int> prescriptionIds;
    std::vector<int> serviceIds;

    for (const Prescription& prescription : clinic.getPrescriptionContainer().getAll()) {
        if (prescription.getAnimal() == animal) {
            prescriptionIds.push_back(prescription.getId());
        }
    }

    for (const Service& service : clinic.getServiceContainer().getAll()) {
        if (service.getAnimal() == animal) {
            serviceIds.push_back(service.getId());
        }
    }

    if ((!prescriptionIds.empty() || !serviceIds.empty()) && !removeAssociatedRecords) {
        throw DataConsistencyException("Animal tem prescrições ou serviços associados. Remoção cancelada.");
    }

    for (int prescriptionId : prescriptionIds) {
        clinic.getPrescriptionContainer().remove(prescriptionId);
    }

    for (int serviceId : serviceIds) {
        clinic.getServiceContainer().remove(serviceId);
    }

    clinic.getAnimalContainer().remove(id);
}

void AnimalService::validateName(const std::string& name) const {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    animal.setName(name);
}

void AnimalService::validateSpecies(const std::string& species) const {
    Animal animal(1, "Nome", "Cão", "Rafeiro", 1.0f, 0);
    animal.setSpecies(species);

    if (!AnimalCatalog::isValidSpecies(species)) {
        throw InvalidDataException("Espécie de Animal não existe.");
    }
}

void AnimalService::validateWeight(float weight) const {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    animal.setWeight(weight);
}

void AnimalService::validateAge(int age) const {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    animal.setAge(age);
}

void AnimalService::validateBreedForSpecies(const std::string& species, const std::string& breed) const {
    if (!AnimalCatalog::isValidSpecies(species)) {
        throw InvalidDataException("Espécie de Animal não existe.");
    }

    Animal animal(1, "Nome", "Cão", "Rafeiro", 1.0f, 0);
    animal.setSpecies(species);
    animal.setBreed(breed);

    if (!AnimalCatalog::isValidBreedForSpecies(species, breed)) {
        if (AnimalCatalog::isExoticSpecies(species)) {
            throw InvalidDataException("Animal exótico não deve ter raça.");
        }

        throw InvalidDataException("Raça não existe para a espécie indicada.");
    }
}

bool AnimalService::speciesRequiresBreed(const std::string& species) const {
    return AnimalCatalog::requiresBreed(species);
}
