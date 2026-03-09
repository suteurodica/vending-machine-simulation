//
// Created by www on 5/3/2025.
//

#include <iostream>
#include <ostream>
#include "ui.h"
#include "service.h"
#include "exceptii.h"



UI::UI(Service& service) {
    this->service = service;
}

void UI::afiseaza_meniu() {
    cout << "Meniu:\n";
    cout << "1: Adauga produs\n";
    cout << "2: Afisare produse\n";
    cout << "3: Sterge produs\n";
    cout << "4: Modifica produs\n";
    cout << "5: Adauga monede\n";
    cout << "6: Cumpara produs\n";
    cout << "7: Afisare monede disponibile\n";
    cout << "0: Iesire\n";
}


void UI::afisare_toate() {
    vector<Produs> produse;
    produse = service.get_all();
    for (int i = 0; i < produse.size(); i++) {
        cout<< "Cod: "  <<produse[i].get_cod() <<" , ";
        cout<< "Nume: " <<produse[i].get_nume() <<" , ";
        cout << "Pret: " << produse[i].get_pret() / 100.0 << " lei" << endl;

    }
}

void UI::cumpara_produs() {
    int cod;
    double suma;
    cout << "Cod produs: ";
    cin >> cod;
    cout << "Suma introdusa (lei): ";
    cin >> suma;

    bool succes = service.achizitioneaza_produs(cod, suma);
    if (!succes) {
        cout << "Achizitia a esuat.\n";
    }
}

void UI::adauga_monede() {
    int valoare, nr;
    cout << "Valoare moneda (ex: 10, 50, 100): ";
    cin >> valoare;
    cout << "Numar monede: ";
    cin >> nr;
    service.adauga_monede(valoare, nr);
}


void UI::afisare_monede() {
    service.afisare_monede();
}


void UI::run() {
    int op;
    while (true) {
        afiseaza_meniu();
        cout << "Alege optiune: ";
        cin >> op;

        if (op == 0) break;

        if (op == 1) {
            int c;
            string n;
            double p;
            cout << "Cod produs: "; cin >> c;
            cout << "Nume produs: "; cin >> n;
            cout << "Pret (lei): "; cin >> p;
            int pr=p*100;
            try {
                service.adauga_produs(c, n, pr);
            } catch (const ProdusException& e) {
                cout << "Eroare: " << e.what() << endl;
            }
        } else if (op == 2) {
            afisare_toate();
        } else if (op == 3) {
            int c;
            cout << "Cod produs: "; cin >> c;
            try {
                service.deleteItem(c);
            } catch (const ProdusException& e) {
                cout << "Eroare: " << e.what() << endl;
            }
        } else if (op == 4) {
            int c;
            string n;
            double p;
            cout << "Cod produs: "; cin >> c;
            cout << "Nume nou: "; cin >> n;
            cout << "Pret nou (lei): "; cin >> p;
            int pr=p*100;
            try {
                service.updateItem(c, n, pr);
            } catch (const ProdusException& e) {
                cout << "Eroare: " << e.what() << endl;
            }
        } else if (op == 5) {
            adauga_monede();
        } else if (op == 6) {
            cumpara_produs();
        } else if (op == 7) {
            afisare_monede();
        } else {
            cout << "Optiune invalida!\n";
        }
    }
}
