/*
    Animal.h

    Created on: 15/05/2026
 */
#ifndef HEADERS_MODEL_ANIMAL_H_
#define HEADERS_MODEL_ANIMAL_H_
#include <string>

class Animal {
    private:
        int id{};
        std::string name{};
        std::string species{};
        std::string breed{};
        float weight{};
        int age;
    public:
        Animal(int id, const std::string &name, const std::string &species, const std::string &breed, float weight, int age);
        Animal(const Animal &animal);
        ~Animal() = default;
        void setId(int id);
        void setName(std::string name);
        void setSpecies(std::string species);
        void setBreed(std::string breed);
        void setWeight(float weight);
        void setAge(int age);
        const int& getId() const;
        const std::string& getName() const;
        const std::string& getSpecies() const;
        const std::string& getBreed() const;
        const float& getWeight() const;
        int getAge() const;

        bool operator == (const Animal& obj) const;
};

#endif /* HEADERS_MODEL_ANIMAL_H_ */