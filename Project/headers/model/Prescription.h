/*
Prescription.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_PRESCRIPTION_H_
#define HEADERS_MODEL_PRESCRIPTION_H_

#include <string>

class Prescription {
    private:
        int id{};
        std::string medication{};
        std::string quantity{};
        std::string duration{};
        int animalId{};
        int veterinarianId{};

    public:
        Prescription(int id,std::string medication, std::string quantity, std::string duration, int animalId, int veterinarianId);
        Prescription(const Prescription& prescription);
        ~Prescription() = default;

        void setId(int id);
        void setMedication(std::string medication);
        void setQuantity(std::string quantity);
        void setDuration(std::string duration);
        void setAnimalId(int animalId);
        void setVeterinarianId(int veterinarianId);

        const int& getId() const;
        const std::string& getMedication() const;
        const std::string& getQuantity() const;
        const std::string& getDuration() const;
        const int& getAnimalId() const;
        const int& getVeterinarianId() const;

    bool operator==(const Prescription& obj) const;
};

#endif