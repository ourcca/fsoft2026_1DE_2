/*
PrescriptionService.cpp

Created on: 16/05/2026
*/
#include "services/PrescriptionService.h"

#include "model/Prescription.h"
#include "mappers/PrescriptionMapper.h"

PrescriptionService::PrescriptionService(Clinic& clinic) : clinic(clinic) {}

void PrescriptionService::addPrescription(const PrescriptionInDTO& dto) {
    Prescription prescription(
        dto.id,
        dto.medication,
        dto.quantity,
        dto.duration,
        dto.animalId,
        dto.veterinarianId
    );

    clinic.getPrescriptionContainer().add(prescription);
}

std::vector<PrescriptionOutDTO> PrescriptionService::getAllPrescriptions() {
    std::vector<Prescription>& prescriptions = clinic.getPrescriptionContainer().getAll();
    return PrescriptionMapper::toDTOList(prescriptions);
}