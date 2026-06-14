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

    void validateServiceStart(const ServiceInDTO& dto);
    void validateAnimalExists(int animalId);
    void validateVeterinarianExists(int veterinarianId);
    void validateVeterinarianCanDoService(int veterinarianId, const std::string& serviceType);
    void validateAnimalCanDoService(int animalId, const std::string& serviceType);
    void validateType(const std::string& type);
    void validateCost(float cost);
    void validateDateText(const std::string& dateText);
    void validateTimeText(const std::string& timeText);

    void addService(const ServiceInDTO& dto);
    std::vector<ServiceOutDTO> getAllServices();
    ServiceOutDTO getServiceById(int id);
    std::vector<ServiceOutDTO> getServicesByVeterinarianId(int veterinarianId);
    void editService(int id,const ServiceInDTO& dto);
    void removeService(int id);
};

#endif