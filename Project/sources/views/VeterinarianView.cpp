/*
VeterinarianView.cpp

Created on: 16/05/2026
*/
#include "views/VeterinarianView.h"

#include "views/Utils.h"

#include <iostream>

int VeterinarianView::menu() {
    std::cout << "\n========== Gestao de Veterinarios ==========\n";
    std::cout << "1. Registar Veterinario\n";
    std::cout << "2. Listar Veterinarios\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

VeterinarianInDTO VeterinarianView::getVeterinarian() {
    VeterinarianInDTO dto{};

    dto.id = Utils::getNumber("ID: ");
    dto.name = Utils::getString("Nome: ");
    dto.age = Utils::getNumber("Idade: ");
    dto.specialty = Utils::getString("Especialidade: ");

    return dto;
}

void VeterinarianView::showVeterinarianCreated() {
    std::cout << "Veterinario registado com sucesso.\n";
}

void VeterinarianView::printVeterinarians(const std::vector<VeterinarianOutDTO>& veterinarians) {
    if (veterinarians.empty()) {
        std::cout << "Nao existem veterinarios registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Veterinarios ==========\n";

    for (const VeterinarianOutDTO& veterinarian : veterinarians) {
        std::cout << "ID: " << veterinarian.id << "\n";
        std::cout << "Nome: " << veterinarian.name << "\n";
        std::cout << "Idade: " << veterinarian.age << "\n";
        std::cout << "Especialidade: " << veterinarian.specialty << "\n";
        std::cout << "------------------------------------------\n";
    }
}