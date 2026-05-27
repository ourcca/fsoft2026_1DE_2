/*
DuplicatedDataException.cpp

Created on: 27/05/2026
*/
#include "exceptions/DuplicatedDataException.h"

DuplicatedDataException::DuplicatedDataException(const std::string& data) {
    this->data = data;
}

const char* DuplicatedDataException::what() const noexcept {
    return data.c_str();
}