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
#include "services/PrescriptionCatalog.h"

PrescriptionService::PrescriptionService(Clinic& clinic) : clinic(clinic) {}

void PrescriptionService::addPrescription(const PrescriptionInDTO& dto) {
    validateAnimalExists(dto.animalId);
    validateVeterinarianExists(dto.veterinarianId);
    validateMedication(dto.medication);
    validateQuantity(dto.quantity);
    validateDuration(dto.duration);

    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

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

PrescriptionOutDTO PrescriptionService::getPrescriptionById(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Prescrição inválido.");
    }

    Prescription* prescription = clinic.getPrescriptionContainer().get(id);

    if (prescription == nullptr) {
        throw NoDataException("Prescrição não encontrada.");
    }

    return PrescriptionMapper::toDTO(*prescription);
}

void PrescriptionService::editPrescription(int id, const PrescriptionInDTO& dto) {
    if (id <= 0) {
        throw InvalidDataException("ID de Prescrição inválido.");
    }

    validateAnimalExists(dto.animalId);
    validateVeterinarianExists(dto.veterinarianId);
    validateMedication(dto.medication);
    validateQuantity(dto.quantity);
    validateDuration(dto.duration);

    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    clinic.getPrescriptionContainer().edit(
        id,
        dto.medication,
        dto.quantity,
        dto.duration,
        animal,
        veterinarian
    );
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
    Animal animal(1, "Nome", "Cão", "Rafeiro", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Cirurgia");
    Prescription prescription(1, "Amoxicilina", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setMedication(medication);

    if (!PrescriptionCatalog::isValidMedication(medication)) {
        throw InvalidDataException("Medicamento da Prescrição não existe.");
    }
}

void PrescriptionService::validateQuantity(const std::string& quantity) {
    Animal animal(1, "Nome", "Cão", "Rafeiro", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Cirurgia");
    Prescription prescription(1, "Amoxicilina", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setQuantity(quantity);
}

void PrescriptionService::validateDuration(const std::string& duration) {
    Animal animal(1, "Nome", "Cão", "Rafeiro", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Cirurgia");
    Prescription prescription(1, "Amoxicilina", "Quantidade", "Duração", &animal, &veterinarian);

    prescription.setDuration(duration);
}

void PrescriptionService::removePrescription(int id) {

    if (id <= 0) {
        throw InvalidDataException("ID de Prescrição inválido.");
    }

    Prescription* prescription = clinic.getPrescriptionContainer().get(id);

    if (prescription == nullptr) {
        throw NoDataException("Prescrição não encontrada.");
    }

    clinic.getPrescriptionContainer().remove(id);
}