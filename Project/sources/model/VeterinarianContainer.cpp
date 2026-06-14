/*
VeterinarianlContainer.cpp

    Created on: 16/05/2026
*/
#include "model/VeterinarianContainer.h"
#include "exceptions/DuplicatedDataException.h"
#include <algorithm>

#include "exceptions/NoDataException.h"

std::deque<Veterinarian>::iterator VeterinarianContainer::findByID(int id) {
    return std::find_if(veterinarians.begin(), veterinarians.end(),
        [id](const Veterinarian& v) {
            return v.getId() == id;
        }
    );
}

void VeterinarianContainer::add(const Veterinarian& veterinarian) {
    if (get(veterinarian.getId()) != nullptr)
        throw DuplicatedDataException("Veterinário já existe.");
    veterinarians.push_back(veterinarian);
}

void VeterinarianContainer::remove(int id) {
    auto it = findByID(id);

    if (it == veterinarians.end()) {
        throw NoDataException("Veterinário não existe.");
    }

    veterinarians.erase(it);
}

Veterinarian* VeterinarianContainer::get(int id) {
    auto it = findByID(id);

    if (it != veterinarians.end()) {
        return &(*it);
    }

    return nullptr;
}

std::deque<Veterinarian>& VeterinarianContainer::getAll() {
    return veterinarians;
}

int VeterinarianContainer::getNextId() {
    int maxId = 0;

    for (const Veterinarian& veterinarian : veterinarians) {
        if (veterinarian.getId() > maxId) {
            maxId = veterinarian.getId();
        }
    }

    return maxId + 1;
}

Veterinarian* VeterinarianContainer::edit(int id, const std::string& name, int age,const std::string& specialty) {
    Veterinarian* veterinarian = get(id);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não existe.");
    }

    Veterinarian updated(*veterinarian);
    updated.setName(name);
    updated.setAge(age);
    updated.setSpecialty(specialty);

    *veterinarian = updated;

    return veterinarian;
}