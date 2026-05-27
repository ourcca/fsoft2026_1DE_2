/*
ServiceView.h

Created on: 16/05/2026
*/
#include "views/ServiceView.h"

#include "views/Utils.h"

#include <iostream>

int ServiceView::menu() {
    std::cout << "\n========== Gestao de Servicos ==========\n";
    std::cout << "1. Registar Servico\n";
    std::cout << "2. Listar Servicos\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

ServiceInDTO ServiceView::getService() {
    ServiceInDTO dto{};

    dto.type = Utils::getString("Tipo de servico: ");
    dto.cost = static_cast<float>(Utils::getNumber("Custo: "));
    dto.date = Utils::getString("Data (dd/mm/aaaa): ");
    dto.time = Utils::getString("Hora (hh:mm): ");
    dto.animalId = Utils::getNumber("ID do animal: ");
    dto.veterinarianId = Utils::getNumber("ID do veterinario: ");

    return dto;
}

void ServiceView::showServiceCreated() {
    std::cout << "Servico registado com sucesso.\n";
}

void ServiceView::printServices(const std::vector<ServiceOutDTO>& services) {
    if (services.empty()) {
        std::cout << "Nao existem servicos registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Servicos ==========\n";

    for (const ServiceOutDTO& service : services) {
        std::cout << "ID: " << service.id << "\n";
        std::cout << "Tipo: " << service.type << "\n";
        std::cout << "Custo: " << service.cost << "\n";
        std::cout << "Data: " << service.date << "\n";
        std::cout << "Hora: " << service.time << "\n";
        std::cout << "ID Animal: " << service.animalId << "\n";
        std::cout << "ID Veterinario: " << service.veterinarianId << "\n";
        std::cout << "--------------------------------------\n";
    }
}