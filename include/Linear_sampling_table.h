//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_LINEAR_SAMPLING_TABLE_H
#define PROJECT_2_LINEAR_SAMPLING_TABLE_H

#include "Hash_vector.h"

class Linear_sampling_table : public Hash_vector {
public:
    Linear_sampling_table(int n);

    virtual ~Linear_sampling_table();

    bool add(int i) override;

    bool remove(int i) override;

    bool search(int i) override;

private:
    struct Node {
        int value;
        bool dostepny;
    };

    Node **_table;
};


#endif //PROJECT_2_LINEAR_SAMPLING_TABLE_H
