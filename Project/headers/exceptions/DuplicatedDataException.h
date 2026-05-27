/*
DuplicatedDataException.h

Created on: 27/05/2026
*/
#ifndef HEADERS_EXCEPTIONS_DUPLICATEDDATAEXCEPTION_H_
#define HEADERS_EXCEPTIONS_DUPLICATEDDATAEXCEPTION_H_

#include <exception>
#include <string>

class DuplicatedDataException : public std::exception {
private:
    std::string data;

public:
    explicit DuplicatedDataException(const std::string& data);
    const char* what() const noexcept override;
};

#endif