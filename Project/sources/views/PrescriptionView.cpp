/*
PrescriptionView.cpp

Created on: 16/05/2026
*/
#include "views/PrescriptionView.h"
#include "views/Utils.h"
#include "services/PrescriptionCatalog.h"
#include <iostream>

int PrescriptionView::menu() {
    std::cout << "\n========== Gestão de Prescrições ==========\n";
    std::cout << "1. Emitir Prescrição\n";
    std::cout << "2. Listar Prescrições\n";
    std::cout << "3. Consultar Prescrições de Animal\n";
    std::cout << "4. Editar Prescrição\n";
    std::cout << "5. Remover Prescrição\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

void PrescriptionView::showPrescriptionCreated() {
    std::cout << "Prescrição registada com sucesso.\n";
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
        std::cout << "Não existem prescrições registadas.\n";
        return;
    }

    std::cout << "\n========== Lista de Prescrições ==========\n";

    for (const PrescriptionOutDTO& prescription : prescriptions) {
        std::cout << "ID: " << prescription.id << "\n";
        std::cout << "Medicamento: " << prescription.medication << "\n";
        std::cout << "Quantidade: " << prescription.quantity << "\n";
        std::cout << "Duração: " << prescription.duration << "\n";
        std::cout << "ID Animal: " << prescription.animalId << "\n";
        std::cout << "ID Veterinário: " << prescription.veterinarianId << "\n";
        std::cout << "------------------------------------------\n";
    }
}

int PrescriptionView::getAnimalId() {
    return Utils::getNumber("ID do animal: ");
}

std::string PrescriptionView::getMedication() {
    std::cout << "\nMedicamentos disponíveis:\n";

    for (const std::string& medication : PrescriptionCatalog::getMedications()) {
        std::cout << "- " << medication << "\n";
    }

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