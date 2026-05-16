/*
VeterinarianMapper.h

Created on: 16/05/2026
 */
#ifndef HEADERS_MAPPERS_VETERINARIANMAPPER_H_
#define HEADERS_MAPPERS_VETERINARIANMAPPER_H_

#include <vector>

#include "model/Veterinarian.h"
#include "dto/VeterinarianOutDTO.h"

class VeterinarianMapper {
public:
    static VeterinarianOutDTO toDTO(const Veterinarian& veterinarian);
    static std::vector<VeterinarianOutDTO> toDTOList(const std::vector<Veterinarian>& veterinarians);
};

#endif