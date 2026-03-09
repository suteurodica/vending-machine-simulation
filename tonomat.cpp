#include "Tonomat.h"
#include <iostream>
using namespace std;

Tonomat::Tonomat() {}

void Tonomat::adaugaMonede(int valoare, int nr) {
    for (int i = 0; i < nr; i++) {
        monede.add(valoare);
    }
}

bool Tonomat::poateDaRest(int suma) const { //suma e in bani  ,de ex poate da rest de 250 de bani?
    int sumaRamasa = suma;
    int valori[] = {50, 10};  // monedele disponibile (1 leu, 50 bani, 10 bani)
    Collection<int> copie;
    copie= monede;

    for (int i = 0; i < 2 && sumaRamasa > 0; i++) {
        while (sumaRamasa >= valori[i] && copie.nrOccurrences(valori[i]) > 0) {
            copie.remove(valori[i]);
            sumaRamasa -= valori[i];
        }
    }

    return sumaRamasa == 0;
}

Collection<int> Tonomat::calculeazaRest(int suma) const {
    int sumaRamasa = suma;
    int valori[] = {50, 10};
    Collection<int> rest;
    Collection<int> copie = monede;

    for (int i = 0; i < 2 && sumaRamasa > 0; i++) {
        while (sumaRamasa >= valori[i] && copie.nrOccurrences(valori[i]) > 0) {
            rest.add(valori[i]);
            copie.remove(valori[i]);
            sumaRamasa -= valori[i];
        }
    }

    if (sumaRamasa == 0)
        return rest;
    else
        return Collection<int>(); // colecție goală dacă nu se poate da rest
}

void Tonomat::retrageSuma(int suma) {
    Collection<int> rest = calculeazaRest(suma);

    if (rest.totalElements() == 0) {
        cout << "Nu se poate oferi restul.\n";
        return;
    }

    for (int i = 0; i < rest.size(); i++) {
        int val = rest.getAt(i);
        for (int j = 0; j < rest.nrOccurrences(val); j++) {
            monede.remove(val);
        }
    }

    cout << "Rest oferit: ";
    rest.afisare();
}

void Tonomat::afisareMonede() const {
    cout << "Monede disponibile:\n";
    monede.afisare();
}
