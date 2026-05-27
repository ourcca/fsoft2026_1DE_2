/*
DataConsistencyException.h

Created on: 27/05/2026
*/
#ifndef HEADERS_EXCEPTIONS_DATACONSISTENCYEXCEPTION_H_
#define HEADERS_EXCEPTIONS_DATACONSISTENCYEXCEPTION_H_

#include <exception>
#include <string>

class DataConsistencyException : public std::exception {
private:
    std::string data;

public:
    explicit DataConsistencyException(const std::string& data);
    const char* what() const noexcept override;
};

#endif