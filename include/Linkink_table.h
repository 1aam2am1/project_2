//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_LINKINK_TABLE_H
#define PROJECT_2_LINKINK_TABLE_H

#include "Hash_vector.h"

class Linkink_table : public Hash_vector {
public:
    Linkink_table(int n);

    virtual ~Linkink_table();

    bool add(int i) override;

    bool remove(int i) override;

    bool search(int i) override;

private:
    struct Node {
        int value;
        Node *next;
    };

    ///Wskaznik na tablice wskaznikow do listy
    Node **_table;
};


#endif //PROJECT_2_LINKINK_TABLE_H
