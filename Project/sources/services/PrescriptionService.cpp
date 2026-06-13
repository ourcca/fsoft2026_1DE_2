/*
PrescriptionService.cpp

Created on: 16/05/2026
*/
#include "services/PrescriptionService.h"

#include "model/Prescription.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "mappers/PrescriptionMapper.h"
#include "exceptions/DataConsistencyException.h"
#include "exceptions/NoDataException.h"
#include "exceptions/InvalidDataException.h"

PrescriptionService::PrescriptionService(Clinic& clinic) : clinic(clinic) {}

void PrescriptionService::addPrescription(const PrescriptionInDTO& dto) {
    if (dto.animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    if (dto.veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    if (animal == nullptr || veterinarian == nullptr) {
        throw DataConsistencyException("Animal ou Veterinário não existe.");
    }

    int id = clinic.getPrescriptionContainer().getNextId();

    Prescription prescription(
        id,
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

std::vector<PrescriptionOutDTO> PrescriptionService::getPrescriptionsByAnimalId(int animalId) {
    if (animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(animalId);

    if (animal == nullptr) {
        throw NoDataException("Animal não encontrado.");
    }

    std::vector<PrescriptionOutDTO> result;
    std::vector<Prescription>& prescriptions = clinic.getPrescriptionContainer().getAll();

    for (const Prescription& prescription : prescriptions) {
        if (prescription.getAnimal() == animal) {
            result.push_back(PrescriptionMapper::toDTO(prescription));
        }
    }

    return result;
}

void PrescriptionService::validateAnimalExists(int animalId) {
    if (animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(animalId);

    if (animal == nullptr) {
        throw DataConsistencyException("Animal não existe.");
    }
}

void PrescriptionService::validateVeterinarianExists(int veterinarianId) {
    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw DataConsistencyException("Veterinário não existe.");
    }
}

void PrescriptionService::validateMedication(const std::string& medication) {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    Prescription prescription(1, "Medicamento", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setMedication(medication);
}

void PrescriptionService::validateQuantity(const std::string& quantity) {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    Prescription prescription(1, "Medicamento", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setQuantity(quantity);
}

void PrescriptionService::validateDuration(const std::string& duration) {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    Prescription prescription(1, "Medicamento", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setDuration(duration);
}