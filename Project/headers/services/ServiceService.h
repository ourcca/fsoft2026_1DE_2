/*
ServiceService.h

Created on: 16/05/2026
*/
#ifndef HEADERS_SERVICES_SERVICESERVICE_H_
#define HEADERS_SERVICES_SERVICESERVICE_H_

#include <vector>
#include <string>

#include "model/Clinic.h"
#include "dto/ServiceInDTO.h"
#include "dto/ServiceOutDTO.h"

class ServiceService {
private:
    Clinic& clinic;

public:
    ServiceService(Clinic& clinic);

    void validateVeterinarianSpecialty(int veterinrianId, bool requiresSpecialty, const std::string& requiredSpecialty);

    void addService(const ServiceInDTO& dto);
    std::vector<ServiceOutDTO> getAllServices();
    std::vector<ServiceOutDTO> getServicesByVeterinarianId(int veterinarianId);
};

#endif