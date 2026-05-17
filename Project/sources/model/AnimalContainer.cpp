/*
AnimalContainer.cpp

Created on: 15/05/2026
 */
#include "model/AnimalContainer.h"

#include <algorithm>

std::vector<Animal>::iterator AnimalContainer::findByID(int id) {
    return std::find_if(animals.begin(), animals.end(),
        [id](const Animal& animal) {
            return animal.getId() == id;
        }
    );
}

void AnimalContainer::add(const Animal& animal) {
    animals.push_back(animal);
}

void AnimalContainer::remove(int id) {
    auto it = findByID(id);

    if (it != animals.end()) {
        animals.erase(it);
    }
}

std::vector<Animal>& AnimalContainer::getAll() {
    return animals;
}

Animal* AnimalContainer::get(int id) {
    auto it = findByID(id);

    if (it != animals.end()) {
        return &(*it);
    }

    return nullptr;
}