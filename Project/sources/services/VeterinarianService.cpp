/*
VeterinarianService.cpp

Created on: 16/05/2026
*/
#include "services/VeterinarianService.h"

#include "model/Veterinarian.h"
#include "mappers/VeterinarianMapper.h"
#include "exceptions/NoDataException.h"
#include "exceptions/InvalidDataException.h"
#include "exceptions/DataConsistencyException.h"
#include "model/Prescription.h"
#include "model/Service.h"
#include "services/ServiceCatalog.h"

VeterinarianService::VeterinarianService(Clinic& clinic) : clinic(clinic) {}

void VeterinarianService::addVeterinarian(const VeterinarianInDTO& dto) {
    validateName(dto.name);
    validateAge(dto.age);
    validateSpecialty(dto.specialty);

    int id = clinic.getVeterinarianContainer().getNextId();
    Veterinarian veterinarian(id, dto.name, dto.age, dto.specialty);
    clinic.getVeterinarianContainer().add(veterinarian);
}

std::vector<VeterinarianOutDTO> VeterinarianService::getAllVeterinarians() {
    auto& veterinarians = clinic.getVeterinarianContainer().getAll();
    return VeterinarianMapper::toDTOList(veterinarians);
}

VeterinarianOutDTO VeterinarianService::getVeterinarianById(int id) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(id);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    return VeterinarianMapper::toDTO(*veterinarian);
}

void VeterinarianService::editVeterinarian(int id, const VeterinarianInDTO& dto) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    validateName(dto.name);
    validateAge(dto.age);
    validateSpecialty(dto.specialty);

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(id);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    const std::string newSpecialtyKey = ServiceCatalog::normalizeKey(dto.specialty);

    for (const Service& service : clinic.getServiceContainer().getAll()) {
        if (service.getVeterinarian() == veterinarian) {
            const std::string requiredSpecialty =
                ServiceCatalog::requiredSpecialtyForService(service.getType());

            const std::string requiredSpecialtyKey =
                ServiceCatalog::normalizeKey(requiredSpecialty);

            if (requiredSpecialtyKey.empty()) {
                if (!newSpecialtyKey.empty()) {
                    throw DataConsistencyException("Não é possível alterar a especialidade do Veterinário porque ele tem serviços sem especialidade associados.");
                }
            } else if (newSpecialtyKey != requiredSpecialtyKey) {
                throw DataConsistencyException("Não é possível alterar a especialidade do Veterinário porque ele tem serviços que exigem outra especialidade.");
            }
        }
    }

    clinic.getVeterinarianContainer().edit(
        id,
        dto.name,
        dto.age,
        dto.specialty
    );
}

int VeterinarianService::countPrescriptionsByVeterinarianId(int veterinarianId) const {
    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    int count = 0;

    for (const Prescription& prescription : clinic.getPrescriptionContainer().getAll()) {
        if (prescription.getVeterinarian() == veterinarian) {
            count++;
        }
    }

    return count;

}

int VeterinarianService::countServicesByVeterinarianId(int veterinarianId) const {
    if (veterinarianId <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(veterinarianId);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    int count = 0;

    for (const Service& service : clinic.getServiceContainer().getAll()) {
        if (service.getVeterinarian() == veterinarian) {
            count++;
        }
    }

    return count;
}

bool VeterinarianService::hasAssociatedRecords(int veterinarianId) const {
    return countPrescriptionsByVeterinarianId(veterinarianId) > 0 || countServicesByVeterinarianId(veterinarianId) > 0;
}

void VeterinarianService::removeVeterinarian(int id, bool removeAssociatedRecords) {
    if (id <= 0) {
        throw InvalidDataException("ID de Veterinário inválido.");
    }

    Veterinarian* veterinarian = clinic.getVeterinarianContainer().get(id);

    if (veterinarian == nullptr) {
        throw NoDataException("Veterinário não encontrado.");
    }

    std::vector<int> prescriptionIds;
    std::vector<int> serviceIds;

    for (const Prescription& prescription : clinic.getPrescriptionContainer().getAll()) {
        if (prescription.getVeterinarian() == veterinarian) {
            prescriptionIds.push_back(prescription.getId());
        }
    }

    for (const Service& service : clinic.getServiceContainer().getAll()) {
        if (service.getVeterinarian() == veterinarian) {
            serviceIds.push_back(service.getId());
        }
    }

    if ((!prescriptionIds.empty() || !serviceIds.empty()) && !removeAssociatedRecords) {
        throw DataConsistencyException("Veterinário tem prescrições ou serviços associados. Remoção cancelada.");
    }

    for (int prescriptionId : prescriptionIds) {
        clinic.getPrescriptionContainer().remove(prescriptionId);
    }

    for (int serviceId : serviceIds) {
        clinic.getServiceContainer().remove(serviceId);
    }

    clinic.getVeterinarianContainer().remove(id);
}


void VeterinarianService::validateName(const std::string& name) {
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    veterinarian.setName(name);
}

void VeterinarianService::validateAge(int age) {
    Veterinarian veterinarian(1, "Nome", 18, "Especialidade");
    veterinarian.setAge(age);
}

void VeterinarianService::validateSpecialty(const std::string& specialty) {
    Veterinarian veterinarian(1, "Nome", 18, "Cirurgia");
    veterinarian.setSpecialty(specialty);

    if (!ServiceCatalog::isValidSpecialty(specialty)) {
        throw InvalidDataException("Especialidade de Veterinário não existe.");
    }
}
