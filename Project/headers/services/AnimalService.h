/*
AnimalService.h

Created on: 15/05/2026
*/
#ifndef HEADERS_SERVICES_ANIMALSERVICE_H_
#define HEADERS_SERVICES_ANIMALSERVICE_H_

#include "model/Clinic.h"
#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"

class AnimalService {
private:
    Clinic& clinic;

public:
    AnimalService(Clinic& clinic);
    void addAnimal(const AnimalInDTO& dto) const;
    std::vector<AnimalOutDTO> getAllAnimals() const;
    AnimalOutDTO getAnimalById(int id);
    void editAnimal(int id, const AnimalInDTO& dto);
};

#endif