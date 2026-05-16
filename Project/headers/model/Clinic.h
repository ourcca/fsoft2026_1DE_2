/*
Clinic.h

Created on: 15/05/2026
 */
#ifndef HEADERS_MODEL_CLINIC_H_
#define HEADERS_MODEL_CLINIC_H_

#include "model/AnimalContainer.h"
#include "model/VeterinarianContainer.h"
#include "model/ServiceContainer.h"

class Clinic {
private:
    AnimalContainer animals;
    VeterinarianContainer veterinarians;
    ServiceContainer services;

public:
    AnimalContainer& getAnimalContainer();
    VeterinarianContainer& getVeterinarianContainer();
    ServiceContainer& getServiceContainer();
};

#endif
