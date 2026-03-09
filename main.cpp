#include <iostream>
#include "teste.h"
#include "UI.h"
#include "repofile.h"

int main() {
    std::cout<<"TESTE"<<endl;

    ruleazaTeste();
    std::cout<<"Toate testele au trecut"<<endl;

    RepoFile repoFile("produse.txt");
    Service service(&repoFile);
    UI ui(service);
    ui.run();
    return 0;

}