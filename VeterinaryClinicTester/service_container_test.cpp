#include "gtest/gtest.h"

#include "model/ServiceContainer.h"
#include "model/Service.h"
#include "model/Animal.h"
#include "model/Veterinarian.h"
#include "model/Date.h"
#include "model/Time.h"

TEST(ServiceContainerAddTest, AddService) {
    ServiceContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Service service(1, "Consultation", 30.0, Date(20, 5, 2026), Time(14, 30), &animal, &veterinarian);

    container.add(service);

    EXPECT_EQ(container.getAll().size(), 1);
}

TEST(ServiceContainerGetTest, GetExistingService) {
    ServiceContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    Service service(1, "Consultation", 30.0, Date(20, 5, 2026), Time(14, 30), &animal, &veterinarian);
    container.add(service);

    Service* result = container.get(1);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getType(), "Consultation");
    EXPECT_EQ(result->getAnimal(), &animal);
    EXPECT_EQ(result->getVeterinarian(), &veterinarian);
}

TEST(ServiceContainerGetTest, GetNonExistingService) {
    ServiceContainer container;

    Service* result = container.get(99);

    EXPECT_EQ(result, nullptr);
}

TEST(ServiceContainerNextIdTest, EmptyContainer) {
    ServiceContainer container;

    int nextId = container.getNextId();

    EXPECT_EQ(nextId, 1);
}

TEST(ServiceContainerNextIdTest, NonEmptyContainer) {
    ServiceContainer container;

    Animal animal(1, "Rex", "Dog", "Labrador", 20.5, 4);
    Veterinarian veterinarian(1, "Joao Silva", 35, "Surgery");

    container.add(Service(1, "Consultation", 30.0, Date(20, 5, 2026), Time(14, 30), &animal, &veterinarian));
    container.add(Service(2, "Vaccine", 20.0, Date(21, 5, 2026), Time(15, 0), &animal, &veterinarian));

    int nextId = container.getNextId();

    EXPECT_EQ(nextId, 3);
}