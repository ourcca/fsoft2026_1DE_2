#include "views/Utils.h"

#include <iostream>
#include <limits>

int Utils::getNumber(const std::string& label) {
    int value;

    while (true) {
        std::cout << label;
        std::cin >> value;

        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor inválido. Tente novamente.\n";
    }
}

std::string Utils::getString(const std::string& label) {
    std::string value;

    std::cout << label;
    std::getline(std::cin, value);

    return value;
}