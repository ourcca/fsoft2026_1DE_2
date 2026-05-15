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

class Controller {
private:
    Clinic clinic;
    View view;
    AnimalView animalView;
    AnimalService animalService;

    void runAnimals() const;

public:
    Controller();
    void run();
};

#endif