/*
PrescriptionView.cpp

Created on: 16/05/2026
*/
#include "views/PrescriptionView.h"

#include "views/Utils.h"

#include <iostream>

int PrescriptionView::menu() {
    std::cout << "\n========== Gestao de Prescricoes ==========\n";
    std::cout << "1. Emitir Prescricao\n";
    std::cout << "2. Listar Prescricoes\n";
    std::cout << "3. Consultar Prescricoes de Animal\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

PrescriptionInDTO PrescriptionView::getPrescription() {
    PrescriptionInDTO dto{};

    dto.medication = Utils::getString("Medicamento: ");
    dto.quantity = Utils::getString("Quantidade: ");
    dto.duration = Utils::getString("Duracao: ");
    dto.animalId = Utils::getNumber("ID do animal: ");
    dto.veterinarianId = Utils::getNumber("ID do veterinario: ");

    return dto;
}

void PrescriptionView::showPrescriptionCreated() {
    std::cout << "Prescricao registada com sucesso.\n";
}

void PrescriptionView::printPrescriptions(const std::vector<PrescriptionOutDTO>& prescriptions) {
    if (prescriptions.empty()) {
        std::cout << "Nao existem prescricoes registadas.\n";
        return;
    }

    std::cout << "\n========== Lista de Prescricoes ==========\n";

    for (const PrescriptionOutDTO& prescription : prescriptions) {
        std::cout << "ID: " << prescription.id << "\n";
        std::cout << "Medicamento: " << prescription.medication << "\n";
        std::cout << "Quantidade: " << prescription.quantity << "\n";
        std::cout << "Duracao: " << prescription.duration << "\n";
        std::cout << "ID Animal: " << prescription.animalId << "\n";
        std::cout << "ID Veterinario: " << prescription.veterinarianId << "\n";
        std::cout << "------------------------------------------\n";
    }
}

int PrescriptionView::getAnimalId() {
    return Utils::getNumber("ID do animal: ");
}