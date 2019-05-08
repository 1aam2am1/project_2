//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_DOUBLE_TABLE_H
#define PROJECT_2_DOUBLE_TABLE_H

#include "Hash_vector.h"


class Double_table : public Hash_vector {
public:
    Double_table(int n);

    virtual ~Double_table();

    bool add(int i) override;

    bool remove(int i) override;

    bool search(int i) override;

private:
    struct Node {
        int value;
        bool dostepny;
    };
    Node **_table;

    int q;
};


#endif //PROJECT_2_DOUBLE_TABLE_H
