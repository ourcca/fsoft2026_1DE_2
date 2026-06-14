/*
ServiceService.cpp

Created on: 16/05/2026
*/
#include <cstdio>
#include <algorithm>
#include <cctype>
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

    std::string normalize(const std::string& value) {
        std::string normalized = trim(value);

        std::transform(normalized.begin(), normalized.end(), normalized.begin(),
            [](unsigned char character) {
                return static_cast<char>(std::tolower(character));
            });

        return normalized;
    }
}

ServiceService::ServiceService(Clinic& clinic) : clinic(clinic) {}

void ServiceService::validateServiceStart(const ServiceInDTO& dto) {
    validateAnimalExists(dto.animalId);
    validateVeterinarianExists(dto.veterinarianId);

    validateVeterinarianSpecialty(
        dto.veterinarianId,
        dto.requiresVeterinarianSpecialty,
        dto.requiredVeterinarianSpecialty
    );
}

void ServiceService::validateAnimalExists(int animalId) {
    if (animalId <= 0) {
        throw InvalidDataException("ID de Animal inválido.");
    }

    Animal* animal = clinic.getAnimalContainer().get(animalId);

    if (animal == nullptr) {
        throw DataConsistencyException("Animal não existe.");
    }
}

void ServiceService::validateVeterinarianExists(int veterinarianId) {
    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw DataConsistencyException("Veterinário não existe.");
    }
}

void ServiceService::validateVeterinarianSpecialty(int veterinarianId, bool requiresSpecialty,
    const std::string& requiredSpecialty) {

    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw DataConsistencyException("Veterinário não existe.");
    }

    const std::string normalizedVeterinarianSpecialty = normalize(veterinarian->getSpecialty());

    if (!requiresSpecialty) {
        if (!normalizedVeterinarianSpecialty.empty()) {
            throw DataConsistencyException("Serviço sem especialização só pode ser realizado por Veterinário sem especialidade.");
        }

        return;
    }

    const std::string normalizedRequiredSpecialty = normalize(requiredSpecialty);

    if (normalizedRequiredSpecialty.empty()) {
        throw InvalidDataException("Especialidade necessária não pode estar vazia.");
    }

    if (normalizedVeterinarianSpecialty != normalizedRequiredSpecialty) {
        throw DataConsistencyException("Veterinário sem especificação necessária.");
    }
}

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

    validateVeterinarianSpecialty(
        dto.veterinarianId,
        dto.requiresVeterinarianSpecialty,
        dto.requiredVeterinarianSpecialty
        );

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

ServiceOutDTO ServiceService::getServiceById(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Serviço inválido.");
    }

    Service* service = clinic.getServiceContainer().get(id);

    if (service == nullptr) {
        throw NoDataException("Serviço não encontrado.");
    }

    return ServiceMapper::toDTO(*service);
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

void ServiceService::editService(int id, const ServiceInDTO& dto) {
    if (id <= 0) {
        throw InvalidDataException("ID de Serviço inválido.");
    }

    validateServiceStart(dto);
    validateType(dto.type);
    validateCost(dto.cost);

    Date date = parseDate(dto.date);
    Time time = parseTime(dto.time);

    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    clinic.getServiceContainer().edit(
        id,
        dto.type,
        dto.cost,
        date,
        time,
        animal,
        veterinarian
    );
}

void ServiceService::removeService(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Serviço inválido.");
    }

    Service* service = clinic.getServiceContainer().get(id);

    if (service == nullptr) {
        throw NoDataException("Servico não encontrado.");
    }

    clinic.getServiceContainer().remove(id);
}

void ServiceService::validateType(const std::string& type) {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    Date date(1, 1, 1900);
    Time time(0, 0);

    Service service(1, "Consulta", 1.0f, date, time, &animal, &veterinarian);
    service.setType(type);
}

void ServiceService::validateCost(float cost) {
    Animal animal(1, "Nome", "Espécie", "", 1.0f, 0);
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    Date date(1, 1, 1900);
    Time time(0, 0);

    Service service(1, "Consulta", 1.0f, date, time, &animal, &veterinarian);
    service.setCost(cost);
}

void ServiceService::validateDateText(const std::string& dateText) {
    parseDate(dateText);
}

void ServiceService::validateTimeText(const std::string& timeText) {
    parseTime(timeText);
}
