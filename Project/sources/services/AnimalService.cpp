/*
AnimalService.cpp

Created on: 15/05/2026
*/
#include "services/AnimalService.h"
#include "model/Animal.h"

AnimalService::AnimalService(Clinic& clinic) : clinic(clinic) {}

void AnimalService::addAnimal(const AnimalInDTO& dto) const {
    Animal animal(dto.id, dto.name, dto.species, dto.breed, dto.weight, dto.age);
    clinic.getAnimalContainer().add(animal);
}
