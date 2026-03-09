#ifndef TONOMAT_H
#define TONOMAT_H

#include "Collection.h"

class Tonomat {
private:
    Collection<int> monede;

public:
    Tonomat();

    void adaugaMonede(int valoare, int nr);
    bool poateDaRest(int suma) const;
    Collection<int> calculeazaRest(int suma) const;
    void retrageSuma(int suma);
    void afisareMonede() const;
};

#endif // TONOMAT_H
