/*
NoDataException.h

Created on: 27/05/2026
*/
#ifndef HEADERS_EXCEPTIONS_NODATAEXCEPTION_H_
#define HEADERS_EXCEPTIONS_NODATAEXCEPTION_H_

#include <exception>
#include <string>

class NoDataException : public std::exception {
private:
    std::string data;

public:
    explicit NoDataException(const std::string& data);
    const char* what() const noexcept override;
};

#endif