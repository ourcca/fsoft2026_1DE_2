/*
PrescriptionService.h

Created on: 16/05/2026
*/
#ifndef HEADERS_SERVICES_PRESCRIPTIONSERVICE_H_
#define HEADERS_SERVICES_PRESCRIPTIONSERVICE_H_

#include <vector>

#include "model/Clinic.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"

class PrescriptionService {
private:
    Clinic& clinic;

public:
    PrescriptionService(Clinic& clinic);

    void addPrescription(const PrescriptionInDTO& dto);
    std::vector<PrescriptionOutDTO> getAllPrescriptions();
    std::vector<PrescriptionOutDTO> getPrescriptionsByAnimalId(int animalId);
};

#endif