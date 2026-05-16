/*
Veterinarian.cpp

Created on: 16/05/2026
*/
#include "model/Veterinarian.h"

Veterinarian::Veterinarian(const int id, const std::string name, int age,const std::string specialty) {
    this->id = id;
    this->name = name;
    this->specialty = specialty;
    this->age = age;
}

Veterinarian::Veterinarian(const Veterinarian &veterinarian) {
    this->id = veterinarian.id;
    this->name = veterinarian.name;
    this->age = veterinarian.age;
    this->specialty = veterinarian.specialty;
}

void Veterinarian::setId(int id) {
    this->id = id;
}

void Veterinarian::setName(std::string name) {
    this->name = name;
}

void Veterinarian::setSpecialty(std::string specialty) {
    this->specialty = specialty;
}

void Veterinarian::setAge(int age) {
    this->age = age;
}

const int& Veterinarian::getId() const {
    return this-> id;
}

const std::string& Veterinarian::getName() const {
    return this->name;
}

const std::string& Veterinarian::getSpecialty() const {
    return this->specialty;
}

int Veterinarian::getAge() const {
    return this->age;
}

bool Veterinarian::operator==(const Veterinarian& obj) const {
    return this->id == obj.id;
}