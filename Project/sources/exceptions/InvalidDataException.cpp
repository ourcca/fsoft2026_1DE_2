/*
InvalidDataException.cpp

Created on: 27/05/2026
*/
#include "exceptions/InvalidDataException.h"

InvalidDataException::InvalidDataException(const std::string& data) {
    this->data = data;
}

const char* InvalidDataException::what() const noexcept {
    return data.c_str();
}