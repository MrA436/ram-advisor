// Exceptions.h
// TCS307 Unit 5: Exception handling (throw/catch, rethrow), custom exception classes
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class InfeasibleUpgradeException : public std::runtime_error {
public:
    explicit InfeasibleUpgradeException(const std::string& reason)
        : std::runtime_error(reason) {}
};

class UnknownMotherboardException : public std::runtime_error {
public:
    explicit UnknownMotherboardException(const std::string& reason)
        : std::runtime_error(reason) {}
};

#endif
