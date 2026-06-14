//
// Created by rodri on 14/06/2026.
//

#ifndef VETERINARYCLINIC_SERVICECATALOG_H
#define VETERINARYCLINIC_SERVICECATALOG_H

#include <string>
#include <vector>

namespace ServiceCatalog {
    std::string normalizeKey(const std::string& value);

    bool isValidSpecialty(const std::string& specialty);
    bool isValidServiceType(const std::string& serviceType);
    bool requiresExoticAnimal(const std::string& serviceType);

    std::string requiredSpecialtyForService(const std::string& serviceType);

    std::vector<std::string> getSpecialties();
    std::vector<std::string> getServiceTypes();
}

#endif //VETERINARYCLINIC_SERVICECATALOG_H