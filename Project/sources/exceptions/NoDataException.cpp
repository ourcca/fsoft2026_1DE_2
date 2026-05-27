/*
NoDataException.cpp

Created on: 27/05/2026
*/
#include "exceptions/NoDataException.h"

NoDataException::NoDataException(const std::string& data) {
    this->data = data;
}

const char* NoDataException::what() const noexcept {
    return data.c_str();
}