#include "Worker.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <utility>

WORKER::WORKER(std::string surnameAndInitials,
               std::string jobTitle,
               double salary,
               int hireYear)
    : surnameAndInitials_(std::move(surnameAndInitials)),
      jobTitle_(std::move(jobTitle)),
      salary_(salary),
      hireYear_(hireYear) {
    validateText(surnameAndInitials_, "Фамилия и инициалы");
    validateText(jobTitle_, "Должность");
    validateSalary(salary_);
    validateHireYear(hireYear_);
}

const std::string& WORKER::getSurnameAndInitials() const noexcept {
    return surnameAndInitials_;
}

const std::string& WORKER::getJobTitle() const noexcept {
    return jobTitle_;
}

double WORKER::getSalary() const noexcept {
    return salary_;
}

int WORKER::getHireYear() const noexcept {
    return hireYear_;
}

void WORKER::setSurnameAndInitials(std::string value) {
    validateText(value, "Фамилия и инициалы");
    surnameAndInitials_ = std::move(value);
}

void WORKER::setJobTitle(std::string value) {
    validateText(value, "Должность");
    jobTitle_ = std::move(value);
}

void WORKER::setSalary(double value) {
    validateSalary(value);
    salary_ = value;
}

void WORKER::setHireYear(int value) {
    validateHireYear(value);
    hireYear_ = value;
}

int WORKER::experienceYears(int currentYear) const {
    if (currentYear < hireYear_) {
        throw std::invalid_argument("Текущий год не может быть меньше года приема на работу.");
    }
    return currentYear - hireYear_;
}

void WORKER::display(std::ostream& output) const {
    output << "ФИО: " << surnameAndInitials_
           << ", должность: " << jobTitle_
           << ", зарплата: " << std::fixed << std::setprecision(2) << salary_
           << ", год приема: " << hireYear_;
}

void WORKER::validateText(const std::string& value, const char* fieldName) {
    if (value.empty()) {
        throw std::invalid_argument(std::string(fieldName) + " не может быть пустым.");
    }
}

void WORKER::validateSalary(double value) {
    if (value < 0.0) {
        throw std::invalid_argument("Зарплата не может быть отрицательной.");
    }
}

void WORKER::validateHireYear(int value) {
    if (value < 1900) {
        throw std::invalid_argument("Год приема должен быть не меньше 1900.");
    }
}
