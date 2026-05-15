#include "controllers/Controller.h"

#include <iostream>

void Controller::run() {
    int option;

    do {
        option = view.menu();

        switch (option) {
            case 1:
                std::cout << "Menu de Animais ainda nao implementado.\n";
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