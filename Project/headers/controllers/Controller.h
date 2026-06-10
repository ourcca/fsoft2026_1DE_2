/*
Controller.h

Created on: 15/05/2026
*/
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "repo/ClinicRepositoryBinary.h"

#include "views/View.h"
#include "views/AnimalView.h"
#include "views/VeterinarianView.h"
#include "views/ServiceView.h"
#include "views/PrescriptionView.h"

#include "services/AnimalService.h"
#include "services/VeterinarianService.h"
#include "services/ServiceService.h"
#include "services/PrescriptionService.h"

class Controller {
private:
    ClinicRepositoryBinary repository;

    View view;

    AnimalView animalView;
    AnimalService animalService;

    VeterinarianView veterinarianView;
    VeterinarianService veterinarianService;

    ServiceView serviceView;
    ServiceService serviceService;

    PrescriptionView prescriptionView;
    PrescriptionService prescriptionService;


    void runAnimals();
    void runVeterinarians();
    void runServices();
    void runPrescriptions();

public:
    Controller();
    void run();
};

#endif