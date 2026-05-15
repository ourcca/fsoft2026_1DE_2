#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static int getNumber(const std::string& label);
    static std::string getString(const std::string& label);
};

#endif