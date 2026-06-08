#ifndef HEADERS_REPO_CLINICREPOSITORYMEMORY_H_
#define HEADERS_REPO_CLINICREPOSITORYMEMORY_H_

#include "repo/IClinicRepository.h"

class ClinicRepositoryMemory : public IClinicRepository {
private:
    Clinic clinic;

public:
    ClinicRepositoryMemory();

    Clinic& getClinic() override;
    void save() override;
};

#endif