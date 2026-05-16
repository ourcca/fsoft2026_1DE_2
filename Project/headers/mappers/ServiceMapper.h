/*
ServiceMapper.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MAPPERS_SERVICEMAPPER_H_
#define HEADERS_MAPPERS_SERVICEMAPPER_H_

#include <vector>

#include "model/Service.h"
#include "dto/ServiceOutDTO.h"

class ServiceMapper {
public:
    static ServiceOutDTO toDTO(const Service& service);
    static std::vector<ServiceOutDTO> toDTOList(const std::vector<Service>& services);
};

#endif