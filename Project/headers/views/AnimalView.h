/*
AnimalView.h

Created on: 15/05/2026
*/
#ifndef HEADERS_VIEWS_ANIMALVIEW_H_
#define HEADERS_VIEWS_ANIMALVIEW_H_

#include <vector>
#include <string>

#include "dto/AnimalInDTO.h"
#include "dto/AnimalOutDTO.h"

class AnimalView {
public:
    static int menu();

    void showAnimalCreated();

    void showAnimalUpdated();

    void showAnimalRemoved();

    void showAnimalRemoveCancelled();

    bool confirmRemoveAssociatedData(int prescriptionCount, int serviceCount);

    void printAnimals(const std::vector<AnimalOutDTO>& animals);

    std::string getName();

    std::string getSpecies();

    std::string getBreed();

    std::string getBreed(const std::string& species);

    float getWeight();

    int getAge();

    int getAnimalId();

    void printAnimal(const AnimalOutDTO& animal);

    void showAnimalNotFound();

};

#endif