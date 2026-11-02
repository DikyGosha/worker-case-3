#include "../Worker.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    WORKER defaultWorker;
    defaultWorker.setSurnameAndInitials("Иванов И. И.");
    defaultWorker.setJobTitle("Программист");
    defaultWorker.setSalary(150000.0);
    defaultWorker.setHireYear(2020);

    assert(defaultWorker.getSurnameAndInitials() == "Иванов И. И.");
    assert(defaultWorker.getJobTitle() == "Программист");
    assert(defaultWorker.getSalary() == 150000.0);
    assert(defaultWorker.experienceYears(2026) == 6);

    WORKER parameterizedWorker("Петров П. П.", "Аналитик", 120000.0, 2024);
    assert(parameterizedWorker.experienceYears(2026) == 2);

    std::ostringstream output;
    parameterizedWorker.display(output);
    assert(output.str().find("Петров П. П.") != std::string::npos);
    assert(output.str().find("Аналитик") != std::string::npos);

    bool rejectedNegativeSalary = false;
    try {
        parameterizedWorker.setSalary(-1.0);
    } catch (const std::invalid_argument&) {
        rejectedNegativeSalary = true;
    }
    assert(rejectedNegativeSalary);

    bool rejectedOldYear = false;
    try {
        parameterizedWorker.setHireYear(1899);
    } catch (const std::invalid_argument&) {
        rejectedOldYear = true;
    }
    assert(rejectedOldYear);

    std::cout << "Все тесты WORKER пройдены.\n";
    return 0;
}
