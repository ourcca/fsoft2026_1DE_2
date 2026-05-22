/*
VeterinarianlContainer.cpp

    Created on: 16/05/2026
*/
#include "model/VeterinarianContainer.h"

#include <algorithm>

std::vector<Veterinarian>::iterator VeterinarianContainer::findByID(int id) {
    return std::find_if(veterinarians.begin(), veterinarians.end(),
        [id](const Veterinarian& v) {
            return v.getId() == id;
        }
    );
}

void VeterinarianContainer::add(const Veterinarian& veterinarian) {
    veterinarians.push_back(veterinarian);
}

void VeterinarianContainer::remove(int id) {
    auto it = findByID(id);

    if (it != veterinarians.end()) {
        veterinarians.erase(it);
    }
}

Veterinarian* VeterinarianContainer::get(int id) {
    auto it = findByID(id);

    if (it != veterinarians.end()) {
        return &(*it);
    }

    return nullptr;
}

std::vector<Veterinarian>& VeterinarianContainer::getAll() {
    return veterinarians;
}
