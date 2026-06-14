/*
ServiceView.h

Created on: 16/05/2026
*/
#ifndef HEADERS_VIEWS_SERVICEVIEW_H_
#define HEADERS_VIEWS_SERVICEVIEW_H_

#include <vector>
#include <string>

#include "dto/ServiceInDTO.h"
#include "dto/ServiceOutDTO.h"

class ServiceView {
public:
    int menu();

    int getAnimalId();
    int getVeterinarianId();
    int getServiceId();
    std::string getType();
    float getCost();
    std::string getDate();
    std::string getTime();

    ServiceInDTO getVeterinarianSpecialtyRequirement(const ServiceInDTO& dto);

    void showServiceCreated();
    void showServiceUpdated();
    void showServiceRemoved();

    void printService(const ServiceOutDTO& service);
    void printServices(const std::vector<ServiceOutDTO>& services);
};

#endif