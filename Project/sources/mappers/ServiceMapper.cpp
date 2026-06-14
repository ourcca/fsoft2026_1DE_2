/*
ServiceMapper.cpp

Created on: 16/05/2026
*/
#include <string>
#include <sstream>
#include <iomanip>
#include "mappers/ServiceMapper.h"
#include "model/Date.h"
#include "model/Time.h"

namespace {
    std::string formatTime(const Time& time) {
        int hour;
        int minute;

        time.getTime(hour, minute);

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hour
            << ":"
            << std::setw(2) << std::setfill('0') << minute;

        return oss.str();
    }
}

ServiceOutDTO ServiceMapper::toDTO(const Service& service) {
    ServiceOutDTO dto{};

    dto.id = service.getId();
    dto.type = service.getType();
    dto.cost = service.getCost();

    int day, month, year;
    service.getDate().getDate(day, month, year);
    dto.date = std::to_string(day) + "/" +
           std::to_string(month) + "/" +
           std::to_string(year);

    int hour, minute;
    service.getTime().getTime(hour, minute);
    dto.time = formatTime(service.getTime());

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