#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include "exceptii.h"

class ProdusValidator {
public:
    static void valideaza(int cod, const std::string& nume, double pret) {
        if (nume.size() < 2)
            throw ProdusException("Numele produsului este prea scurt!");

        if (pret <= 0)
            throw ProdusException("Pretul trebuie sa fie pozitiv!");

        if (cod <= 0)
            throw ProdusException("Codul trebuie sa fie un numar pozitiv!");
    }
};

#endif // VALIDATOR_H
