/*
AnimalView.h

Created on: 15/05/2026
*/
#ifndef HEADERS_VIEWS_ANIMALVIEW_H_
#define HEADERS_VIEWS_ANIMALVIEW_H_

#include "dto/AnimalInDTO.h"

class AnimalView {
public:
    static int menu();

    static AnimalInDTO getAnimal();

    static void showAnimalCreated();
};

#endif