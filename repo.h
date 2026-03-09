//
// Created by www on 5/3/2025.
//

#ifndef REPO_H
#define REPO_H

#include <vector>;
using namespace std;
#include "produs.h"

class Repo {
    protected:
    vector<Produs>  produse;
    public:
    Repo();
    virtual ~Repo();

    virtual void addItem(const Produs& p);
    vector<Produs> getAll() const;
    int size() const;

    virtual bool deleteItem(int cod);
    virtual bool updateItem(int cod, const Produs& p);


};








#endif //REPO_H
