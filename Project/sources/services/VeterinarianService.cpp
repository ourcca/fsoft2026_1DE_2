/*
VeterinarianService.cpp

Created on: 16/05/2026
*/
#include "services/VeterinarianService.h"

#include "model/Veterinarian.h"
#include "mappers/VeterinarianMapper.h"
#include "exceptions/NoDataException.h"
#include "exceptions/InvalidDataException.h"

VeterinarianService::VeterinarianService(Clinic& clinic) : clinic(clinic) {}

void VeterinarianService::addVeterinarian(const VeterinarianInDTO& dto) {
    int id = clinic.getVeterinarianContainer().getNextId();
    Veterinarian veterinarian(id, dto.name, dto.age, dto.specialty);
    clinic.getVeterinarianContainer().add(veterinarian);
}

std::vector<VeterinarianOutDTO> VeterinarianService::getAllVeterinarians() {
    auto& veterinarians = clinic.getVeterinarianContainer().getAll();
    return VeterinarianMapper::toDTOList(veterinarians);
}

VeterinarianOutDTO VeterinarianService::getVeterinarianById(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(id);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    return VeterinarianMapper::toDTO(*veterinarian);
}

void VeterinarianService::editVeterinarian(int id, const VeterinarianInDTO& dto) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    clinic.getVeterinarianContainer().edit(
        id,
        dto.name,
        dto.age,
        dto.specialty
    );
}
