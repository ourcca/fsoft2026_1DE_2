/*
Service.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_SERVICE_H_
#define HEADERS_MODEL_SERVICE_H_

#include <string>

class Service {
private:
    int id{};
    std::string type{};
    float cost{};
    std::string date{};
    std::string time{};
    int animalId{};
    int veterinarianId{};

public:
    Service(int id, std::string type, float cost, std::string date, std::string time,
            int animalId, int veterinarianId);

    Service(const Service& service);
    ~Service() = default;

    void setId(int id);
    void setType(std::string type);
    void setCost(float cost);
    void setDate(std::string date);
    void setTime(std::string time);
    void setAnimalId(int animalId);
    void setVeterinarianId(int veterinarianId);

    const int& getId() const;
    const std::string& getType() const;
    const float& getCost() const;
    const std::string& getDate() const;
    const std::string& getTime() const;
    const int& getAnimalId() const;
    const int& getVeterinarianId() const;

    bool operator==(const Service& obj) const;
};

#endif