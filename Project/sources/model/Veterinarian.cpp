/*
Veterinarian.cpp

Created on: 16/05/2026
*/
#include "model/Veterinarian.h"
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

Veterinarian::Veterinarian(int id, const std::string& name, int age,const std::string& specialty) {
    setId(id);
    setName(name);
    setAge(age);
    setSpecialty(specialty);
}

Veterinarian::Veterinarian(const Veterinarian &veterinarian) {
    setId(veterinarian.id);
    setName(veterinarian.name);
    setAge(veterinarian.age);
    setSpecialty(veterinarian.specialty);
}

void Veterinarian::setId(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário tem de ser positivo.");
    }
    this->id = id;
}

void Veterinarian::setName(const std::string& name) {
    std::string trimmed_name = trim(name);
    if (trimmed_name.empty()) {
        throw InvalidDataException("Nome de Veterinário não pode estar vazio.");
    }
    this->name = trimmed_name;
}

void Veterinarian::setSpecialty(const std::string& specialty) {
    std::string trimmed_specialty = trim(specialty);
    if (trimmed_specialty.empty()) {
        throw InvalidDataException("Especialidade de Veterinário não pode estar vazia.");
    }
    this->specialty = trimmed_specialty;
}

void Veterinarian::setAge(int age) {
    if (age < 18) {
        throw InvalidDataException("Idade de Veterinário inválida.");
    }
    this->age = age;
}

int Veterinarian::getId() const {
    return this->id;
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