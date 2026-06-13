#include "views/View.h"
#include "views/Utils.h"

#include <iostream>

int View::menu() {
    std::cout << "\n====================================\n";
    std::cout << " Sistema de Gestão Clínica Veterinária\n";
    std::cout << "====================================\n";
    std::cout << "1. Gestão de Animais\n";
    std::cout << "2. Gestão de Veterinários\n";
    std::cout << "3. Gestão de Serviços\n";
    std::cout << "4. Gestão de Prescrições\n";
    std::cout << "0. Sair\n";

    return Utils::getNumber("Escolha uma opção: ");
}

void View::showExitMessage() {
    std::cout << "A sair da aplicação...\n";
}