/*
AnimalOutDTO.h

Created on: 15/05/2026
*/
#ifndef HEADERS_DTO_ANIMALOUTDTO_H_
#define HEADERS_DTO_ANIMALOUTDTO_H_

#include <string>

struct AnimalOutDTO {
    int id;
    std::string name;
    std::string species;
    std::string breed;
    float weight;
    int age;
};

#endif