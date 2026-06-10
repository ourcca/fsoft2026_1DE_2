/*
Prescription.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_PRESCRIPTION_H_
#define HEADERS_MODEL_PRESCRIPTION_H_

#include <string>

#include "model/Animal.h"
#include "model/Veterinarian.h"

class Prescription {
    private:
        int id{};
        std::string medication{};
        std::string quantity{};
        std::string duration{};
        Animal* animal{};
        Veterinarian* veterinarian{};

    public:
        Prescription(int id,const std::string& medication,const std::string& quantity,const std::string& duration, Animal* animal, Veterinarian* veterinarian);
        Prescription(const Prescription& prescription);
        ~Prescription() = default;

        void setId(int id);
        void setMedication(const std::string& medication);
        void setQuantity(const std::string& quantity);
        void setDuration(const std::string& duration);
        void setAnimal(Animal* animal);
        void setVeterinarian(Veterinarian* veterinarian);

        const int& getId() const;
        const std::string& getMedication() const;
        const std::string& getQuantity() const;
        const std::string& getDuration() const;
        Animal* getAnimal() const;
        Veterinarian* getVeterinarian() const;

    bool operator==(const Prescription& obj) const;
};

#endif