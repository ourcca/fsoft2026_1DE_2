/*
Prescription.cpp

Created on: 16/05/2026
*/
#include "model/Prescription.h"
#include "exceptions/InvalidDataException.h"

namespace {
    std::string trim(const std::string& value) {
        const std::string whitespace = " \t\n\r\f\v";
        const size_t start = value.find_first_not_of(whitespace);

        if (start == std::string::npos) {
            return "";
        }

        const size_t end = value.find_last_not_of(whitespace);
        return value.substr(start, end - start + 1);
    }
}

Prescription::Prescription(int id,const std::string& medication,const std::string& quantity,const std::string& duration, Animal* animal, Veterinarian* veterinarian) {
    setId(id);
    setMedication(medication);
    setQuantity(quantity);
    setDuration(duration);
    setAnimal(animal);
    setVeterinarian(veterinarian);
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

void Prescription::setMedication(const std::string& medication) {
    if (medication.empty()) {
        throw InvalidDataException("Medicamento da Prescrição não pode estar vazio.");
    }
    this->medication = medication;
}

void Prescription::setQuantity(const std::string& quantity) {
    if (quantity.empty()) {
        throw InvalidDataException("Quantidade de medicamento da Prescrição não pode estar vazio.");
    }
    this->quantity = quantity;
}

void Prescription::setDuration(const std::string& duration) {
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