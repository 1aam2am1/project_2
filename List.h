//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_LIST_H
#define PROJECT_2_LIST_H

template<typename T>
class List {
public:
    List() : l(nullptr) {

    }

    ~List() {
        if (l) {
            Node *next;
            Node *parent;
            parent = l;
            while (parent) {
                next = parent->next;
                delete parent;
                parent = next;
            }
        }
    }

    struct Node {
        Node() : next(nullptr) {

        }

        T value;
        Node *next;
    };

    void push(T v) {
        if (l == nullptr) {
            l = new Node;
            l->value = v;
        } else {
            auto parent = l;
            while (parent->next) {
                parent = parent->next;
            }
            parent->next = new Node;
            parent->next->value = v;
        }
    }

    void remove(T v) {
        if (l->value == v) {
            auto *next = l->next;
            delete l;
            l = next;
        } else {
            auto *parent = l;

            while (parent->next) {
                if (parent->next->value == v) {
                    Node *next = parent->next->next;
                    delete parent->next;
                    parent->next = next;
                }
                parent = parent->next;
            }
        }
    }

    template<typename PredicateT>
    void remove_if(const PredicateT &predicate) {
        if (!l) { return; }
        if (predicate(l->value)) {
            auto *next = l->next;
            delete l;
            l = next;
        } else {
            auto *parent = l;

            while (parent->next) {
                if (predicate(parent->next->value)) {
                    Node *next = parent->next->next;
                    delete parent->next;
                    parent->next = next;
                }
                parent = parent->next;
            }
        }
    }

    Node *begin() {
        return l;
    }

    const Node *end() {
        return nullptr;
    }

private:
    Node *l;
};


#endif //PROJECT_2_LIST_H
