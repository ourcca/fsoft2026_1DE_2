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

Animal::Animal(int id, const std::string &name, const std::string &species, const std::string &breed, float weight, int age) {
    setId(id);
    setName(name);
    setSpecies(species);
    setBreed(breed);
    setWeight(weight);
    setAge(age);
}

Animal::Animal(const Animal& animal) {
    setId(animal.id);
    setName(animal.name);
    setSpecies(animal.species);
    setBreed(animal.breed);
    setWeight(animal.weight);
    setAge(animal.age);
}

void Animal::setId(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Animal tem de ser positivo.");
    }
    this->id = id;
}

void Animal::setName(const std::string& name) {
    std::string trimmed_name = trim(name);
    if (trimmed_name.empty()) {
        throw InvalidDataException("Nome de Animal não pode estar vazio.");
    }
    this->name = trimmed_name;
}

void Animal::setSpecies(const std::string& species) {
    std::string trimmed_species = trim(species);
    if (trimmed_species.empty()) {
        throw InvalidDataException("Espécie de Animal não pode estar vazia.");
    }
    this->species = trimmed_species;
}

void Animal::setBreed(const std::string& breed) {
    this->breed = trim(breed);
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

int Animal::getId() const {
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

float Animal::getWeight() const {
    return this->weight;
}

int Animal::getAge() const {
    return this->age;
}

bool Animal::operator==(const Animal& obj) const {
    return this->id == obj.id;
}
