/*
    AnimalContainer.h

    Created on: 15/05/2026
 */
#ifndef HEADERS_MODEL_ANIMALCONTAINER_H_
#define HEADERS_MODEL_ANIMALCONTAINER_H_

#include <vector>
#include "Animal.h"

class  AnimalContainer {
    private:
        std::vector<Animal> animals;
        std::vector<Animal>::iterator findByID(int id);
    public:
        void add(const Animal& animal);
        void remove(int id);
        std::vector<Animal>& getAll();
};

#endif