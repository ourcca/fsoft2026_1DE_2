/*
VeterinarianService.h

Created on: 16/05/2026
*/
#ifndef HEADERS_SERVICES_VETERINARIANSERVICE_H_
#define HEADERS_SERVICES_VETERINARIANSERVICE_H_

#include <vector>
#include <string>

#include "model/Clinic.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"

class VeterinarianService {
private:
    Clinic& clinic;

public:
    VeterinarianService(Clinic& clinic);

    void validateName(const std::string& name);
    void validateAge(int age);
    void validateSpecialty(const std::string& specialty);
    void addVeterinarian(const VeterinarianInDTO& dto);
    std::vector<VeterinarianOutDTO> getAllVeterinarians();
    VeterinarianOutDTO getVeterinarianById(int id);
    void editVeterinarian(int id, const VeterinarianInDTO& dto);

    int countPrescriptionsByVeterinarianId(int veterinarianId) const;
    int countServicesByVeterinarianId(int veterinarianId) const;
    bool hasAssociatedRecords(int veterinarianId) const;
    void removeVeterinarian(int id, bool removeAssociatedRecords);
};

#endif