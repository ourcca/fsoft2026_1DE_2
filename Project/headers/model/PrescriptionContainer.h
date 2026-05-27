/*
PrescriptionContainer.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_PRESCRIPTIONCONTAINER_H_
#define HEADERS_MODEL_PRESCRIPTIONCONTAINER_H_

#include <vector>

#include "Prescription.h"

class PrescriptionContainer {
private:
    std::vector<Prescription> prescriptions;
    std::vector<Prescription>::iterator findByID(int id);
public:
    void add(const Prescription& prescription);
    void remove(int id);
    Prescription* get(int id);
    std::vector<Prescription>& getAll();
    int getNextId();

};

#endif
