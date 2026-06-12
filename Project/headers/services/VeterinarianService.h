/*
VeterinarianService.h

Created on: 16/05/2026
*/
#ifndef HEADERS_SERVICES_VETERINARIANSERVICE_H_
#define HEADERS_SERVICES_VETERINARIANSERVICE_H_

#include <vector>

#include "model/Clinic.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"

class VeterinarianService {
private:
    Clinic& clinic;

public:
    VeterinarianService(Clinic& clinic);

    void addVeterinarian(const VeterinarianInDTO& dto);
    std::vector<VeterinarianOutDTO> getAllVeterinarians();
    VeterinarianOutDTO getVeterinarianById(int id);
    void editVeterinarian(int id, const VeterinarianInDTO& dto);
};

#endif