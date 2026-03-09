//
// Created by www on 5/3/2025.
//

#ifndef UI_H
#define UI_H
#include "service.h"

class UI {
private:
    Service service;
    void afiseaza_meniu();
    void afisare_toate();
    void cumpara_produs();
    void adauga_monede();
    void afisare_monede();

public:
    UI(Service& service);
    void run();


};

#endif //UI_H
