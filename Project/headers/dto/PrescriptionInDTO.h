/*
PrescriptionInDTO.cpp

Created on: 16/05/2026
*/
#ifndef HEADERS_DTO_PRESCRIPTIONINDTO_H_
#define HEADERS_DTO_PRESCRIPTIONINDTO_H_

#include <string>

struct PrescriptionInDTO {
    std::string medication;
    std::string quantity;
    std::string duration;
    int animalId{};
    int veterinarianId{};
};

#endif