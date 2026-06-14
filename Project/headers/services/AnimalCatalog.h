//
// Created by rodri on 14/06/2026.
//

#ifndef HEADERS_SERVICES_ANIMALCATALOG_H_
#define HEADERS_SERVICES_ANIMALCATALOG_H_

#include <string>
#include <vector>

namespace AnimalCatalog {
    std::string normalizeKey(const std::string& value);

    bool isValidSpecies(const std::string& species);
    bool isCommonPetSpecies(const std::string& species);
    bool isExoticSpecies(const std::string& species);

    bool requiresBreed(const std::string& species);
    bool isValidBreedForSpecies(const std::string& species, const std::string& breed);

    std::vector<std::string> getCommonPetSpecies();
    std::vector<std::string> getExoticSpecies();
    std::vector<std::string> getBreedsForSpecies(const std::string& species);
}

#endif //VETERINARYCLINIC_ANIMALCATALOG_H