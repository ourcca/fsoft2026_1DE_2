/*
PrescriptionView.h

Created on: 16/05/2026
*/
#ifndef HEADERS_VIEWS_PRESCRIPTIONVIEW_H_
#define HEADERS_VIEWS_PRESCRIPTIONVIEW_H_

#include <vector>
#include <string>

#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"

class PrescriptionView {
public:
    int menu();

    PrescriptionInDTO getPrescription();

    void showPrescriptionCreated();
    void printPrescriptions(const std::vector<PrescriptionOutDTO>& prescriptions);

    int getAnimalId();
    std::string getMedication();
    std::string getQuantity();
    std::string getDuration();
    int getVeterinarianId();
};

#endif