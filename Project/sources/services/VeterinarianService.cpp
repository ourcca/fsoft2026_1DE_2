/*
VeterinarianService.cpp

Created on: 16/05/2026
*/
#include "services/VeterinarianService.h"

#include "model/Veterinarian.h"
#include "mappers/VeterinarianMapper.h"

VeterinarianService::VeterinarianService(Clinic& clinic) : clinic(clinic) {}

void VeterinarianService::addVeterinarian(const VeterinarianInDTO& dto) {
    Veterinarian veterinarian(dto.id, dto.name, dto.age, dto.specialty);
    clinic.getVeterinarianContainer().add(veterinarian);
}

std::vector<VeterinarianOutDTO> VeterinarianService::getAllVeterinarians() {
    std::vector<Veterinarian>& veterinarians = clinic.getVeterinarianContainer().getAll();
    return VeterinarianMapper::toDTOList(veterinarians);
}