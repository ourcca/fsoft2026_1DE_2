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
    repository.load();
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
                std::cout << "Opcao invalida.\n";
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
                    AnimalInDTO dto = animalView.getAnimal();
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

                        AnimalInDTO dto = animalView.getAnimal();
                        animalService.editAnimal(id, dto);

                        repository.save();
                        animalView.showAnimalUpdated();

                        break;
            }
                case 0:
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
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

                    VeterinarianInDTO dto = veterinarianView.getVeterinarian();
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

                        VeterinarianInDTO dto = veterinarianView.getVeterinarian();
                        veterinarianService.editVeterinarian(id, dto);

                        repository.save();
                        veterinarianView.showVeterinarianUpdated();

                        break;
                    }
                case 0:
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
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

                    ServiceInDTO dto = serviceView.getServiceStart();

                        serviceService.validateServiceStart(dto);

                    dto = serviceView.getServiceDetails(dto);

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

                        ServiceInDTO dto = serviceView.getServiceStart();
                        serviceService.validateServiceStart(dto);

                        dto = serviceView.getServiceDetails(dto);

                        serviceService.editService(id, dto);
                        repository.save();
                        serviceView.showServiceUpdated();

                        break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
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

                    PrescriptionInDTO dto = prescriptionView.getPrescription();
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
                case 0:
                    break;
                default:
                    std::cout << "Opcao invalida.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    } while (option != 0);
}
