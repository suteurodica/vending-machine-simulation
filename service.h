#ifndef SERVICE_H
#define SERVICE_H

#include "repo.h"
#include "produs.h"
#include "tonomat.h"
#include <vector>
#include <string>

class Service {
private:
    Repo* repo;     // pointer pentru a lucra cu RepoFile
    Tonomat tonomat; // tonomat pentru gestionarea monedelor

public:
    Service(Repo* r = nullptr);

    // Funcționalități produse
    void adauga_produs(int c, const std::string& n, double pret);
    std::vector<Produs> get_all() const;
    int get_size() const;
    bool deleteItem(int cod);
    bool updateItem(int cod, const std::string& n, double p);

    // Funcționalități tonomat
    void adauga_monede(int valoare, int nr);
    bool achizitioneaza_produs(int cod, double suma_client_lei);
    void afisare_monede() const;

};

#endif // SERVICE_H
