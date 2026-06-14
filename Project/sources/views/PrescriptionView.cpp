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
    std::cout << "4. Editar Prescrição\n";
    std::cout << "5. Remover Prescrição\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

void PrescriptionView::showPrescriptionCreated() {
    std::cout << "Prescricao registada com sucesso.\n";
}

void PrescriptionView::showPrescriptionUpdated() {
    std::cout << "Prescrição editada com sucesso.\n";
}

void PrescriptionView::showPrescriptionRemoved() {
    std::cout << "Prescrição removida com sucesso.\n";
}

void PrescriptionView::printPrescription(const PrescriptionOutDTO& prescription) {
    std::cout << "\n========== Dados da Prescrição ==========\n";
    std::cout << "ID: " << prescription.id << "\n";
    std::cout << "Medicamento: " << prescription.medication << "\n";
    std::cout << "Quantidade: " << prescription.quantity << "\n";
    std::cout << "Duração: " << prescription.duration << "\n";
    std::cout << "ID Animal: " << prescription.animalId << "\n";
    std::cout << "ID Veterinário: " << prescription.veterinarianId << "\n";
    std::cout << "----------------------------------------\n";
}

int PrescriptionView::getPrescriptionId() {
    return Utils::getNumber("ID da prescrição: ");
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

std::string PrescriptionView::getMedication() {
    return Utils::getString("Medicamento: ");
}

std::string PrescriptionView::getQuantity() {
    return Utils::getString("Quantidade: ");
}

std::string PrescriptionView::getDuration() {
    return Utils::getString("Duração: ");
}

int PrescriptionView::getVeterinarianId() {
    return Utils::getNumber("ID do veterinário: ");
}