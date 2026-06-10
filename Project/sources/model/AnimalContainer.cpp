/*
AnimalContainer.cpp

Created on: 15/05/2026
 */
#include "model/AnimalContainer.h"
#include "exceptions/DuplicatedDataException.h"
#include <algorithm>

#include "exceptions/NoDataException.h"

std::deque<Animal>::iterator AnimalContainer::findByID(int id) {
    return std::find_if(animals.begin(), animals.end(),
        [id](const Animal& animal) {
            return animal.getId() == id;
        }
    );
}

void AnimalContainer::add(const Animal& animal) {
    if (get(animal.getId()) != nullptr)
        throw DuplicatedDataException("Animal já existe.");
    animals.push_back(animal);
}

void AnimalContainer::remove(int id) {
    auto it = findByID(id);

    if (it != animals.end()) {
        animals.erase(it);
    }
}

std::deque<Animal>& AnimalContainer::getAll() {
    return animals;
}

Animal* AnimalContainer::get(int id) {
    auto it = findByID(id);

    if (it != animals.end()) {
        return &(*it);
    }

    return nullptr;
}

int AnimalContainer::getNextId() {
    int maxId = 0;

    for (const Animal& animal : animals) {
        if (animal.getId() > maxId) {
            maxId = animal.getId();
        }
    }

    return maxId + 1;
}

Animal* AnimalContainer::edit(int id, const std::string& name, const std::string& species,const std::string& breed, float weight, int age) {
    Animal* animal = get(id);

    if (animal == nullptr) {
        throw NoDataException("Animal não existe.");
    }

    animal->setName(name);
    animal->setSpecies(species);
    animal->setBreed(breed);
    animal->setWeight(weight);
    animal->setAge(age);

    return animal;
}