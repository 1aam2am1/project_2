//
// Created by MacBook on 2019-05-08.
//

#include "Linear_sampling_table.h"
#include <cstdio>

Linear_sampling_table::Linear_sampling_table(int n) : Hash_vector(n) {
    _table = new Node *[n];

    for (int i = 0; i < _N; ++i) {
        _table[i] = nullptr;
    }

}

Linear_sampling_table::~Linear_sampling_table() {
    for (int i = 0; i < _N; ++i) {
        if (_table[i]) {
            delete _table[i];
        }
    }

    delete[] _table;
}

bool Linear_sampling_table::add(int i) {
    int hash = i % _N;

    int probka = 1;

    int position = hash;
    while (true) {
        if (_table[position] == nullptr) {
            _table[position] = new Node;
            _table[position]->value = i;
            _table[position]->dostepny = false;

            printf("add(%i) t: %i\n", i, probka);
            return true;
        } else if (_table[position]->dostepny) {
            _table[position]->dostepny = false;
            _table[position]->value = i;

            printf("add(%i) t: %i\n", i, probka);
            return true;
        } else {
            ++probka;
            ++position;
            position = position % _N;
            if (position == hash) { break; }
        }
    }

    printf("add(%i) f: %i\n", i, probka);
    return false;
}

bool Linear_sampling_table::remove(int i) {
    int hash = i % _N;
    int probka = 1;

    int position = hash;
    while (true) {
        if (_table[position] == nullptr) {
            printf("r(%i) f: %i\n", i, probka);
            return false;
        } else {
            if (_table[position]->value == i && !_table[position]->dostepny) {
                _table[position]->dostepny = true;
                printf("r(%i) t: %i\n", i, probka);
                return true;
            }
            ++position;
            position = position % _N;
            if (position == hash) { break; }
            ++probka;
        }
    }
    printf("r(%i) f: %i\n", i, probka);
    return false;
}

bool Linear_sampling_table::search(int i) {
    int hash = i % _N;
    int probka = 1;

    int position = hash;
    while (true) {
        if (_table[position] == nullptr) {
            printf("s(%i) f: %i\n", i, probka);
            return false;
        } else {
            if (_table[position]->value == i && _table[position]->dostepny) {
                printf("s(%i) t: %i\n", i, probka);
                return true;
            }

            ++probka;
            ++position;
            position = position % _N;
            if (position == hash) { break; }
        }
    }

    printf("s(%i) f: %i\n", i, probka);
    return false;
}
