/*
VeterinarianView.h

Created on: 16/05/2026
*/
#ifndef HEADERS_VIEWS_VETERINARIANVIEW_H_
#define HEADERS_VIEWS_VETERINARIANVIEW_H_

#include <vector>

#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"

class VeterinarianView {
public:
    int menu();

    VeterinarianInDTO getVeterinarian();

    void showVeterinarianCreated();
    void printVeterinarians(const std::vector<VeterinarianOutDTO>& veterinarians);
};

#endif