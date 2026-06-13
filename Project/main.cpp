#include "controllers/Controller.h"

#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::setlocale(LC_ALL, ".UTF-8");

    Controller controller;
    controller.run();

    return 0;
}