#include "views/View.h"
#include "views/Utils.h"

#include <iostream>

int View::menu() {
    std::cout << "\n====================================\n";
    std::cout << " Sistema de Gestao Clinica Veterinaria\n";
    std::cout << "====================================\n";
    std::cout << "1. Gestao de Animais\n";
    std::cout << "2. Gestao de Veterinarios\n";
    std::cout << "3. Gestao de Servicos\n";
    std::cout << "4. Gestao de Prescricoes\n";
    std::cout << "0. Sair\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

void View::showExitMessage() {
    std::cout << "A sair da aplicacao...\n";
}