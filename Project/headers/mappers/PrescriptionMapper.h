/*
PrescriptionMapper.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MAPPERS_PRESCRIPTIONMAPPER_H_
#define HEADERS_MAPPERS_PRESCRIPTIONMAPPER_H_

#include <vector>

#include "model/Prescription.h"
#include "dto/PrescriptionOutDTO.h"

class PrescriptionMapper {
public:
    static PrescriptionOutDTO toDTO(const Prescription& prescription);
    static std::vector<PrescriptionOutDTO> toDTOList(const std::vector<Prescription>& prescriptions);
};

#endif