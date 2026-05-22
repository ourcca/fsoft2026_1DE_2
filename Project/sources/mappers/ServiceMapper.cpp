/*
ServiceMapper.cpp

Created on: 16/05/2026
*/
#include "mappers/ServiceMapper.h"

ServiceOutDTO ServiceMapper::toDTO(const Service& service) {
    ServiceOutDTO dto{};

    dto.id = service.getId();
    dto.type = service.getType();
    dto.cost = service.getCost();
    dto.date = service.getDate();
    dto.time = service.getTime();
    dto.animalId = service.getAnimal()->getId();
    dto.veterinarianId = service.getVeterinarian()->getId();

    return dto;
}

std::vector<ServiceOutDTO> ServiceMapper::toDTOList(const std::vector<Service>& services) {
    std::vector<ServiceOutDTO> dtos;

    for (const Service& service : services) {
        dtos.push_back(toDTO(service));
    }

    return dtos;
}