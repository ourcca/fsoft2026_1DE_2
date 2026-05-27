/*
AnimalInDTO.h

Created on: 15/05/2026
*/
#ifndef HEADERS_DTO_ANIMALINDTO_H_
#define HEADERS_DTO_ANIMALINDTO_H_

#include <string>

struct AnimalInDTO {
    std::string name;
    std::string species;
    std::string breed;
    float weight;
    int age;
};

#endif