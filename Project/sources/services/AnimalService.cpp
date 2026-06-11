/*
AnimalService.cpp

Created on: 15/05/2026
*/
#include "services/AnimalService.h"
#include "mappers/AnimalMapper.h"
#include "model/Animal.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"

AnimalService::AnimalService(Clinic& clinic) : clinic(clinic) {}

void AnimalService::addAnimal(const AnimalInDTO& dto) const {
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

    clinic.getAnimalContainer().edit(
        id,
        dto.name,
        dto.species,
        dto.breed,
        dto.weight,
        dto.age
    );
}