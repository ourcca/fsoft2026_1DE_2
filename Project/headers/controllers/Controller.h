/*
Controller.h

Created on: 15/05/2026
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "views/View.h"
#include "views/AnimalView.h"
#include "model/Clinic.h"
#include "services/AnimalService.h"
#include "views/VeterinarianView.h"
#include "services/VeterinarianService.h"
#include "views/ServiceView.h"
#include "services/ServiceService.h"

class Controller {
private:
    Clinic clinic;
    View view;
    AnimalView animalView;
    AnimalService animalService;
    VeterinarianView veterinarianView;
    VeterinarianService veterinarianService;
    ServiceView serviceView;
    ServiceService serviceService;

    void runAnimals() const;
    void runVeterinarians();
    void runServices();

public:
    Controller();
    void run();
};

#endif