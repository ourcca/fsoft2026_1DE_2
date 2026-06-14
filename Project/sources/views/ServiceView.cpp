/*
ServiceView.h

Created on: 16/05/2026
*/
#include "views/ServiceView.h"

#include "views/Utils.h"

#include <iostream>

int ServiceView::menu() {
    std::cout << "\n========== Gestão de Serviços ==========\n";
    std::cout << "1. Registar Serviço\n";
    std::cout << "2. Listar Serviços\n";
    std::cout << "3. Editar Serviço\n";
    std::cout << "4. Remover Serviço\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

int ServiceView::getAnimalId() {
    return Utils::getNumber("ID do animal: ");
}

int ServiceView::getVeterinarianId() {
    return Utils::getNumber("ID do veterinário: ");
}

ServiceInDTO ServiceView::getVeterinarianSpecialtyRequirement(const ServiceInDTO& dto) {
    ServiceInDTO completedDto = dto;

    std::string answer;

    do {
        answer = Utils::getString("O serviço precisa de uma especialidade específica do veterinário? (s/n): ");

        if (answer != "s" && answer != "S" && answer != "n" && answer != "N") {
            std::cout << "Opção inválida. Escreva s ou n.\n";
        }

    } while (answer != "s" && answer != "S" && answer != "n" && answer != "N");

    completedDto.requiresVeterinarianSpecialty = answer == "s" || answer == "S";

    if (completedDto.requiresVeterinarianSpecialty) {
        completedDto.requiredVeterinarianSpecialty = Utils::getString("Especialidade necessária: ");
    }

    return completedDto;
}

int ServiceView::getServiceId() {
    return Utils::getNumber("ID do serviço: ");
}

std::string ServiceView::getType() {
    return Utils::getString("Tipo de serviço: ");
}

float ServiceView::getCost() {
    return Utils::getFloat("Custo: ");
}

std::string ServiceView::getDate() {
    return Utils::getString("Data (dd/mm/aaaa): ");
}

std::string ServiceView::getTime() {
    return Utils::getString("Hora (hh:mm): ");
}

void ServiceView::showServiceCreated() {
    std::cout << "Serviço registado com sucesso.\n";
}

void ServiceView::showServiceUpdated() {
    std::cout << "Serviço editado com sucesso.\n";
}

void ServiceView::showServiceRemoved() {
    std::cout << "Serviço removido com sucesso.\n";
}

void ServiceView::printService(const ServiceOutDTO& service) {
    std::cout << "\n========== Dados do Serviço ==========\n";
    std::cout << "ID: " << service.id << "\n";
    std::cout << "Tipo: " << service.type << "\n";
    std::cout << "Custo: " << service.cost << "\n";
    std::cout << "Data: " << service.date << "\n";
    std::cout << "Hora: " << service.time << "\n";
    std::cout << "ID Animal: " << service.animalId << "\n";
    std::cout << "ID Veterinário: " << service.veterinarianId << "\n";
    std::cout << "--------------------------------------\n";
}

void ServiceView::printServices(const std::vector<ServiceOutDTO>& services) {
    if (services.empty()) {
        std::cout << "Não existem serviços registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Serviços ==========\n";

    for (const ServiceOutDTO& service : services) {
        std::cout << "ID: " << service.id << "\n";
        std::cout << "Tipo: " << service.type << "\n";
        std::cout << "Custo: " << service.cost << "\n";
        std::cout << "Data: " << service.date << "\n";
        std::cout << "Hora: " << service.time << "\n";
        std::cout << "ID Animal: " << service.animalId << "\n";
        std::cout << "ID Veterinário: " << service.veterinarianId << "\n";
        std::cout << "--------------------------------------\n";
    }
}