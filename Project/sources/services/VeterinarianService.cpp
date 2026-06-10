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
    int id = clinic.getVeterinarianContainer().getNextId();
    Veterinarian veterinarian(id, dto.name, dto.age, dto.specialty);
    clinic.getVeterinarianContainer().add(veterinarian);
}

std::vector<VeterinarianOutDTO> VeterinarianService::getAllVeterinarians() {
    auto& veterinarians = clinic.getVeterinarianContainer().getAll();
    return VeterinarianMapper::toDTOList(veterinarians);
}

void VeterinarianService::edit(int id, const VeterinarianInDTO& dto) {
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(id);
    Veterinarian veterinarian(id, dto.name, dto.age, dto.specialty);
    VeterinarianContainer::edit(veterinarian);
}