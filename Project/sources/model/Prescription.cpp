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
    setId(prescription.id);
    setMedication(prescription.medication);
    setQuantity(prescription.quantity);
    setDuration(prescription.duration);
    setAnimal(prescription.animal);
    setVeterinarian(prescription.veterinarian);
}

void Prescription::setId(int id) {
    if (id <= 0) {
        throw InvalidDataException("Id de Prescrição tem de ser positivo.");
    }
    this->id = id;
}

void Prescription::setMedication(const std::string& medication) {
    std::string trimmed_medication = trim(medication);
    if (trimmed_medication.empty()) {
        throw InvalidDataException("Medicamento da Prescrição não pode estar vazio.");
    }
    this->medication = trimmed_medication;
}

void Prescription::setQuantity(const std::string& quantity) {
    std::string trimmed_quantity = trim(quantity);
    if (trimmed_quantity.empty()) {
        throw InvalidDataException("Quantidade de medicamento da Prescrição não pode estar vazia.");
    }
    this->quantity = trimmed_quantity;
}

void Prescription::setDuration(const std::string& duration) {
    std::string trimmed_duration = trim(duration);
    if (trimmed_duration.empty()) {
        throw InvalidDataException("Duração da Prescrição não pode estar vazia.");
    }
    this->duration = trimmed_duration;
}

void Prescription::setAnimal(Animal* animal) {
    if (animal == nullptr) {
        throw InvalidDataException("Prescrição tem de estar associada a um Animal.");
    }
    this->animal = animal;
}

void Prescription::setVeterinarian(Veterinarian* veterinarian) {
    if (veterinarian == nullptr) {
        throw InvalidDataException("Prescrição tem de ser feita por um Veterinário.");
    }
    this->veterinarian = veterinarian;
}



int Prescription::getId() const {
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