/*
ServiceView.h

Created on: 16/05/2026
*/
#ifndef HEADERS_VIEWS_SERVICEVIEW_H_
#define HEADERS_VIEWS_SERVICEVIEW_H_

#include <vector>

#include "dto/ServiceInDTO.h"
#include "dto/ServiceOutDTO.h"

class ServiceView {
public:
    int menu();

    ServiceInDTO getServiceStart();
    ServiceInDTO getServiceDetails(const ServiceInDTO& dto);

    int getServiceId();

    void showServiceCreated();
    void showServiceUpdated();
    void printServices(const std::vector<ServiceOutDTO>& services);
    void printService(const ServiceOutDTO& service);
};

#endif