/*
ServiceService.cpp

Created on: 16/05/2026
*/
#include <cstdio>
#include "services/ServiceService.h"
#include "model/Service.h"
#include "mappers/ServiceMapper.h"
#include "exceptions/DataConsistencyException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/NoDataException.h"
#include "model/Date.h"
#include "model/Time.h"

namespace {
    std::string trim(const std::string& value) {
        const std::string whitespace = " \t\n\r\f\v";
        const size_t start = value.find_first_not_of(whitespace);

        if (start == std::string::npos) {
            return "";
        }

        const size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }

    Date parseDate(const std::string& dateText) {
        const std::string value = trim(dateText);
        int day, month, year;
        char extra;

        if (std::sscanf(value.c_str(), "%d/%d/%d%c", &day, &month, &year, &extra) != 3) {
            throw InvalidDataException("Formato de Data inválido. Use dd/mm/aaaa.");
        }

        return Date(day, month, year);
    }

    Time parseTime(const std::string& timeText) {
        const std::string value = trim(timeText);
        int hour, minute;
        char extra;

        if (std::sscanf(value.c_str(), "%d:%d%c", &hour, &minute, &extra) != 2) {
            throw InvalidDataException("Formato de Hora inválido. Use hh:mm.");
        }

        return Time(hour, minute);
    }
}

ServiceService::ServiceService(Clinic& clinic) : clinic(clinic) {}

void ServiceService::addService(const ServiceInDTO& dto) {
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

    int id = clinic.getServiceContainer().getNextId();
    Date date = parseDate(dto.date);
    Time time = parseTime(dto.time);

    Service service(id, dto.type, dto.cost, date, time, animal, veterinarian);
    clinic.getServiceContainer().add(service);
}

std::vector<ServiceOutDTO> ServiceService::getAllServices() {
    std::vector<Service>& services = clinic.getServiceContainer().getAll();
    return ServiceMapper::toDTOList(services);
}

std::vector<ServiceOutDTO> ServiceService::getServicesByVeterinarianId(int veterinarianId) {
    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    std::vector<ServiceOutDTO> result;
    std::vector<Service>& services = clinic.getServiceContainer().getAll();

    for (const Service& service : services) {
        if (service.getVeterinarian() == veterinarian) {
            result.push_back(ServiceMapper::toDTO(service));
        }
    }

    return result;
}