#include "produs.h"

Produs::Produs() {
    this->cod = 0;
    this->nume = "";
    this->pret = 0;
}

Produs::Produs(int c, string n, double p) {
    this->cod = c;
    this->nume = n;
    this->pret = static_cast<int>(p * 100 + 0.5); // lei → bani
}

int Produs::get_cod() const {
    return this->cod;
}

string Produs::get_nume() const {
    return this->nume;
}

double Produs::get_pret() const {
    return pret / 100.0; // bani → lei
}

void Produs::set_cod(int c) {
    this->cod = c;
}

void Produs::set_nume(const string& n) {
    this->nume = n;
}

void Produs::set_pret(double p) {
    this->pret = static_cast<int>(p * 100 + 0.5); // lei → bani
}
