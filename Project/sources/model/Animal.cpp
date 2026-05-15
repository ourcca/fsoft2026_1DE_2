/*
    Animal.cpp

    Created on: 15/05/2026
 */
#include "model/Animal.h"

Animal::Animal(const int id, const std::string &name, const std::string &species, const std::string &breed, const float weight, const int age) {
    this->id = id;
    this->name = name;
    this->species = species;
    this->breed = breed;
    this->weight = weight;
    this->age = age;
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

void Animal::setName(std::string name) {
    this->name = name;
}

void Animal::setSpecies(std::string species) {
    this->species = species;
}

void Animal::setBreed(std::string breed) {
    this->breed = breed;
}

void Animal::setWeight(float weight) {
    this->weight = weight;
}

void Animal::setAge(int age) {
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
