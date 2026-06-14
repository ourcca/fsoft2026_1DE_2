/*
ServiceContainer.cpp

Created on: 16/05/2026
*/
#include "model/ServiceContainer.h"
#include "exceptions/DuplicatedDataException.h"
#include <algorithm>
#include "exceptions/NoDataException.h"

std::vector<Service>::iterator ServiceContainer::findByID(int id) {
    return std::find_if(services.begin(), services.end(),
        [id](const Service& service) {
            return service.getId() == id;
        }
    );
}

void ServiceContainer::add(const Service& service) {
    if (get(service.getId()) != nullptr)
        throw DuplicatedDataException("Serviço já existe.");
    services.push_back(service);
}

void ServiceContainer::remove(int id) {
    auto it = findByID(id);

    if (it == services.end()) {
        throw NoDataException("Serviço não existe.");
    }

    services.erase(it);
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

Service* ServiceContainer::edit(int id,const std::string& type,float cost,const Date& date,const Time& time,Animal* animal, Veterinarian* veterinarian) {
    Service* service = get(id);

    if (service == nullptr) {
        throw NoDataException("Serviço não existe.");
    }

    Service updated(*service);
    updated.setType(type);
    updated.setCost(cost);
    updated.setDate(date);
    updated.setTime(time);
    updated.setAnimal(animal);
    updated.setVeterinarian(veterinarian);

    *service = updated;

    return service;
}