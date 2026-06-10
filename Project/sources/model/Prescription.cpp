/*
Prescription.cpp

Created on: 16/05/2026
*/
#include "model/Prescription.h"
#include "exceptions/InvalidDataException.h"

Prescription::Prescription(int id, std::string medication, std::string quantity, std::string duration, Animal* animal, Veterinarian* veterinarian) {
    this->id = id;
    this->medication = medication;
    this->quantity = quantity;
    this->duration = duration;
    this->animal = animal;
    this->veterinarian = veterinarian;
}

Prescription::Prescription(const Prescription &prescription) {
    this->id = prescription.id;
    this->medication = prescription.medication;
    this->quantity = prescription.quantity;
    this->duration = prescription.duration;
    this->animal = prescription.animal;
    this->veterinarian = prescription.veterinarian;
}

void Prescription::setId(int id) {
    this->id = id;
}

void Prescription::setMedication(std::string medication) {
    if (medication.empty()) {
        throw InvalidDataException("Medicamento da Prescrição não pode estar vazio.");
    }
    this->medication = medication;
}

void Prescription::setQuantity(std::string quantity) {
    if (quantity.empty()) {
        throw InvalidDataException("Quantidade de medicamento da Prescrição não pode estar vazio.");
    }
    this->quantity = quantity;
}

void Prescription::setDuration(std::string duration) {
    if (duration.empty()) {
        throw InvalidDataException("Duração da Prescrição não pode estar vazio.");
    }
    this->duration = duration;
}

void Prescription::setAnimal(Animal* animal) {
    this->animal = animal;
}

void Prescription::setVeterinarian(Veterinarian* veterinarian) {
    this->veterinarian = veterinarian;
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

Animal* Prescription::getAnimal() const {
    return this->animal;
}

Veterinarian* Prescription::getVeterinarian() const {
    return this->veterinarian;
}

bool Prescription::operator==(const Prescription& obj) const {
    return this->id == obj.id;
}