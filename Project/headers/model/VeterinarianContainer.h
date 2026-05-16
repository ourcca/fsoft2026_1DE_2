/*
VeterinarianlContainer.h

    Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_VETERINARIANCONTAINER_H_
#define HEADERS_MODEL_VETERINARIANCONTAINER_H_

#include <vector>
#include "Veterinarian.h"

class VeterinarianContainer {
    private:
        std::vector<Veterinarian> veterinarians;
        std::vector<Veterinarian>::iterator findByID(int id);
    public:
        void add(const Veterinarian& veterinarian);
        void remove(int id);
        std::vector<Veterinarian>& getAll();
};

#endif