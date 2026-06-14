//
// Created by rodri on 14/06/2026.
//

#ifndef HEADERS_SERVICES_PRESCRIPTIONCATALOG_H_
#define HEADERS_SERVICES_PRESCRIPTIONCATALOG_H_

#include <string>
#include <vector>

namespace PrescriptionCatalog {
    std::string normalizeKey(const std::string& value);

    bool isValidMedication(const std::string& medication);

    std::vector<std::string> getMedications();
}

#endif //VETERINARYCLINIC_PRESCRIPTIONCATALOG_H