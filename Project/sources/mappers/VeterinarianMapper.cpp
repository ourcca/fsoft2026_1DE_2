/*
VeterinarianMapper.cpp

Created on: 16/05/2026
 */
#include "mappers/VeterinarianMapper.h"

VeterinarianOutDTO VeterinarianMapper::toDTO(const Veterinarian& veterinarian) {
    VeterinarianOutDTO dto{};

    dto.id = veterinarian.getId();
    dto.name = veterinarian.getName();
    dto.age = veterinarian.getAge();
    dto.specialty = veterinarian.getSpecialty();

    return dto;
}

std::vector<VeterinarianOutDTO> VeterinarianMapper::toDTOList(const std::deque<Veterinarian>& veterinarians) {
    std::vector<VeterinarianOutDTO> dtos;

    for (const Veterinarian& veterinarian : veterinarians) {
        dtos.push_back(toDTO(veterinarian));
    }

    return dtos;
}