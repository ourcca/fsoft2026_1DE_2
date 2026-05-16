/*
Clinic.cpp

Created on: 15/05/2026
 */
#include "model/Clinic.h"

AnimalContainer& Clinic::getAnimalContainer() {
    return animals;
}

VeterinarianContainer& Clinic::getVeterinarianContainer() {
    return veterinarians;
}

ServiceContainer& Clinic::getServiceContainer() {
    return services;
}