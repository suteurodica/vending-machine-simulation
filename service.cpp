//
// Created by www on 5/3/2025.
//

#include "service.h"
#include "tonomat.h"
#include "exceptii.h"
#include "validator.h"



Service::Service(Repo* r) {
    if (r)
        repo = r;
    else
        repo = new Repo();
}

void Service::adauga_produs(int c, const string &n, double pret) {
    ProdusValidator::valideaza(c, n, pret);

    // Verificare cod duplicat
    vector<Produs> toate = repo->getAll();
    for (const auto& p : toate) {
        if (p.get_cod() == c)
            throw CodDuplicatException("Exista deja un produs cu acest cod!");
    }

    Produs produs(c, n, pret);
    repo->addItem(produs);
}


vector<Produs> Service::get_all() const{
    return repo->getAll();

}
bool Service::deleteItem(int cod) {
    if (!repo->deleteItem(cod)) {
        throw ProdusInexistentException("Produsul nu exista si nu poate fi sters!");
    }
    return true;
}

bool Service::updateItem(int cod, const std::string& n, double pret) {
    ProdusValidator::valideaza(cod, n, pret);
    Produs produs(cod, n, pret);
    if (!repo->updateItem(cod, produs)) {
        throw ProdusInexistentException("Produsul nu exista si nu poate fi actualizat!");
    }
    return true;
}


void Service::adauga_monede(int valoare, int nr) {
    tonomat.adaugaMonede(valoare, nr);
}

void Service::afisare_monede() const {
    tonomat.afisareMonede();
}

bool Service::achizitioneaza_produs(int cod, double suma_client_lei) {
    int suma_bani = static_cast<int>(suma_client_lei * 100 + 0.5);

    std::vector<Produs> produse = repo->getAll();
    for (const auto& p : produse) {
        if (p.get_cod() == cod) {
            int pret = p.get_pret();
            if (suma_bani < pret) {
                std::cout << "Suma introdusa este prea mica.\n";
                return false;
            }

            int rest = suma_bani - pret;

            if (!tonomat.poateDaRest(rest)) {
                std::cout << "Tonomatul nu poate oferi restul.\n";
                return false;
            }

            // Scade restul efectiv
            tonomat.retrageSuma(rest);

            std::cout << "Produs achizitionat: " << p.get_nume() << "\n";
            std::cout << "Rest primit: " << rest / 100.0 << " lei\n";
            return true;
        }
    }

    std::cout << "Produs cu codul " << cod << " nu exista.\n";
    return false;
}

