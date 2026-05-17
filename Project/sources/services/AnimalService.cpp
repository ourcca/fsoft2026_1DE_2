/*
AnimalService.cpp

Created on: 15/05/2026
*/
#include "services/AnimalService.h"
#include "mappers/AnimalMapper.h"
#include "model/Animal.h"

AnimalService::AnimalService(Clinic& clinic) : clinic(clinic) {}

void AnimalService::addAnimal(const AnimalInDTO& dto) const {
    Animal animal(dto.id, dto.name, dto.species, dto.breed, dto.weight, dto.age);
    clinic.getAnimalContainer().add(animal);
}

std::vector<AnimalOutDTO> AnimalService::getAllAnimals() const {
    std::vector<Animal>& animals = clinic.getAnimalContainer().getAll();
    return AnimalMapper::toDTOList(animals);
}

AnimalOutDTO AnimalService::getAnimalById(int id) {
    Animal* animal = clinic.getAnimalContainer().get(id);

    if (animal == nullptr) {
        return AnimalOutDTO{-1, "", "", "", 0, 0};
    }

    return AnimalMapper::toDTO(*animal);
}