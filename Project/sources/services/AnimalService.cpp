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
    if (dto.name.empty())
        throw InvalidDataException("Nome de Animal não pode estar vazio.");
    if (dto.species.empty())
        throw InvalidDataException("Espécie de Animal não pode estar vazio.");
    if (dto.weight <= 0)
        throw InvalidDataException("Peso do Animal tem de ser positivo.");
    if (dto.age < 0)
        throw InvalidDataException("Idade de Animal não pode ser negativa.");
    int id = clinic.getAnimalContainer().getNextId();
    Animal animal(id, dto.name, dto.species, dto.breed, dto.weight, dto.age);
    clinic.getAnimalContainer().add(animal);
}

std::vector<AnimalOutDTO> AnimalService::getAllAnimals() const {
    std::vector<Animal>& animals = clinic.getAnimalContainer().getAll();
    return AnimalMapper::toDTOList(animals);
}

AnimalOutDTO AnimalService::getAnimalById(int id) {
    Animal* animal = clinic.getAnimalContainer().get(id);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    return AnimalMapper::toDTO(*animal);
}