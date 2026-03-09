#ifndef REPOFILE_H
#define REPOFILE_H

#include "repo.h"
#include <string>

class RepoFile : public Repo {
private:
    std::string filename;

public:
    RepoFile(const std::string& fname);
    void loadFromFile();
    void saveToFile();
    void addItem(const Produs& p) override;
    bool deleteItem(int cod) override;
    bool updateItem(int cod, const Produs& p) override;
};

#endif
