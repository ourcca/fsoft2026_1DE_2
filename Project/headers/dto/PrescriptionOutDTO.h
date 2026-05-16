/*
PrescriptionOutDTO.cpp

Created on: 16/05/2026
*/
#ifndef HEADERS_DTO_PRESCRIPTIONOUTDTO_H_
#define HEADERS_DTO_PRESCRIPTIONOUTDTO_H_

#include <string>

struct PrescriptionOutDTO {
    int id;
    std::string medication;
    std::string quantity;
    std::string duration;
    int animalId;
    int veterinarianId;
};

#endif