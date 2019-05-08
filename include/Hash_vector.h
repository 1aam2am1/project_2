//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_HASH_VECTOR_H
#define PROJECT_2_HASH_VECTOR_H


class Hash_vector {
public:
    Hash_vector(int N) : _N(N) {}

    virtual ~Hash_vector() {};

    ///< Add value int to vector
    ///< /return true if added
    virtual bool add(int) = 0;

    ///< Remove value int if exist
    ///< /return true if removed
    virtual bool remove(int) = 0;

    ///< Search if that value exists
    ///< /return true if exists
    virtual bool search(int) = 0;

protected:
    int _N;
};


#endif //PROJECT_2_HASH_VECTOR_H
