/*
Veterinarian.h

Created on: 16/05/2026
*/
#ifndef HEADERS_MODEL_VETERINARIAN_H_
#define HEADERS_MODEL_VETERINARIAN_H_

#include <string>

class Veterinarian {
    private:
        int id{};
        std::string name{};
        int age{};
        std::string specialty{};
    public:
        Veterinarian(int id,const std::string& name,int age,const std::string& specialty);
        Veterinarian(const Veterinarian &veterinarian);
        ~Veterinarian() = default;
        void setId(int id);
        void setName(const std::string& name);
        void setSpecialty(const std::string& specialty);
        void setAge(int age);
        int getId() const;
        const std::string& getName() const;
        const std::string& getSpecialty() const;
        int getAge() const;

        bool operator == (const Veterinarian& obj) const;

};

#endif