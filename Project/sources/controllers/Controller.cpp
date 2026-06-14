/*
Controller.cpp

Created on: 15/05/2026
*/
#include "controllers/Controller.h"
#include "dto/AnimalOutDTO.h"
#include "dto/VeterinarianInDTO.h"
#include "dto/VeterinarianOutDTO.h"
#include "dto/PrescriptionInDTO.h"
#include "dto/PrescriptionOutDTO.h"


#include <iostream>
#include <exception>
#include <vector>

Controller::Controller()
    : repository("clinic.dat"),
      animalService(repository.getClinic()),
      veterinarianService(repository.getClinic()),
      serviceService(repository.getClinic()),
      prescriptionService(repository.getClinic()) {
    try {
        repository.load();
    } catch (const std::exception& e) {
        std::cout << "Erro ao carregar clinic.dat: " << e.what() << "\n";
        std::cout << "A iniciar com dados vazios.\n";
    }
}

void Controller::run() {
    int option;

    do {
        option = view.menu();

        switch (option) {
            case 1:
                runAnimals();
                break;
            case 2:
                runVeterinarians();
                break;
            case 3:
                runServices();
                break;
            case 4:
                runPrescriptions();
                break;
            case 0:
                view.showExitMessage();
                break;
            default:
                std::cout << "Opção inválida.\n";
                break;
        }

    } while (option != 0);
}

void Controller::runAnimals() {
    int option;

    do {
        option = AnimalView::menu();

        try {
            switch (option) {
                case 1: {
                    AnimalInDTO dto{};

                    dto.name = animalView.getName();
                    animalService.validateName(dto.name);

                    dto.species = animalView.getSpecies();
                    animalService.validateSpecies(dto.species);

                    dto.breed = animalView.getBreed();

                    dto.weight = animalView.getWeight();
                    animalService.validateWeight(dto.weight);

                    dto.age = animalView.getAge();
                    animalService.validateAge(dto.age);

                    animalService.addAnimal(dto);
                    repository.save();
                    animalView.showAnimalCreated();
                    break;
                }
                case 2: {
                    std::vector<AnimalOutDTO> animals = animalService.getAllAnimals();
                    animalView.printAnimals(animals);
                    break;
                }
                case 3: {
                    int id = animalView.getAnimalId();
                    AnimalOutDTO animal = animalService.getAnimalById(id);
                    animalView.printAnimal(animal);
                    break;
                }
            case 4:{
                    int id = animalView.getAnimalId();

                    AnimalOutDTO animal = animalService.getAnimalById(id);
                    animalView.printAnimal(animal);

                    AnimalInDTO dto{};

                    dto.name = animalView.getName();
                    animalService.validateName(dto.name);

                    dto.species = animalView.getSpecies();
                    animalService.validateSpecies(dto.species);

                    dto.breed = animalView.getBreed();

                    dto.weight = animalView.getWeight();
                    animalService.validateWeight(dto.weight);

                    dto.age = animalView.getAge();
                    animalService.validateAge(dto.age);

                    animalService.editAnimal(id, dto);

                    repository.save();
                    animalView.showAnimalUpdated();

                    break;
            }
            case 5: {
                    int id = animalView.getAnimalId();

                    AnimalOutDTO animal = animalService.getAnimalById(id);
                    animalView.printAnimal(animal);

                    int prescriptionCount = animalService.countPrescriptionsByAnimalId(id);
                    int serviceCount = animalService.countServicesByAnimalId(id);

                    bool removeAssociatedRecords = false;

                    if (prescriptionCount > 0 || serviceCount > 0) {
                        removeAssociatedRecords = animalView.confirmRemoveAssociatedData(prescriptionCount,serviceCount);

                        if (!removeAssociatedRecords) {
                            animalView.showAnimalRemoveCancelled();
                            break;
                        }
                    }

                    animalService.removeAnimal(id, removeAssociatedRecords);
                    repository.save();
                    animalView.showAnimalRemoved();

                    break;
                }

                case 0:
                    break;
                default:
                    std::cout << "Opção inválida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }

    } while (option != 0);
}

void Controller::runVeterinarians() {
    int option;

    do {
        option = veterinarianView.menu();
        try {
            switch (option) {
                case 1: {

                    VeterinarianInDTO dto{};

                    dto.name = veterinarianView.getName();
                    veterinarianService.validateName(dto.name);

                    dto.age = veterinarianView.getAge();
                    veterinarianService.validateAge(dto.age);

                    dto.specialty = veterinarianView.getSpecialty();
                    veterinarianService.validateSpecialty(dto.specialty);

                    veterinarianService.addVeterinarian(dto);
                    repository.save();
                    veterinarianView.showVeterinarianCreated();

                    break;
                }
                case 2: {
                    std::vector<VeterinarianOutDTO> veterinarians = veterinarianService.getAllVeterinarians();
                    veterinarianView.printVeterinarians(veterinarians);
                    break;
                }
                case 3: {
                    int veterinarianId = veterinarianView.getVeterinarianId();

                    std::vector<ServiceOutDTO> services =
                        serviceService.getServicesByVeterinarianId(veterinarianId);

                    serviceView.printServices(services);

                    break;
                }
                case 4: {
                    int id = veterinarianView.getVeterinarianId();

                    VeterinarianOutDTO veterinarian = veterinarianService.getVeterinarianById(id);
                    veterinarianView.printVeterinarian(veterinarian);

                    VeterinarianInDTO dto{};

                    dto.name = veterinarianView.getName();
                    veterinarianService.validateName(dto.name);

                    dto.age = veterinarianView.getAge();
                    veterinarianService.validateAge(dto.age);

                    dto.specialty = veterinarianView.getSpecialty();
                    veterinarianService.validateSpecialty(dto.specialty);

                    veterinarianService.editVeterinarian(id, dto);

                    repository.save();
                    veterinarianView.showVeterinarianUpdated();

                    break;
                    }
                case 5: {
                    int id = veterinarianView.getVeterinarianId();

                    VeterinarianOutDTO veterinarian = veterinarianService.getVeterinarianById(id);
                    veterinarianView.printVeterinarian(veterinarian);

                    int prescriptionCount = veterinarianService.countPrescriptionsByVeterinarianId(id);
                    int serviceCount = veterinarianService.countServicesByVeterinarianId(id);

                    bool removeAssociatedRecords = false;

                    if (prescriptionCount > 0 || serviceCount > 0) {
                        removeAssociatedRecords = veterinarianView.confirmRemoveAssociatedData(
                            prescriptionCount,
                            serviceCount
                        );

                        if (!removeAssociatedRecords) {
                            veterinarianView.showVeterinarianRemoveCancelled();
                            break;
                        }
                    }

                    veterinarianService.removeVeterinarian(id, removeAssociatedRecords);
                    repository.save();
                    veterinarianView.showVeterinarianRemoved();

                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Opção inválida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    } while (option != 0);
}
void Controller::runServices() {
    int option;

    do {
        option = serviceView.menu();
        try {
            switch (option) {
                case 1: {

                    ServiceInDTO dto{};

                    dto.animalId = serviceView.getAnimalId();
                    serviceService.validateAnimalExists(dto.animalId);

                    dto.veterinarianId = serviceView.getVeterinarianId();
                    serviceService.validateVeterinarianExists(dto.veterinarianId);

                    dto.type = serviceView.getType();
                    serviceService.validateVeterinarianCanDoService(dto.veterinarianId, dto.type);

                    dto.cost = serviceView.getCost();
                    serviceService.validateCost(dto.cost);

                    dto.date = serviceView.getDate();
                    serviceService.validateDateText(dto.date);

                    dto.time = serviceView.getTime();
                    serviceService.validateTimeText(dto.time);

                    serviceService.addService(dto);
                    repository.save();
                    serviceView.showServiceCreated();

                    break;
                }
                case 2: {
                    std::vector<ServiceOutDTO> services = serviceService.getAllServices();
                    serviceView.printServices(services);
                    break;
                }
            case 3: {
                    int id = serviceView.getServiceId();

                    ServiceOutDTO service = serviceService.getServiceById(id);
                    serviceView.printService(service);

                    ServiceInDTO dto{};

                    dto.animalId = serviceView.getAnimalId();
                    serviceService.validateAnimalExists(dto.animalId);

                    dto.veterinarianId = serviceView.getVeterinarianId();
                    serviceService.validateVeterinarianExists(dto.veterinarianId);


                    dto.type = serviceView.getType();
                    serviceService.validateVeterinarianCanDoService(dto.veterinarianId, dto.type);

                    dto.cost = serviceView.getCost();
                    serviceService.validateCost(dto.cost);

                    dto.date = serviceView.getDate();
                    serviceService.validateDateText(dto.date);

                    dto.time = serviceView.getTime();
                    serviceService.validateTimeText(dto.time);

                    serviceService.editService(id, dto);

                    repository.save();
                    serviceView.showServiceUpdated();

                    break;
                }
            case 4: {
                    int id = serviceView.getServiceId();
                    ServiceOutDTO service = serviceService.getServiceById(id);
                    serviceView.printService(service);

                    serviceService.removeService(id);
                    repository.save();
                    serviceView.showServiceRemoved();

                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Opção inválida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    } while (option != 0);
}

void Controller::runPrescriptions() {
    int option;

    do {
        option = prescriptionView.menu();
        try {
            switch (option) {
                case 1: {

                    PrescriptionInDTO dto{};

                    dto.animalId = prescriptionView.getAnimalId();
                    prescriptionService.validateAnimalExists(dto.animalId);

                    dto.veterinarianId = prescriptionView.getVeterinarianId();
                    prescriptionService.validateVeterinarianExists(dto.veterinarianId);

                    dto.medication = prescriptionView.getMedication();
                    prescriptionService.validateMedication(dto.medication);

                    dto.quantity = prescriptionView.getQuantity();
                    prescriptionService.validateQuantity(dto.quantity);

                    dto.duration = prescriptionView.getDuration();
                    prescriptionService.validateDuration(dto.duration);

                    prescriptionService.addPrescription(dto);
                    repository.save();
                    prescriptionView.showPrescriptionCreated();

                    break;
                }
                case 2: {
                    std::vector<PrescriptionOutDTO> prescriptions =
                        prescriptionService.getAllPrescriptions();

                    prescriptionView.printPrescriptions(prescriptions);
                    break;
                }
                case 3: {
                    int animalId = prescriptionView.getAnimalId();

                    std::vector<PrescriptionOutDTO> prescriptions =
                        prescriptionService.getPrescriptionsByAnimalId(animalId);

                    prescriptionView.printPrescriptions(prescriptions);
                    break;
                }
            case 4: {
                        int id = prescriptionView.getPrescriptionId();

                        PrescriptionOutDTO prescription = prescriptionService.getPrescriptionById(id);
                        prescriptionView.printPrescription(prescription);

                        PrescriptionInDTO dto{};

                        dto.animalId = prescriptionView.getAnimalId();
                        prescriptionService.validateAnimalExists(dto.animalId);

                        dto.veterinarianId = prescriptionView.getVeterinarianId();
                        prescriptionService.validateVeterinarianExists(dto.veterinarianId);

                        dto.medication = prescriptionView.getMedication();
                        prescriptionService.validateMedication(dto.medication);

                        dto.quantity = prescriptionView.getQuantity();
                        prescriptionService.validateQuantity(dto.quantity);

                        dto.duration = prescriptionView.getDuration();
                        prescriptionService.validateDuration(dto.duration);

                        prescriptionService.editPrescription(id, dto);
                        repository.save();
                        prescriptionView.showPrescriptionUpdated();

                        break;
                    }
            case 5: {
                        int id = prescriptionView.getPrescriptionId();

                        prescriptionService.removePrescription(id);
                        repository.save();
                        prescriptionView.showPrescriptionRemoved();

                        break;
                    }
                case 0:
                    break;
                default:
                    std::cout << "Opção inválida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    } while (option != 0);
}
