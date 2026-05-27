/*
ServiceService.cpp

Created on: 16/05/2026
*/
#include "services/ServiceService.h"

#include "model/Service.h"
#include "mappers/ServiceMapper.h"

ServiceService::ServiceService(Clinic& clinic) : clinic(clinic) {}

void ServiceService::addService(const ServiceInDTO& dto) {
    Animal* animal = clinic.getAnimalContainer().get(dto.animalId);
    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(dto.veterinarianId);

    if (animal == nullptr || veterinarian == nullptr) {
        return;
    }

    int id = clinic.getServiceContainer().getNextId();

    Service service(id, dto.type, dto.cost, dto.date, dto.time, animal, veterinarian);
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