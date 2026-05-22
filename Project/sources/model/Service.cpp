/*
Service.cpp

Created on: 16/05/2026
*/
#include "model/Service.h"

Service::Service(int id, std::string type, float cost, std::string date, std::string time,
                 Animal* animal, Veterinarian* veterinarian) {
    this->id = id;
    this->type = type;
    this->cost = cost;
    this->date = date;
    this->time = time;
    this->animal = animal;
    this->veterinarian = veterinarian;
}

Service::Service(const Service& service) {
    this->id = service.id;
    this->type = service.type;
    this->cost = service.cost;
    this->date = service.date;
    this->time = service.time;
    this->animal = service.animal;
    this->veterinarian = service.veterinarian;
}

void Service::setId(int id) {
    this->id = id;
}

void Service::setType(std::string type) {
    this->type = type;
}

void Service::setCost(float cost) {
    this->cost = cost;
}

void Service::setDate(std::string date) {
    this->date = date;
}

void Service::setTime(std::string time) {
    this->time = time;
}

void Service::setAnimal(Animal*animal) {
    this->animal = animal;
}

void Service::setVeterinarian(Veterinarian*veterinarian) {
    this->veterinarian = veterinarian;
}

const int& Service::getId() const {
    return this->id;
}

const std::string& Service::getType() const {
    return this->type;
}

const float& Service::getCost() const {
    return this->cost;
}

const std::string& Service::getDate() const {
    return this->date;
}

const std::string& Service::getTime() const {
    return this->time;
}

Animal* Service::getAnimal() const {
    return this->animal;
}

Veterinarian* Service::getVeterinarian() const {
    return this->veterinarian;
}
bool Service::operator==(const Service& obj) const {
    return this->id == obj.id;
}