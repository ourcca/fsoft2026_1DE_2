/*
    Animal.cpp

    Created on: 15/05/2026
 */
#include "model/Animal.h"
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

Animal::Animal(const int id, const std::string &name, const std::string &species, const std::string &breed, const float weight, const int age) {
    setId(id);
    setName(name);
    setSpecies(species);
    setBreed(breed);
    setWeight(weight);
    setAge(age);
}

Animal::Animal(const Animal& animal) {
    this->id = animal.id;
    this->name = animal.name;
    this->species = animal.species;
    this->breed = animal.breed;
    this->weight = animal.weight;
    this->age = animal.age;
}

void Animal::setId(int id) {
    this->id = id;
}

void Animal::setName(const std::string& name) {
    if (name.empty()) {
        throw InvalidDataException("Nome de Animal não pode estar vazio.");
    }
    this->name = name;
}

void Animal::setSpecies(const std::string& species) {
    if (species.empty()) {
        throw InvalidDataException("Espécie de Animal não pode estar vazia.");
    }
    this->species = species;
}

void Animal::setBreed(const std::string& breed) {
    this->breed = breed;
}

void Animal::setWeight(float weight) {
    if (weight <= 0) {
        throw InvalidDataException("Peso de Animal tem de ser positivo.");
    }
    this->weight = weight;
}

void Animal::setAge(int age) {
    if (age < 0) {
        throw InvalidDataException("Idade de Animal não pode ser negativa.");
    }
    this->age = age;
}

const int& Animal::getId() const {
    return this->id;
}

const std::string& Animal::getName() const {
    return this->name;
}

const std::string& Animal::getSpecies() const {
    return this->species;
}

const std::string& Animal::getBreed() const {
    return this->breed;
}

const float& Animal::getWeight() const {
    return this->weight;
}

int Animal::getAge() const {
    return this->age;
}

bool Animal::operator==(const Animal& obj) const {
    return this->id == obj.id;
}
