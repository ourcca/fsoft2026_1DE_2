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
#include "model/Date.h"
#include "model/Time.h"

ServiceService::ServiceService(Clinic& clinic) : clinic(clinic) {}

void ServiceService::addService(const ServiceInDTO& dto) {
    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    if (animal == nullptr || veterinarian == nullptr) {
        throw DataConsistencyException("Animal ou veterinario nao existe.");
    }

    int id = clinic.getServiceContainer().getNextId();

    int day, month, year;
    if (sscanf(dto.date.c_str(), "%d/%d/%d",
           &day, &month, &year) != 3) {
        throw InvalidDataException("Invalid date format.");
    }
    Date date(day, month, year);

    int hour, minute;
    if (sscanf(dto.time.c_str(), "%d:%d",
        &hour, &minute) != 2) {
        throw InvalidDataException("Invalid time format.");
    }
    Time time(hour, minute);

    Service service(id, dto.type, dto.cost, date, time, animal, veterinarian);
    clinic.getServiceContainer().add(service);
}

std::vector<ServiceOutDTO> ServiceService::getAllServices() {
    std::vector<Service>& services = clinic.getServiceContainer().getAll();
    return ServiceMapper::toDTOList(services);
}

std::vector<ServiceOutDTO> ServiceService::getServicesByVeterinarianId(int veterinarianId) {
    std::vector<ServiceOutDTO> result;

    std::vector<Service>& services = clinic.getServiceContainer().getAll();

    for (const Service& service : services) {
        if (service.getVeterinarian() != nullptr &&
            service.getVeterinarian()->getId() == veterinarianId) {
            result.push_back(ServiceMapper::toDTO(service));
            }
    }

    return result;
}