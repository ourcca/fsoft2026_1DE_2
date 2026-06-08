#ifndef HEADERS_REPO_CLINICREPOSITORYBINARY_H_
#define HEADERS_REPO_CLINICREPOSITORYBINARY_H_

#include <string>

#include "repo/IClinicRepository.h"

class ClinicRepositoryBinary : public IClinicRepository {
private:
    Clinic clinic;
    std::string fileName;

public:
    explicit ClinicRepositoryBinary(const std::string& fileName);

    Clinic& getClinic() override;
    void save() override;

    void load();
};

#endif