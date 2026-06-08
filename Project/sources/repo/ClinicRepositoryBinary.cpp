#include "repo/ClinicRepositoryBinary.h"

ClinicRepositoryBinary::ClinicRepositoryBinary(const std::string& fileName) {
    this->fileName = fileName;
}

Clinic& ClinicRepositoryBinary::getClinic() {
    return clinic;
}

void ClinicRepositoryBinary::save() {
    // TODO: implement binary persistence
}

void ClinicRepositoryBinary::load() {
    // TODO: implement binary loading
}