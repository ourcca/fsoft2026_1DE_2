/*
    AnimalContainer.h

    Created on: 15/05/2026
*/
#ifndef HEADERS_MODEL_ANIMALCONTAINER_H_
#define HEADERS_MODEL_ANIMALCONTAINER_H_

#include <deque>
#include "Animal.h"

class  AnimalContainer {
    private:
        std::deque<Animal> animals;
        std::deque<Animal>::iterator findByID(int id);
    public:
        void add(const Animal& animal);
        void remove(int id);
        Animal* get(int id);
        std::deque<Animal>& getAll();
        int getNextId();
        Animal* edit(int id, const std::string& name, const std::string& species, const std::string& breed,float weight,int age);
};

#endif