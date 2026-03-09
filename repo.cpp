//
// Created by www on 5/3/2025.
//
#include "repo.h"



Repo::Repo() {};

Repo::~Repo() {};

void Repo::addItem(const Produs &p) {
    produse.push_back(p);
}

vector<Produs> Repo::getAll() const {
    return produse;
}

int Repo::size() const {
    return produse.size();
}

bool Repo::deleteItem(int cod) {
    for (auto it =produse.begin( ); it!= produse.end(); it++) {
        if (it->get_cod() == cod) {
            produse.erase(it);
            return true;
        }
    }
    return false;
}

bool Repo::updateItem(int cod, const Produs &nou) {
    for (auto& p: produse) {
        if (p.get_cod() == cod) {
            p.set_nume(nou.get_nume());
            p.set_pret(nou.get_pret());
            return true;
        }
    }
    return false;
}


