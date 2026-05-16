/*
PrescriptionMapper.cpp

Created on: 16/05/2026
*/
#include "mappers/PrescriptionMapper.h"

PrescriptionOutDTO PrescriptionMapper::toDTO(const Prescription& prescription) {
    PrescriptionOutDTO dto{};

    dto.id = prescription.getId();
    dto.medication = prescription.getMedication();
    dto.quantity = prescription.getQuantity();
    dto.duration = prescription.getDuration();
    dto.animalId = prescription.getAnimalId();
    dto.veterinarianId = prescription.getVeterinarianId();

    return dto;
}

std::vector<PrescriptionOutDTO> PrescriptionMapper::toDTOList(const std::vector<Prescription>& prescriptions) {
    std::vector<PrescriptionOutDTO> dtos;

    for (const Prescription& prescription : prescriptions) {
        dtos.push_back(toDTO(prescription));
    }

    return dtos;
}