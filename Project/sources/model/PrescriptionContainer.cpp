/*
PrescriptionContainer.cpp

Created on: 16/05/2026
*/
#include "model/PrescriptionContainer.h"

#include <algorithm>

std::vector<Prescription>::iterator PrescriptionContainer::findByID(int id) {
    return std::find_if(prescriptions.begin(), prescriptions.end(),
        [id](const Prescription& prescription) {
            return prescription.getId() == id;
        }
    );
}

void PrescriptionContainer::add(const Prescription& prescription) {
    prescriptions.push_back(prescription);
}

void PrescriptionContainer::remove(int id) {
    auto it = findByID(id);

    if (it != prescriptions.end()) {
        prescriptions.erase(it);
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