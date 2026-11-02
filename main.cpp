#include "Worker.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace {

int currentYear() {
    const std::time_t now = std::time(nullptr);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    return localTime.tm_year + 1900;
}

int readInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        int value{};

        if (std::cin >> value && value >= minValue && value <= maxValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Ошибка: введите целое число в диапазоне от "
                  << minValue << " до " << maxValue << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readSalary() {
    while (true) {
        std::cout << "Зарплата: ";
        double value{};

        if (std::cin >> value && value >= 0.0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cout << "Ошибка: зарплата должна быть неотрицательным числом.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readText(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin >> std::ws, value);
    return value;
}

} // namespace

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        const int year = currentYear();
        std::cout << "Программа учета работников. Текущий год: " << year << "\n\n";

        const int count = readInt("Количество работников: ", 0, 100000);
        std::vector<WORKER> workers;
        workers.reserve(static_cast<std::size_t>(count));

        for (int index = 0; index < count; ++index) {
            std::cout << "\nРаботник №" << index + 1 << "\n";
            const std::string surname = readText("Фамилия и инициалы: ");
            const std::string jobTitle = readText("Должность: ");
            const double salary = readSalary();
            const int hireYear = readInt("Год приема: ", 1900, year);

            // Параметризованный конструктор проверяет данные перед добавлением объекта.
            workers.emplace_back(surname, jobTitle, salary, hireYear);
        }

        std::cout << "\nВведенные работники:\n";
        for (const WORKER& worker : workers) {
            worker.display(std::cout);
            std::cout << "\n";
        }

        const int threshold = readInt(
            "\nПорог стажа в годах (вывести работников со стажем больше порога): ",
            0,
            year - 1900);

        bool found = false;
        std::cout << "\nРаботники со стажем больше " << threshold << " лет:\n";

        for (const WORKER& worker : workers) {
            if (worker.experienceYears(year) > threshold) {
                std::cout << "- " << worker.getSurnameAndInitials()
                          << " (" << worker.experienceYears(year) << " лет)\n";
                found = true;
            }
        }

        if (!found) {
            std::cout << "Работники с указанным стажем не найдены.\n";
        }

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Критическая ошибка: " << error.what() << "\n";
        return 1;
    }
}
