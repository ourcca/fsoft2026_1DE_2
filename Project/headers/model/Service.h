/*
Service.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_SERVICE_H_
#define HEADERS_MODEL_SERVICE_H_

#include <string>
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Date.h"
#include "model/Time.h"

class Service {
private:
    int id{};
    std::string type{};
    float cost{};
    Date date{};
    Time time{};
    Animal* animal{};
    Veterinarian* veterinarian{};

public:
    Service(int id,const std::string& type, float cost,const Date& date,const Time& time,
        Animal* animal, Veterinarian* veterinarian);

    Service(const Service& service);
    ~Service() = default;

    void setId(int id);
    void setType(const std::string& type);
    void setCost(float cost);
    void setDate(const Date& date);
    void setTime(const Time& time);
    void setAnimal(Animal* animal);
    void setVeterinarian(Veterinarian* veterinarian);

    int getId() const;
    const std::string& getType() const;
    float getCost() const;
    const Date& getDate() const;
    const Time& getTime() const;
    Animal* getAnimal() const;
    Veterinarian* getVeterinarian() const;

    bool operator==(const Service& obj) const;
};

#endif