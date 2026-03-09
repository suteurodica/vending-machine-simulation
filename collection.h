#ifndef COLLECTION_H
#define COLLECTION_H

template<typename T>
struct pereche {
    T elem;
    int frecv;
};

template<typename T>
class Collection {
private:
    pereche<T>* elems;
    int len;
    int capacity;
    void resize();

public:
    Collection();
    Collection(const Collection<T>& other);
    Collection<T>& operator=(const Collection<T>& other);
    ~Collection();

    void add(T elem);
    bool remove(T elem);
    bool search(T elem) const;
    int size() const;
    T getAt(int position) const;
    int nrOccurrences(T elem) const;
    void afisare() const;
    int totalElements() const;
};

#include "Collection.tpp"

#endif // COLLECTION_H
