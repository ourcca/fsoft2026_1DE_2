/*
PrescriptionService.h

Created on: 16/05/2026
*/
#ifndef HEADERS_SERVICES_PRESCRIPTIONSERVICE_H_
#define HEADERS_SERVICES_PRESCRIPTIONSERVICE_H_

#include <vector>
#include <string>

#include "model/Clinic.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"

class PrescriptionService {
private:
    Clinic& clinic;

public:
    PrescriptionService(Clinic& clinic);

    void validateAnimalExists(int animalId);
    void validateVeterinarianExists(int veterinarianId);
    void validateMedication(const std::string& medication);
    void validateQuantity(const std::string& quantity);
    void validateDuration(const std::string& duration);
    void addPrescription(const PrescriptionInDTO& dto);
    std::vector<PrescriptionOutDTO> getAllPrescriptions();
    std::vector<PrescriptionOutDTO> getPrescriptionsByAnimalId(int animalId);
    PrescriptionOutDTO getPrescriptionById(int id);
    void editPrescription(int id, const PrescriptionInDTO& dto);
    void removePrescription(int id);
};

#endif