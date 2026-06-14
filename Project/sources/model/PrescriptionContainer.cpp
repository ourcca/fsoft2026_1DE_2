/*
PrescriptionContainer.cpp

Created on: 16/05/2026
*/
#include "model/PrescriptionContainer.h"
#include "exceptions/DuplicatedDataException.h"
#include <algorithm>
#include "exceptions/NoDataException.h"

std::vector<Prescription>::iterator PrescriptionContainer::findByID(int id) {
    return std::find_if(prescriptions.begin(), prescriptions.end(),
        [id](const Prescription& prescription) {
            return prescription.getId() == id;
        }
    );
}

void PrescriptionContainer::add(const Prescription& prescription) {
    if (get(prescription.getId()) != nullptr)
        throw DuplicatedDataException("Prescrição já existe.");
    prescriptions.push_back(prescription);
}

void PrescriptionContainer::remove(int id) {
    auto it = findByID(id);

    if (it != prescriptions.end()) {
        throw NoDataException("Perscrição não existe.");
    }
}

Prescription* PrescriptionContainer::get(int id) {
    auto it = findByID(id);

    if (it != prescriptions.end()) {
        return &(*it);
    }

    return nullptr;
}

std::vector<Prescription>& PrescriptionContainer::getAll() {
    return prescriptions;
}

int PrescriptionContainer::getNextId() {
    int maxId = 0;

    for (const Prescription& prescription : prescriptions) {
        if (prescription.getId() > maxId) {
            maxId = prescription.getId();
        }
    }

    return maxId + 1;
}

Prescription* PrescriptionContainer::edit(int id,const std::string& medication,const std::string& quantity,const std::string& duration, Animal* animal, Veterinarian* veterinarian) {
    Prescription* prescription = get(id);

    if (prescription == nullptr) {
        throw NoDataException("Prescrição não existe.");
    }

    prescription->setMedication(medication);
    prescription->setQuantity(quantity);
    prescription->setDuration(duration);
    prescription->setAnimal(animal);
    prescription->setVeterinarian(veterinarian);

    return prescription;
}