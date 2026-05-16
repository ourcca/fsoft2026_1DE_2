/*
Prescription.cpp

Created on: 16/05/2026
*/
#include "model/Prescription.h"

Prescription::Prescription(int id, std::string medication, std::string quantity, std::string duration, int animalId, int veterinarianId) {
    this->id = id;
    this->medication = medication;
    this->quantity = quantity;
    this->duration = duration;
    this->animalId = animalId;
    this->veterinarianId = veterinarianId;
}

Prescription::Prescription(const Prescription &prescription) {
    this->id = prescription.id;
    this->medication = prescription.medication;
    this->quantity = prescription.quantity;
    this->duration = prescription.duration;
    this->animalId = prescription.animalId;
    this->veterinarianId = prescription.veterinarianId;
}

void Prescription::setId(int id) {
    this->id = id;
}

void Prescription::setMedication(std::string medication) {
    this->medication = medication;
}

void Prescription::setQuantity(std::string quantity) {
    this->quantity = quantity;
}

void Prescription::setDuration(std::string duration) {
    this->duration = duration;
}

void Prescription::setAnimalId(int animalId) {
    this->animalId = animalId;
}


void Prescription::setVeterinarianId(int veterinarianId) {
    this->veterinarianId = veterinarianId;
}


const int& Prescription::getId() const {
    return this->id;
}

const std::string& Prescription::getMedication() const {
    return this->medication;
}

const std::string& Prescription::getQuantity() const {
    return this->quantity;
}

const std::string& Prescription::getDuration() const {
    return this->duration;
}

const int& Prescription::getAnimalId() const {
    return this->animalId;
}

const int& Prescription::getVeterinarianId() const {
    return this->veterinarianId;
}

bool Prescription::operator==(const Prescription& obj) const {
    return this->id == obj.id;
}