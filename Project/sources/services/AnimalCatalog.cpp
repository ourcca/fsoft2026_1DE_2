//
// Created by rodri on 14/06/2026.
//
#include "services/AnimalCatalog.h"

#include <algorithm>
#include <cctype>

namespace {
    struct SpeciesRule {
        std::string species;
        std::vector<std::string> breeds;
    };

    std::string trim(const std::string& value) {
        const std::string whitespace = " \t\n\r\f\v";
        const size_t start = value.find_first_not_of(whitespace);

        if (start == std::string::npos) {
            return "";
        }

        const size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }

    void replaceAll(std::string& value, const std::string& from, const std::string& to) {
        size_t position = 0;

        while ((position = value.find(from, position)) != std::string::npos) {
            value.replace(position, from.length(), to);
            position += to.length();
        }
    }

    const std::vector<SpeciesRule>& commonPetRules() {
        static const std::vector<SpeciesRule> rules = {
            {
                "Cão",
                {
                    "Labrador",
                    "Golden Retriever",
                    "Pastor Alemão",
                    "Bulldog",
                    "Beagle",
                    "Poodle",
                    "Chihuahua",
                    "Yorkshire Terrier",
                    "Rafeiro",
                    "Sem Raça Definida",
                    "Outro"
                }
            },
            {
                "Gato",
                {
                    "Europeu Comum",
                    "Siamês",
                    "Persa",
                    "Maine Coon",
                    "Bengal",
                    "Ragdoll",
                    "Sphynx",
                    "Sem Raça Definida",
                    "Outro"
                }
            },
            {
                "Coelho",
                {
                    "Anão",
                    "Lop",
                    "Rex",
                    "Angorá",
                    "Outro"
                }
            },
            {
                "Ave",
                {
                    "Canário",
                    "Periquito",
                    "Calopsita",
                    "Papagaio",
                    "Agapornis",
                    "Outro"
                }
            },
            {
                "Hamster",
                {
                    "Sírio",
                    "Anão Russo",
                    "Roborovski",
                    "Chinês",
                    "Outro"
                }
            },
            {
                "Porquinho-da-Índia",
                {
                    "Abissínio",
                    "Peruano",
                    "Inglês",
                    "Sheltie",
                    "Outro"
                }
            }
        };

        return rules;
    }

    const std::vector<std::string>& exoticSpecies() {
        static const std::vector<std::string> values = {
            "Cobra",
            "Lagarto",
            "Tartaruga",
            "Iguana",
            "Camaleão",
            "Gecko",
            "Aranha",
            "Escorpião",
            "Furão"
        };

        return values;
    }
}

std::string AnimalCatalog::normalizeKey(const std::string& value) {
    std::string normalized = trim(value);

    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::tolower(character));
        });

    replaceAll(normalized, "á", "a");
    replaceAll(normalized, "à", "a");
    replaceAll(normalized, "â", "a");
    replaceAll(normalized, "ã", "a");
    replaceAll(normalized, "Á", "a");
    replaceAll(normalized, "À", "a");
    replaceAll(normalized, "Â", "a");
    replaceAll(normalized, "Ã", "a");

    replaceAll(normalized, "é", "e");
    replaceAll(normalized, "ê", "e");
    replaceAll(normalized, "É", "e");
    replaceAll(normalized, "Ê", "e");

    replaceAll(normalized, "í", "i");
    replaceAll(normalized, "Í", "i");

    replaceAll(normalized, "ó", "o");
    replaceAll(normalized, "ô", "o");
    replaceAll(normalized, "õ", "o");
    replaceAll(normalized, "Ó", "o");
    replaceAll(normalized, "Ô", "o");
    replaceAll(normalized, "Õ", "o");

    replaceAll(normalized, "ú", "u");
    replaceAll(normalized, "Ú", "u");

    replaceAll(normalized, "ç", "c");
    replaceAll(normalized, "Ç", "c");

    return normalized;
}

bool AnimalCatalog::isCommonPetSpecies(const std::string& species) {
    const std::string speciesKey = normalizeKey(species);

    for (const SpeciesRule& rule : commonPetRules()) {
        if (normalizeKey(rule.species) == speciesKey) {
            return true;
        }
    }

    return false;
}

bool AnimalCatalog::isExoticSpecies(const std::string& species) {
    const std::string speciesKey = normalizeKey(species);

    for (const std::string& exotic : exoticSpecies()) {
        if (normalizeKey(exotic) == speciesKey) {
            return true;
        }
    }

    return false;
}

bool AnimalCatalog::isValidSpecies(const std::string& species) {
    return isCommonPetSpecies(species) || isExoticSpecies(species);
}

bool AnimalCatalog::requiresBreed(const std::string& species) {
    return isCommonPetSpecies(species);
}

bool AnimalCatalog::isValidBreedForSpecies(const std::string& species, const std::string& breed) {
    if (!isValidSpecies(species)) {
        return false;
    }

    const std::string breedKey = normalizeKey(breed);

    if (isExoticSpecies(species)) {
        return breedKey.empty();
    }

    if (breedKey.empty()) {
        return false;
    }

    const std::string speciesKey = normalizeKey(species);

    for (const SpeciesRule& rule : commonPetRules()) {
        if (normalizeKey(rule.species) == speciesKey) {
            for (const std::string& availableBreed : rule.breeds) {
                if (normalizeKey(availableBreed) == breedKey) {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<std::string> AnimalCatalog::getCommonPetSpecies() {
    std::vector<std::string> result;

    for (const SpeciesRule& rule : commonPetRules()) {
        result.push_back(rule.species);
    }

    return result;
}

std::vector<std::string> AnimalCatalog::getExoticSpecies() {
    return exoticSpecies();
}

std::vector<std::string> AnimalCatalog::getBreedsForSpecies(const std::string& species) {
    const std::string speciesKey = normalizeKey(species);

    for (const SpeciesRule& rule : commonPetRules()) {
        if (normalizeKey(rule.species) == speciesKey) {
            return rule.breeds;
        }
    }

    return {};
}