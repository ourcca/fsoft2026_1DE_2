/*
Service.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_SERVICE_H_
#define HEADERS_MODEL_SERVICE_H_

#include <string>
#include "model/Animal.h"
#include "model/Veterinarian.h"

class Service {
private:
    int id{};
    std::string type{};
    float cost{};
    std::string date{};
    std::string time{};
    Animal* animal{};
    Veterinarian* veterinarian{};

public:
    Service(int id, std::string type, float cost, std::string date, std::string time,
        Animal* animal, Veterinarian* veterinarian);

    Service(const Service& service);
    ~Service() = default;

    void setId(int id);
    void setType(std::string type);
    void setCost(float cost);
    void setDate(std::string date);
    void setTime(std::string time);
    void setAnimal(Animal* animal);
    void setVeterinarian(Veterinarian* veterinarian);

    const int& getId() const;
    const std::string& getType() const;
    const float& getCost() const;
    const std::string& getDate() const;
    const std::string& getTime() const;
    Animal* getAnimal() const;
    Veterinarian* getVeterinarian() const;

    bool operator==(const Service& obj) const;
};

#endif