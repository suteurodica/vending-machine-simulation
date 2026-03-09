//
// Created by www on 5/3/2025.
//
#include <cassert>
#include <fstream>

#include "repo.h"
#include "service.h"
#include "tonomat.h"
#include "repofile.h"
#include "exceptii.h"
#include "validator.h"


void test_add_getall_repo() {

    Repo repo;

    assert(repo.size() == 0);

    Produs produs1(1, "baton",7 );
    Produs produs2(2, "suc",10 );

    repo.addItem(produs1);
    repo.addItem(produs2);

    assert(repo.size() == 2);

    vector<Produs> produse = repo.getAll();
    assert(produse[0].get_cod() == 1);
    assert(produse[0].get_nume() == "baton");
    assert(produse[1].get_cod() == 2);
    assert(produse[1].get_nume() == "suc");

    repo.deleteItem(1);
    assert(repo.size() == 1);

    Produs p(4,"apa",7);
    repo.updateItem(2, p);
    assert(repo.getAll()[0].get_nume()=="apa");


}
void testService() {
    Service service;

    service.adauga_produs(1,"baton", 15);
    service.adauga_produs(2,"suc", 7);

    vector<Produs> produse;
    produse = service.get_all();
    assert(produse[0].get_cod() == 1);
    assert(produse[0].get_nume() == "baton");
    assert(produse[1].get_cod() == 2);
    assert(produse[1].get_nume() == "suc");
    assert(produse.size()==2);

    try {
        service.adauga_produs(3,"a", 15);
        assert(false);
    } catch (ProdusException e) {
        assert(std::string(e.what()) == "Numele produsului este prea scurt!");
    }

    try {
        service.adauga_produs(2, "suc", -5);  // preț invalid
        assert(false);
    } catch (ProdusException& e) {
        assert(std::string(e.what()) == "Pretul trebuie sa fie pozitiv!");
    }


    try {
        service.deleteItem(999);  // cod inexistent
        assert(false); // dacă nu aruncă excepție, testul pică
    } catch (ProdusInexistentException& e) {
        assert(std::string(e.what()) == "Produsul nu exista si nu poate fi sters!");
    }

    try {
        service.updateItem(999, "apa", 5);  // cod inexistent
        assert(false);
    } catch (ProdusInexistentException& e) {
        assert(std::string(e.what()) == "Produsul nu exista si nu poate fi actualizat!");
    }


    try {
        service.adauga_produs(1, "altceva", 15);  // cod deja existent
        assert(false);
    } catch (CodDuplicatException& e) {
        assert(std::string(e.what()) == "Exista deja un produs cu acest cod!");
    }

}

void test_validator() {
    // Test nume prea scurt
    try {
        ProdusValidator::valideaza(1, "a", 10);
        assert(false);
    } catch (ProdusException& e) {
        assert(std::string(e.what()) == "Numele produsului este prea scurt!");
    }

    // Test preț negativ
    try {
        ProdusValidator::valideaza(1, "cola", -5);
        assert(false);
    } catch (ProdusException& e) {
        assert(std::string(e.what()) == "Pretul trebuie sa fie pozitiv!");
    }

    // Test cod invalid
    try {
        ProdusValidator::valideaza(0, "apa", 5);
        assert(false);
    } catch (ProdusException& e) {
        assert(std::string(e.what()) == "Codul trebuie sa fie un numar pozitiv!");
    }

    // Test date corecte
    try {
        ProdusValidator::valideaza(1, "suc", 5);
        // Nu ar trebui să arunce nimic
    } catch (...) {
        assert(false); // dacă aruncă ceva, testul pică
    }
}

void test_tonomat() {
    Tonomat t;
    t.adaugaMonede(50,5);
    t.adaugaMonede(10,3);
    assert(t.poateDaRest(200));
    assert(!t.poateDaRest(300));
    assert(!t.poateDaRest(40));

    Collection<int> r= t.calculeazaRest(70);
    assert(r.size()==2);
    assert(r.totalElements() == 3);


}
void test_retrageSuma() {
    Tonomat t;
    t.adaugaMonede(50, 2); // 100 bani
    t.adaugaMonede(10, 1); // 10 bani

    assert(t.poateDaRest(100));
    t.retrageSuma(100);

    // Acum trebuie să mai rămână doar 1x10
    assert(!t.poateDaRest(100));  // nu mai are 2x50
    assert(t.poateDaRest(10));    // are încă o monedă de 10
}

void test_achizitie_service() {
    Service s;

    // Adaugă produs: ciocolata, 1.20 lei = 120 bani
    s.adauga_produs(1, "ciocolata", 120);

    // Adaugă monede: 2x50 + 2x10 = 120 bani exact
    s.adauga_monede(50, 2);
    s.adauga_monede(10, 2);

    // Caz 1: clientul plătește exact cât trebuie → trebuie să reușească
    assert(s.achizitioneaza_produs(1, 1.20)); // TRUE

    // Caz 2: produs inexistent → trebuie să eșueze
    assert(!s.achizitioneaza_produs(99, 2.00)); // FALSE

    // Adaugă alt produs: napolitana, 1.00 lei = 100 bani
    s.adauga_produs(2, "napolitana", 100);

    assert(!s.achizitioneaza_produs(2, 5)); // FALSE, NU poate da rest
}

#include "repofile.h"

void test_repo_file() {
    const std::string testFile = "test_repo.txt";

    // PAS 1: scriem manual un fișier de test
    {
        std::ofstream fout(testFile);
        fout << "1 cola 2.5\n";
        fout << "2 apa 1.0\n";
        fout.close();
    }

    // PAS 2: încărcăm repo-ul din fișier
    RepoFile repo(testFile);
    assert(repo.size() == 2);
    assert(repo.getAll()[0].get_nume() == "cola");
    assert(repo.getAll()[1].get_pret() == 100);

    // PAS 3: adăugăm produs nou
    Produs p3(3, "fanta", 300); // preț în bani
    repo.addItem(p3);
    assert(repo.size() == 3);

    // PAS 4: modificăm produs
    Produs p3_modificat(3, "fantaZero", 350);
    repo.updateItem(3, p3_modificat);
    assert(repo.getAll()[2].get_pret() == 350);

    // PAS 5: ștergem un produs
    repo.deleteItem(1);
    assert(repo.size() == 2);

    // PAS 6: testăm persistenta
    RepoFile reloadRepo(testFile); // se reîncarcă din fișier
    assert(reloadRepo.size() == 2);
    assert(reloadRepo.getAll()[0].get_cod() == 2);
    assert(reloadRepo.getAll()[1].get_nume() == "fantaZero");

    // 🧹 Cleanup (opțional): șterge fișierul de test
    std::remove(testFile.c_str());
}


void ruleazaTeste() {
    test_add_getall_repo();
    testService();
    test_tonomat();
    test_retrageSuma();
    test_achizitie_service();
    test_repo_file();
    test_validator();
}
