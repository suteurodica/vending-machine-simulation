#ifndef PRODUS_H
#define PRODUS_H

#include <string>
using namespace std;

class Produs {
private:
    int cod;
    string nume;
    int pret; // stocat în BANI (ex: 250 = 2.5 lei)

public:
    Produs();
    Produs(int cod, string nume, double pret); // primește lei

    int get_cod() const;
    string get_nume() const;
    double get_pret() const; // returnează în lei

    void set_cod(int c);
    void set_nume(const string& n);
    void set_pret(double p); // primește lei
};

#endif // PRODUS_H
