/*
Service.cpp

Created on: 16/05/2026
*/
#include "model/Service.h"
#include "exceptions/InvalidDataException.h"

namespace {
    std::string trim(const std::string& value) {
        const std::string whitespace = " \t\n\r\f\v";
        const size_t start = value.find_first_not_of(whitespace);

        if (start == std::string::npos) {
            return "";
        }

        const size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }
}

Service::Service(int id,const std::string& type, float cost,const Date& date,const Time& time,
                 Animal* animal, Veterinarian* veterinarian) {
    setId(id);
    setType(type);
    setCost(cost);
    setDate(date);
    setTime(time);
    setAnimal(animal);
    setVeterinarian(veterinarian);
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

void Service::setType(const std::string& type) {
    if (type.empty()) {
        throw InvalidDataException("Tipo de Serviço não pode estar vazio.");
    }
    this->type = type;
}

void Service::setCost(float cost) {
    if (cost <= 0) {
        throw InvalidDataException("Custo de Serviço tem de ser positivo.");
    }
    this->cost = cost;
}

void Service::setDate(const Date& date) {
    this->date = date;
}

void Service::setTime(const Time& time) {
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

const Date& Service::getDate() const {
    return this->date;
}

const Time& Service::getTime() const {
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