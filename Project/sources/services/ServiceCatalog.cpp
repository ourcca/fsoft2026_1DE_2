//
// Created by rodri on 14/06/2026.
//

#include "services/ServiceCatalog.h"

#include <algorithm>
#include <cctype>

namespace {
    struct ServiceRule {
        std::string serviceType;
        std::string requiredSpecialty;
        bool requiresExoticAnimal;
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

    const std::vector<std::string>& specialties() {
        static const std::vector<std::string> values = {
            "Cirurgia",
            "Dermatologia",
            "Cardiologia",
            "Odontologia",
            "Ortopedia",
            "Oftalmologia",
            "Imagiologia",
            "Animais Exóticos"
        };

        return values;
    }

    const std::vector<ServiceRule>& serviceRules() {
        static const std::vector<ServiceRule> rules = {
            {"Consulta Geral", "", false},
            {"Vacinação", "", false},
            {"Desparasitação", "", false},
            {"Check-up", "", false},

            {"Cirurgia", "Cirurgia", false},
            {"Consulta de Dermatologia", "Dermatologia", false},
            {"Consulta de Cardiologia", "Cardiologia", false},
            {"Destartarização", "Odontologia", false},
            {"Consulta de Ortopedia", "Ortopedia", false},
            {"Consulta de Oftalmologia", "Oftalmologia", false},
            {"Raio-X", "Imagiologia", false},
            {"Ecografia", "Imagiologia", false},

            {"Consulta de Animais Exóticos", "Animais Exóticos", true},
            {"Cuidados de Animais Exóticos", "Animais Exóticos", true}
        };

        return rules;
    }
}

std::string ServiceCatalog::normalizeKey(const std::string& value) {
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

    if (normalized == "geral" ||
        normalized == "sem especialidade" ||
        normalized == "sem especializacao" ||
        normalized == "nenhuma") {
        return "";
    }

    return normalized;
}

bool ServiceCatalog::isValidSpecialty(const std::string& specialty) {
    const std::string specialtyKey = normalizeKey(specialty);

    if (specialtyKey.empty()) {
        return true;
    }

    for (const std::string& availableSpecialty : specialties()) {
        if (normalizeKey(availableSpecialty) == specialtyKey) {
            return true;
        }
    }

    return false;
}

bool ServiceCatalog::isValidServiceType(const std::string& serviceType) {
    const std::string serviceKey = normalizeKey(serviceType);

    if (serviceKey.empty()) {
        return false;
    }

    for (const ServiceRule& rule : serviceRules()) {
        if (normalizeKey(rule.serviceType) == serviceKey) {
            return true;
        }
    }

    return false;
}

std::string ServiceCatalog::requiredSpecialtyForService(const std::string& serviceType) {
    const std::string serviceKey = normalizeKey(serviceType);

    for (const ServiceRule& rule : serviceRules()) {
        if (normalizeKey(rule.serviceType) == serviceKey) {
            return rule.requiredSpecialty;
        }
    }

    return "__INVALID_SERVICE__";
}

std::vector<std::string> ServiceCatalog::getSpecialties() {
    return specialties();
}

std::vector<std::string> ServiceCatalog::getServiceTypes() {
    std::vector<std::string> result;

    for (const ServiceRule& rule : serviceRules()) {
        result.push_back(rule.serviceType);
    }

    return result;
}

bool ServiceCatalog::requiresExoticAnimal(const std::string& serviceType) {
    const std::string serviceKey = normalizeKey(serviceType);

    for (const ServiceRule& rule : serviceRules()) {
        if (normalizeKey(rule.serviceType) == serviceKey) {
            return rule.requiresExoticAnimal;
        }
    }

    return false;
}
