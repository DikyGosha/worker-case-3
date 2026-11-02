#pragma once

#include <string>
#include <iosfwd>

class WORKER {
public:
    WORKER() = default;

    WORKER(std::string surnameAndInitials,
           std::string jobTitle,
           double salary,
           int hireYear);

    ~WORKER() = default;

    const std::string& getSurnameAndInitials() const noexcept;
    const std::string& getJobTitle() const noexcept;
    double getSalary() const noexcept;
    int getHireYear() const noexcept;

    void setSurnameAndInitials(std::string value);
    void setJobTitle(std::string value);
    void setSalary(double value);
    void setHireYear(int value);

    int experienceYears(int currentYear) const;
    void display(std::ostream& output) const;

private:
    static void validateText(const std::string& value, const char* fieldName);
    static void validateSalary(double value);
    static void validateHireYear(int value);

    std::string surnameAndInitials_;
    std::string jobTitle_;
    double salary_ = 0.0;
    int hireYear_ = 0;
};
