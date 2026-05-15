/*
AnimalMapper.h

Created on: 15/05/2026
*/
#ifndef HEADERS_MAPPERS_ANIMALMAPPER_H_
#define HEADERS_MAPPERS_ANIMALMAPPER_H_

#include <vector>

#include "model/Animal.h"
#include "dto/AnimalOutDTO.h"

class AnimalMapper {
public:
    static AnimalOutDTO toDTO(const Animal& animal);
    static std::vector<AnimalOutDTO> toDTOList(const std::vector<Animal>& animals);
};

#endif