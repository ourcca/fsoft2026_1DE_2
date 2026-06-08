#ifndef HEADERS_REPO_ICLINICREPOSITORY_H_
#define HEADERS_REPO_ICLINICREPOSITORY_H_

#include "model/Clinic.h"

class IClinicRepository {
public:
    virtual ~IClinicRepository() = default;

    virtual Clinic& getClinic() = 0;
    virtual void save() = 0;
};

#endif