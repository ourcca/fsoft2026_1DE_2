/*
VeterinarianView.cpp

Created on: 16/05/2026
*/
#include "views/VeterinarianView.h"

#include "views/Utils.h"

#include <iostream>

int VeterinarianView::menu() {
    std::cout << "\n========== Gestão de Veterinários ==========\n";
    std::cout << "1. Registar Veterinário\n";
    std::cout << "2. Listar Veterinários\n";
    std::cout << "3. Consultar Serviços de Veterinário\n";
    std::cout << "4. Editar Veterinário\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

void VeterinarianView::showVeterinarianCreated() {
    std::cout << "Veterinário registado com sucesso.\n";
}

void VeterinarianView::showVeterinarianUpdated() {
    std::cout << "Veterinário editado com sucesso.\n";
}

void VeterinarianView::printVeterinarians(const std::vector<VeterinarianOutDTO>& veterinarians) {
    if (veterinarians.empty()) {
        std::cout << "Não existem veterinários registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Veterinários ==========\n";

    for (const VeterinarianOutDTO& veterinarian : veterinarians) {
        std::cout << "ID: " << veterinarian.id << "\n";
        std::cout << "Nome: " << veterinarian.name << "\n";
        std::cout << "Idade: " << veterinarian.age << "\n";
        std::cout << "Especialidade: "
          << (veterinarian.specialty.empty() ? "Sem especialidade" : veterinarian.specialty)
          << "\n";
        std::cout << "------------------------------------------\n";
    }
}

void VeterinarianView::printVeterinarian(const VeterinarianOutDTO& veterinarian) {
    std::cout << "\n========== Dados do Veterinário ==========\n";
    std::cout << "ID: " << veterinarian.id << "\n";
    std::cout << "Nome: " << veterinarian.name << "\n";
    std::cout << "Idade: " << veterinarian.age << "\n";
    std::cout << "Especialidade: "
          << (veterinarian.specialty.empty() ? "Sem especialidade" : veterinarian.specialty)
          << "\n";
    std::cout << "------------------------------------------\n";
}

int VeterinarianView::getVeterinarianId() {
    return Utils::getNumber("ID do veterinário: ");
}

std::string VeterinarianView::getName() {
    return Utils::getString("Nome: ");
}

int VeterinarianView::getAge() {
    return Utils::getNumber("Idade: ");
}

std::string VeterinarianView::getSpecialty() {
    return Utils::getString("Especialidade (deixe vazio se não tiver): ");
}
