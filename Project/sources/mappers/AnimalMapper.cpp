/*
AnimalMapper.cpp

Created on: 15/05/2026
*/
#include "mappers/AnimalMapper.h"

AnimalOutDTO AnimalMapper::toDTO(const Animal& animal) {
    AnimalOutDTO dto{};

    dto.id = animal.getId();
    dto.name = animal.getName();
    dto.species = animal.getSpecies();
    dto.breed = animal.getBreed();
    dto.weight = animal.getWeight();
    dto.age = animal.getAge();

    return dto;
}

std::vector<AnimalOutDTO> AnimalMapper::toDTOList(std::deque<Animal>& animals) {
    std::vector<AnimalOutDTO> dtos;

    for (const Animal& animal : animals) {
        dtos.push_back(toDTO(animal));
    }

    return dtos;
}