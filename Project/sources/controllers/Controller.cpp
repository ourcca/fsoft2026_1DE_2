/*
Controller.cpp

Created on: 15/05/2026
*/
#include "controllers/Controller.h"
#include "dto/AnimalOutDTO.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"


#include <iostream>
#include <vector>

Controller::Controller() : animalService(clinic),
                            veterinarianService(clinic) {}

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
                std::cout << "Menu de Servicos ainda nao implementado.\n";
                break;
            case 4:
                std::cout << "Menu de Prescricoes ainda nao implementado.\n";
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

void Controller::runAnimals() const {
    int option;

    do {
        option = AnimalView::menu();

        switch (option) {
            case 1: {
                AnimalInDTO dto = AnimalView::getAnimal();
                animalService.addAnimal(dto);
                AnimalView::showAnimalCreated();
                break;
            }
            case 2: {
                std::vector<AnimalOutDTO> animals = animalService.getAllAnimals();
                AnimalView::printAnimals(animals);
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
                VeterinarianInDTO dto = veterinarianView.getVeterinarian();
                veterinarianService.addVeterinarian(dto);
                veterinarianView.showVeterinarianCreated();
                break;
            }
            case 2: {
                std::vector<VeterinarianOutDTO> veterinarians = veterinarianService.getAllVeterinarians();
                veterinarianView.printVeterinarians(veterinarians);
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

