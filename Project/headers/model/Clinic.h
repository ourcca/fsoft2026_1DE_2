/*
Clinic.h

Created on: 15/05/2026
 */
#ifndef HEADERS_MODEL_CLINIC_H_
#define HEADERS_MODEL_CLINIC_H_

#include "model/AnimalContainer.h"

class Clinic {
private:
    AnimalContainer animals;

public:
    AnimalContainer& getAnimalContainer();
};

#endif
