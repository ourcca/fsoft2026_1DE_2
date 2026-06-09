#include "gtest/gtest.h"

#include "model/Service.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Date.h"
#include "model/Time.h"

TEST(ServiceConstructorTest, ValidService) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");
    Date date(20, 5, 2026);
    Time time(14, 30);

    Service service(1, "Consultation", 30.0, date, time, &animal, &veterinarian);

    EXPECT_EQ(service.getId(), 1);
    EXPECT_EQ(service.getType(), "Consultation");
    EXPECT_EQ(service.getCost(), 30.0f);
    EXPECT_TRUE(service.getDate() == date);
    EXPECT_TRUE(service.getTime() == time);
    EXPECT_EQ(service.getAnimal(), &animal);
    EXPECT_EQ(service.getVeterinarian(), &veterinarian);
}

TEST(ServiceOperatorEqualTest, EqualServices) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Service service1(1, "Consultation", 30.0, Date(20, 5, 2026), Time(14, 30), &animal, &veterinarian);
    Service service2(1, "Vaccine", 20.0, Date(21, 5, 2026), Time(15, 0), &animal, &veterinarian);

    EXPECT_TRUE(service1 == service2);
}

TEST(ServiceOperatorEqualTest, DifferentServices) {
    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Service service1(1, "Consultation", 30.0, Date(20, 5, 2026), Time(14, 30), &animal, &veterinarian);
    Service service2(2, "Vaccine", 20.0, Date(21, 5, 2026), Time(15, 0), &animal, &veterinarian);

    EXPECT_FALSE(service1 == service2);
}