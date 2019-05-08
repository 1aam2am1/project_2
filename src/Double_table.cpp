//
// Created by MacBook on 2019-05-08.
//

#include "Double_table.h"
#include <cstdio>
#include <cstdlib>

static bool pierwsza(int n) {

    if (n < 2) {
        return false; //gdy liczba jest mniejsza niż 2 to nie jest pierwszą
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false; //gdy znajdziemy dzielnik, to dana liczba nie jest pierwsza
        }
    }

    return true;
}

Double_table::Double_table(int n) : Hash_vector(n) {

    q = n;
    do {
        q = q - 1;
        if (q <= 2) {
            printf("Error\n");
            std::exit(-1);
        }
    } while (!pierwsza(q));

    printf("q: %i\n", q);

    _table = new Node *[n];

    for (int i = 0; i < n; ++i) {
        _table[i] = nullptr;
    }
}

Double_table::~Double_table() {
    for (int i = 0; i < _N; ++i) {
        if (_table[i]) {
            delete _table[i];
        }
    }

    delete[] _table;

}

bool Double_table::add(int i) {
    int hash = i % _N;
    int hash2 = q - i % q;

    int probka = 1;

    for (int j = 0; j < _N; ++j) {
        int h = hash = (hash + j * hash2) % _N;
        if (_table[h] == nullptr) {
            _table[h] = new Node;
            _table[h]->dostepny = false;
            _table[h]->value = i;

            printf("add(%i) t: %i\n", i, probka);
            return true;
        }
        if (_table[h]->dostepny) {
            _table[h]->dostepny = false;
            _table[h]->value = i;

            printf("add(%i) t: %i\n", i, probka);
            return true;
        }
        ///Druga funkcja hashujaca niemoze przyjmowac zera
        if (i == 0) {
            printf("add(%i) f: %i\n", i, probka);
            return false;
        }

        ++probka;
    }

    printf("add(%i) f: %i\n", i, probka);
    return false;
}

bool Double_table::remove(int i) {
    int hash = i % _N;
    int hash2 = q - i % q;
    int probka = 1;

    for (int j = 0; j < _N; ++j) {
        int h = hash = (hash + j * hash2) % _N;
        if (_table[h] == nullptr) {
            printf("r(%i) f: %i\n", i, probka);
            return false;
        } else {
            if (_table[h]->value == i && !_table[h]->dostepny) {
                _table[h]->dostepny = true;
                printf("r(%i) t: %i\n", i, probka);
                return true;
            }
        }
        ///Druga funkcja hashujaca niemoze przyjmowac zera
        if (i == 0) {
            return false;
        }
        ++probka;
    }

    printf("r(%i) f: %i\n", i, probka);
    return false;
}

bool Double_table::search(int i) {
    int hash = i % _N;
    int hash2 = q - i % q;
    int probka = 1;

    for (int j = 0; j < _N; ++j) {
        int h = hash = (hash + j * hash2) % _N;
        if (_table[h] == nullptr) {
            printf("s(%i) f: %i\n", i, probka);
            return false;
        } else {
            if (_table[h]->value == i && !_table[h]->dostepny) {
                printf("s(%i) t: %i\n", i, probka);
                return true;
            }
        }
        ///Druga funkcja hashujaca niemoze przyjmowac zera
        if (i == 0) {
            return false;
        }
        ++probka;
    }

    printf("s(%i) f: %i\n", i, probka);
    return false;
}
