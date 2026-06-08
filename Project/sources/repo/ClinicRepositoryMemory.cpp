#include "repo/ClinicRepositoryMemory.h"

ClinicRepositoryMemory::ClinicRepositoryMemory() = default;

Clinic& ClinicRepositoryMemory::getClinic() {
    return clinic;
}

void ClinicRepositoryMemory::save() {
    // Memory repository does not persist data.
}