/*
Controller.cpp

Created on: 15/05/2026
*/
#include "controllers/Controller.h"

#include <iostream>

Controller::Controller() : animalService(clinic) {}

void Controller::run() {
    int option;

    do {
        option = view.menu();

        switch (option) {
            case 1:
                runAnimals();
                break;
            case 2:
                std::cout << "Menu de Veterinarios ainda nao implementado.\n";
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
            case 2:
                std::cout << "Listar animais ainda nao implementado.\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }

    } while (option != 0);
}
