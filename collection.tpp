#include <iostream>
using namespace std;

template<typename T>
Collection<T>::Collection() {
    capacity = 3;
    elems = new pereche<T>[capacity];
    len = 0;
}

template<typename T>
Collection<T>::~Collection() {
    delete[] elems;
    cout<<"~";
}

template<typename T>
Collection<T>::Collection(const Collection<T>& other) {
    capacity = other.capacity;
    len = other.len;
    elems = new pereche<T>[capacity];
    for (int i = 0; i < len; i++) {
        elems[i] = other.elems[i];
    }
}

template<typename T>
Collection<T>& Collection<T>::operator=(const Collection<T>& other) {
    if (this == &other)
        return *this;
    delete[] elems;
    capacity = other.capacity;
    len = other.len;
    elems = new pereche<T>[capacity];
    for (int i = 0; i < len; i++) {
        elems[i] = other.elems[i];
    }
    return *this;
}

template<typename T>
void Collection<T>::resize() {
    capacity *= 2;
    auto* temp = new pereche<T>[capacity];
    for (int i = 0; i < len; i++) {
        temp[i] = elems[i];
    }
    delete[] elems;
    elems = temp;
}

template<typename T>
void Collection<T>::add(T elem) {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            elems[i].frecv++;
            return;
        }
    }
    if (len == capacity) {
        resize();
    }
    elems[len++] = {elem, 1};
}

template<typename T>
bool Collection<T>::remove(T elem) {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) {
            if (elems[i].frecv > 1) {
                elems[i].frecv--;
            } else {
                for (int j = i; j < len - 1; j++) {
                    elems[j] = elems[j + 1];
                }
                len--;
            }
            return true;
        }
    }
    return false;
}

template<typename T>
bool Collection<T>::search(T elem) const {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) return true;
    }
    return false;
}

template<typename T>
int Collection<T>::size() const {
    return len;
}

template<typename T>
int Collection<T>::nrOccurrences(T elem) const {
    for (int i = 0; i < len; i++) {
        if (elems[i].elem == elem) return elems[i].frecv;
    }
    return 0;
}

template<typename T>
T Collection<T>::getAt(int position) const {
    return elems[position].elem;
}

template<typename T>
void Collection<T>::afisare() const {
    cout << "Elemente: ";
    for (int i = 0; i < len; i++) {
        cout << "(" << elems[i].elem << ", " << elems[i].frecv << ") ";
    }
    cout << endl;
}

template<typename T>
int Collection<T>::totalElements() const {
    int total = 0;
    for (int i = 0; i < len; i++) {
        total += elems[i].frecv;
    }
    return total;
}
