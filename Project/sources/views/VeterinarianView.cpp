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
    std::cout << "5. Remover Veterinário\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

void VeterinarianView::showVeterinarianCreated() {
    std::cout << "Veterinário registado com sucesso.\n";
}

void VeterinarianView::showVeterinarianUpdated() {
    std::cout << "Veterinário editado com sucesso.\n";
}

void VeterinarianView::showVeterinarianRemoved() {
    std::cout << "Veterinario removido com sucesso.\n";
}

void VeterinarianView::showVeterinarianRemoveCancelled() {
    std::cout << "Remoção do veterinario cancelada.\n";
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
        std::cout << "Especialidade: " << veterinarian.specialty << "\n";
        std::cout << "------------------------------------------\n";
    }
}

void VeterinarianView::printVeterinarian(const VeterinarianOutDTO& veterinarian) {
    std::cout << "\n========== Dados do Veterinário ==========\n";
    std::cout << "ID: " << veterinarian.id << "\n";
    std::cout << "Nome: " << veterinarian.name << "\n";
    std::cout << "Idade: " << veterinarian.age << "\n";
    std::cout << "Especialidade: " << veterinarian.specialty << "\n";
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
    return Utils::getString("Especialidade: ");
}

bool VeterinarianView::confirmRemoveAssociatedData(int prescriptionCount, int serviceCount) {
    std::cout << "Este veterinario tem " << prescriptionCount << " prescrição(ões) e "
              << serviceCount << " serviço(s) associado(s).\n";

    std::string answer;

    do {
        answer = Utils::getString("Quer remover também as prescrições e serviços associados? (s/n): ");

        if (answer != "s" && answer != "S" && answer != "n" && answer != "N") {
            std::cout << "Opção inválida. Escreva s ou n.\n";
        }

    } while (answer != "s" && answer != "S" && answer != "n" && answer != "N");

    return answer == "s" || answer == "S";
}