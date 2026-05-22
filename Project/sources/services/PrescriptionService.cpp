/*
PrescriptionService.cpp

Created on: 16/05/2026
*/
#include "services/PrescriptionService.h"

#include "model/Prescription.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "mappers/PrescriptionMapper.h"

PrescriptionService::PrescriptionService(Clinic& clinic) : clinic(clinic) {}

void PrescriptionService::addPrescription(const PrescriptionInDTO& dto) {
    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    if (animal == nullptr || veterinarian == nullptr) {
        return;
    }

    Prescription prescription(
        dto.id,
        dto.medication,
        dto.quantity,
        dto.duration,
        animal,
        veterinarian
    );

    clinic.getPrescriptionContainer().add(prescription);
}

std::vector<PrescriptionOutDTO> PrescriptionService::getAllPrescriptions() {
    std::vector<Prescription>& prescriptions = clinic.getPrescriptionContainer().getAll();
    return PrescriptionMapper::toDTOList(prescriptions);
}