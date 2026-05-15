/*
AnimalView.h

Created on: 15/05/2026
*/
#ifndef HEADERS_VIEWS_ANIMALVIEW_H_
#define HEADERS_VIEWS_ANIMALVIEW_H_

#include <vector>

#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"

class AnimalView {
public:
    static int menu();

    static AnimalInDTO getAnimal();

    static void showAnimalCreated();

    static void printAnimals(const std::vector<AnimalOutDTO>& animals);
};

#endif