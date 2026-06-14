//
// Created by rodri on 14/06/2026.
//
#include "services/PrescriptionCatalog.h"

#include <algorithm>
#include <cctype>

namespace {
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

    const std::vector<std::string>& medications() {
        static const std::vector<std::string> values = {
            "Amoxicilina",
            "Cefalexina",
            "Doxiciclina",
            "Metronidazol",
            "Meloxicam",
            "Carprofeno",
            "Prednisolona",
            "Tramadol",
            "Gabapentina",
            "Ivermectina",
            "Praziquantel",
            "Selamectina",
            "Itraconazol",
            "Maropitant",
            "Insulina"
        };

        return values;
    }
}

std::string PrescriptionCatalog::normalizeKey(const std::string& value) {
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

bool PrescriptionCatalog::isValidMedication(const std::string& medication) {
    const std::string medicationKey = normalizeKey(medication);

    if (medicationKey.empty()) {
        return false;
    }

    for (const std::string& availableMedication : medications()) {
        if (normalizeKey(availableMedication) == medicationKey) {
            return true;
        }
    }

    return false;
}

std::vector<std::string> PrescriptionCatalog::getMedications() {
    return medications();
}