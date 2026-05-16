/*
ServiceInDTO.h

Created on: 16/05/2026
*/
#ifndef HEADERS_DTO_SERVICEOUTDTO_H_
#define HEADERS_DTO_SERVICEOUTDTO_H_

#include <string>

struct ServiceOutDTO {
    int id;
    std::string type;
    float cost;
    std::string date;
    std::string time;
    int animalId;
    int veterinarianId;
};

#endif