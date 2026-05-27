/*
ServiceContainer.cpp

Created on: 16/05/2026
*/
#include "model/ServiceContainer.h"

#include <algorithm>

std::vector<Service>::iterator ServiceContainer::findByID(int id) {
    return std::find_if(services.begin(), services.end(),
        [id](const Service& service) {
            return service.getId() == id;
        }
    );
}

void ServiceContainer::add(const Service& service) {
    services.push_back(service);
}

void ServiceContainer::remove(int id) {
    auto it = findByID(id);

    if (it != services.end()) {
        services.erase(it);
    }
}

Service* ServiceContainer::get(int id) {
    auto it = findByID(id);

    if (it != services.end()) {
        return &(*it);
    }

    return nullptr;
}

std::vector<Service>& ServiceContainer::getAll() {
    return services;
}

int ServiceContainer::getNextId() {
    int maxId = 0;

    for (const Service& service : services) {
        if (service.getId() > maxId) {
            maxId = service.getId();
        }
    }

    return maxId + 1;
}