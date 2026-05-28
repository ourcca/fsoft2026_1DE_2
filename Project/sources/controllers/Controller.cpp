/*
Controller.cpp

Created on: 15/05/2026
*/
#include "controllers/Controller.h"
#include "dto/AnimalOutDTO.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"


#include <iostream>
#include <exception>
#include <vector>

Controller::Controller() :
                            animalService(clinic),
                            veterinarianService(clinic),
                            serviceService(clinic),
                            prescriptionService(clinic) {}

void Controller::run() {
    int option;

    do {
        option = view.menu();

        switch (option) {
            case 1:
                runAnimals();
                break;
            case 2:
                runVeterinarians();
                break;
            case 3:
                runServices();
                break;
            case 4:
                runPrescriptions();
                break;
            case 0:
                view.showExitMessage();
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}

void Controller::runAnimals() {
    int option;

    do {
        option = AnimalView::menu();

        switch (option) {
            case 1: {
                try {
                    AnimalInDTO dto = animalView.getAnimal();
                    animalService.addAnimal(dto);
                    animalView.showAnimalCreated();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }

                break;
            }
            case 2: {
                std::vector<AnimalOutDTO> animals = animalService.getAllAnimals();
                animalView.printAnimals(animals);
                break;
            }
            case 3: {
                int id = animalView.getAnimalId();
                AnimalOutDTO animal = animalService.getAnimalById(id);

                if (animal.id == -1) {
                    animalView.showAnimalNotFound();
                } else {
                    animalView.printAnimal(animal);
                }

                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}

void Controller::runVeterinarians() {
    int option;

    do {
        option = veterinarianView.menu();

        switch (option) {
            case 1: {
                try {
                    VeterinarianInDTO dto = veterinarianView.getVeterinarian();
                    veterinarianService.addVeterinarian(dto);
                    veterinarianView.showVeterinarianCreated();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }

                break;
            }
            case 2: {
                std::vector<VeterinarianOutDTO> veterinarians = veterinarianService.getAllVeterinarians();
                veterinarianView.printVeterinarians(veterinarians);
                break;
            }
            case 3: {
                int veterinarianId = veterinarianView.getVeterinarianId();

                std::vector<ServiceOutDTO> services =
                    serviceService.getServicesByVeterinarianId(veterinarianId);

                serviceView.printServices(services);

                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}
void Controller::runServices() {
    int option;

    do {
        option = serviceView.menu();

        switch (option) {
            case 1: {
                try {
                    ServiceInDTO dto = serviceView.getService();
                    serviceService.addService(dto);
                    serviceView.showServiceCreated();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }

                break;
            }
            case 2: {
                std::vector<ServiceOutDTO> services = serviceService.getAllServices();
                serviceView.printServices(services);
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}

void Controller::runPrescriptions() {
    int option;

    do {
        option = prescriptionView.menu();

        switch (option) {
            case 1: {
                try {
                    PrescriptionInDTO dto = prescriptionView.getPrescription();
                    prescriptionService.addPrescription(dto);
                    prescriptionView.showPrescriptionCreated();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }

                break;
            }
            case 2: {
                std::vector<PrescriptionOutDTO> prescriptions =
                    prescriptionService.getAllPrescriptions();

                prescriptionView.printPrescriptions(prescriptions);
                break;
            }
            case 3: {
                int animalId = prescriptionView.getAnimalId();

                std::vector<PrescriptionOutDTO> prescriptions =
                    prescriptionService.getPrescriptionsByAnimalId(animalId);

                prescriptionView.printPrescriptions(prescriptions);
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}
