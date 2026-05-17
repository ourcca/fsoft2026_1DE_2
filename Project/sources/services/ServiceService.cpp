/*
ServiceService.cpp

Created on: 16/05/2026
*/
#include "services/ServiceService.h"

#include "model/Service.h"
#include "mappers/ServiceMapper.h"

ServiceService::ServiceService(Clinic& clinic) : clinic(clinic) {}

void ServiceService::addService(const ServiceInDTO& dto) {
    Service service(dto.id, dto.type, dto.cost, dto.date, dto.time, dto.animalId, dto.veterinarianId);
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
        if (service.getVeterinarianId() == veterinarianId) {
            result.push_back(ServiceMapper::toDTO(service));
        }
    }

    return result;
}