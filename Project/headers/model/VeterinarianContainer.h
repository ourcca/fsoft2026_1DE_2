/*
VeterinarianlContainer.h

    Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_VETERINARIANCONTAINER_H_
#define HEADERS_MODEL_VETERINARIANCONTAINER_H_

#include <deque>
#include <string>
#include "Veterinarian.h"

class VeterinarianContainer {
    private:
        std::deque<Veterinarian> veterinarians;
        std::deque<Veterinarian>::iterator findByID(int id);
    public:
        void add(const Veterinarian& veterinarian);
        void remove(int id);
        Veterinarian* get(int id);
        std::deque<Veterinarian>& getAll();
        int getNextId();
        Veterinarian* edit(int id, const std::string& name, int age, const std::string& specialty);
};

#endif