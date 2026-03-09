#include "repofile.h"
#include <fstream>
using namespace std;
#include <iostream>

RepoFile::RepoFile(const std::string& fname) {
    filename = fname;
    loadFromFile();
}

void RepoFile::loadFromFile() {


    produse.clear();
    std::ifstream fin(filename);
    int cod;
    std::string nume;
    double pret;
    while (fin >> cod >> nume >> pret) {


        produse.push_back(Produs(cod, nume, static_cast<int>(pret * 100 + 0.5)));
    }
    fin.close();

}

void RepoFile::saveToFile() {
    std::ofstream fout(filename);
    for (const auto& p : produse) {
        fout << p.get_cod() << " " << p.get_nume() << " " << p.get_pret() / 100.0 << "\n";
    }
    fout.close();
}

void RepoFile::addItem(const Produs& p) {
    Repo::addItem(p);
    saveToFile();
}

bool RepoFile::deleteItem(int cod) {
    bool rezultat = Repo::deleteItem(cod);
    if (rezultat) saveToFile();
    return rezultat;
}

bool RepoFile::updateItem(int cod, const Produs& p) {
    bool rezultat = Repo::updateItem(cod, p);
    if (rezultat) saveToFile();
    return rezultat;
}
