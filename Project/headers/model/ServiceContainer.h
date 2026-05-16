/*
ServiceContainer.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_SERVICECONTAINER_H_
#define HEADERS_MODEL_SERVICECONTAINER_H_

#include <vector>

#include "Service.h"

class ServiceContainer {
private:
    std::vector<Service> services;
    std::vector<Service>::iterator findByID(int id);

public:
    void add(const Service& service);
    void remove(int id);
    Service* get(int id);
    std::vector<Service>& getAll();
};

#endif