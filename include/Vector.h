//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_VECTOR_H
#define PROJECT_2_VECTOR_H

template<typename T>
class Vector {
public:
    Vector(T *t, int size) : tab(t), _size(size) {

    }

    const T &operator[](int i) {
        return tab[i];
    }

    int size() {
        return _size;
    }

private:
    T *tab;
    int _size;
};


#endif //PROJECT_2_VECTOR_H
