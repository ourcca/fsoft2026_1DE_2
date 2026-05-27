/*
DataConsistencyException.cpp

Created on: 27/05/2026
*/
#include "exceptions/DataConsistencyException.h"

DataConsistencyException::DataConsistencyException(const std::string& data) {
    this->data = data;
}

const char* DataConsistencyException::what() const noexcept {
    return data.c_str();
}