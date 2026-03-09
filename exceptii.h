#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class ProdusException : public std::runtime_error {
public:
    explicit ProdusException(const std::string& msg) : std::runtime_error(msg) {}
};

class ProdusInexistentException : public ProdusException {
public:
    explicit ProdusInexistentException(const std::string& msg) : ProdusException(msg) {}
};

class CodDuplicatException : public ProdusException {
public:
    explicit CodDuplicatException(const std::string& msg) : ProdusException(msg) {}
};

#endif // EXCEPTII_H
