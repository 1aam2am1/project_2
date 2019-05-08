//
// Created by MacBook on 2019-05-08.
//

#include "Linkink_table.h"
#include <cstdio>

Linkink_table::Linkink_table(int n) : Hash_vector(n) {
    _table = new Node *[n];

    for (int i = 0; i < n; ++i) {
        _table[i] = nullptr;
    }
}

Linkink_table::~Linkink_table() {
    for (int i = 0; i < _N; ++i) {

        ///Usun wszystkie elementy w listach
        if (_table[i]) {
            Node *next;
            Node *parent;
            parent = _table[i];
            while (parent) {
                next = parent->next;
                delete parent;
                parent = next;
            }
        }
    }

    delete[] _table;
}


bool Linkink_table::add(int i) {
    int hash = i % _N;
    int probka = 1;

    if (_table[hash]) {
        Node *lista = _table[hash];
        Node *nowa = new Node;
        nowa->value = i;
        nowa->next = nullptr;

        while (lista) {
            if (lista->value == i) {
                delete nowa;
                printf("add(%i) f: %i\n", i, probka);
                return false;
            }
            if (lista->next == nullptr) {
                lista->next = nowa;
                break;
            } else {
                ++probka;
                lista = lista->next;
            }
        }
    } else {
        Node *nowa = new Node;
        nowa->value = i;
        nowa->next = nullptr;

        _table[hash] = nowa;
    }

    printf("add(%i) t: %i\n", i, probka);
    return true;
}

bool Linkink_table::remove(int i) {
    int hash = i % _N;

    int probka = 1;

    if (_table[hash]) {
        if (_table[hash]->value == i) {
            Node *next = _table[hash]->next;
            delete _table[hash];
            _table[hash] = next;
            printf("r(%i) t: %i\n", i, probka);
            return true;
        }
        Node *parent = _table[hash];

        while (parent->next) {
            ++probka;
            if (parent->next->value == i) {
                Node *next = parent->next->next;
                delete parent->next;
                parent->next = next;
                printf("r(%i) t: %i\n", i, probka);
                return true;
            }
            parent = parent->next;
        }
    }

    printf("r(%i) f: %i\n", i, probka);
    return false;
}

bool Linkink_table::search(int i) {
    int hash = i % _N;
    int probka = 1;

    if (_table[hash]) {
        Node *lista = _table[hash];

        while (lista) {
            if (lista->value == i) {
                printf("s(%i) f: %i\n", i, probka);
                return true;
            }
            ++probka;
            lista = lista->next;
        }
    }

    printf("s(%i) f: %i\n", i, probka);
    return false;
}