/*
VeterinarianService.cpp

Created on: 16/05/2026
*/
#include "services/VeterinarianService.h"

#include "model/Veterinarian.h"
#include "mappers/VeterinarianMapper.h"
#include "exceptions/InvalidDataException.h"

VeterinarianService::VeterinarianService(Clinic& clinic) : clinic(clinic) {}

void VeterinarianService::addVeterinarian(const VeterinarianInDTO& dto) {
    if (dto.name.empty())
        throw InvalidDataException("Veterinarian name cannot be empty.");
    if (dto.specialty.empty())
        throw InvalidDataException("Veterinarian specialty cannot be empty.");
    if (dto.age < 18)
        throw InvalidDataException("Veterinarian age is invalid.");
    int id = clinic.getVeterinarianContainer().getNextId();
    Veterinarian veterinarian(id, dto.name, dto.age, dto.specialty);
    clinic.getVeterinarianContainer().add(veterinarian);
}

std::vector<VeterinarianOutDTO> VeterinarianService::getAllVeterinarians() {
    std::vector<Veterinarian>& veterinarians = clinic.getVeterinarianContainer().getAll();
    return VeterinarianMapper::toDTOList(veterinarians);
}