/*
InvalidDataException.h

Created on: 27/05/2026
*/
#ifndef HEADERS_EXCEPTIONS_INVALIDDATAEXCEPTION_H_
#define HEADERS_EXCEPTIONS_INVALIDDATAEXCEPTION_H_

#include <exception>
#include <string>

class InvalidDataException : public std::exception {
private:
    std::string data;

public:
    explicit InvalidDataException(const std::string& data);
    const char* what() const noexcept override;
};

#endif