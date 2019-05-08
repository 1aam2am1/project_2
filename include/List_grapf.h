//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_LIST_GRAPF_H
#define PROJECT_2_LIST_GRAPF_H

#include <utility>
#include <memory.h>
#include "List.h"
#include "Vector.h"

template<typename T>
class List_grapf {
public:
    typedef std::pair<int, int> Edge;
    typedef std::pair<int, int> Vertixes;
    typedef int Vertex;

    List_grapf();

    ~List_grapf();

    ///Jakie wierzcholki laczy
    Vertixes endVerticles(Edge e);

    ///Jaki wierzcholek jest naprzeciwko
    Vertex oposite(Vertex v, Edge e);

    ///Czy wierzcholki sa polaczone
    bool areAdjacent(Vertex v, Vertex w);

    ///Zmien dane w wierzcholku
    void replace(Vertex v, T t);

    ///Zmien dane na krawedzi
    void replace(Edge ptr, T t);

    ///Dodaj wierzcholek o wartosci t
    Vertex insertVertex(T t);

    ///Dodaj krwedz o wartosci t pomiedzy (w,v)
    Edge insertEdge(Vertex w, Vertex v, T t);

    ///Usun wierzcholek i wszystkie krawedzie do niego nalezace
    void removeVertex(Vertex ptr);

    ///Usun krawedz
    void removeEdge(Edge ptr);

    ///Wszystkie krawedzie danego wierzcholka
    List<Edge> incidentEdges(Vertex ptr);

    ///Wszystkie wierzcholki
    List<Vertex> verticles();

    ///Wszystkie krawedzie
    List<Edge> edges();


private:
    int max_vertex_count = 0;

    struct Node {
        int connected;
        T value;
    };

    struct VNode {
        List<Node> list;
        T value;
        bool deleted = false;
    };

    VNode *list;
};

template<typename T>
List_grapf<T>::List_grapf() : list(nullptr) {

}

template<typename T>
List_grapf<T>::~List_grapf() {
    delete[] list;
}

template<typename T>
typename List_grapf<T>::Vertixes List_grapf<T>::endVerticles(List_grapf::Edge e) {
    return e;
}

template<typename T>
typename List_grapf<T>::Vertex List_grapf<T>::oposite(List_grapf::Vertex v, List_grapf::Edge e) {
    bool c = false;
    for (auto it = list[e.first].list.begin(); it != nullptr; it = it->next) {
        if (it->value.connected == e.second) {
            c = true;
        }
    }
    if (!c) {
        return -1;
    }
    if (e.first == v) {
        return e.second;
    } else if (e.second == v) {
        return e.first;
    }
    return -1;
}

template<typename T>
bool List_grapf<T>::areAdjacent(List_grapf::Vertex v, List_grapf::Vertex w) {
    for (auto it = list[v].list.begin(); it != nullptr; it = it->next) {
        if (it->value.connected == w) {
            return true;
        }
    }
    return false;
}

template<typename T>
void List_grapf<T>::replace(List_grapf::Vertex v, T t) {
    list[v].value = t;
}

template<typename T>
void List_grapf<T>::replace(List_grapf::Edge ptr, T t) {
    for (auto it = list[ptr.first].list.begin(); it != nullptr; it = it->next) {
        if (it->value.connected == ptr.second) {
            it->value.value = t;
        }
    }
    for (auto it = list[ptr.second].list.begin(); it != nullptr; it = it->next) {
        if (it->value.connected == ptr.first) {
            it->value.value = t;
        }
    }
}

template<typename T>
typename List_grapf<T>::Vertex List_grapf<T>::insertVertex(T t) {
    ++max_vertex_count;
    VNode *newlist = new VNode[max_vertex_count];

    for (int i = 0; i < max_vertex_count - 1; ++i) {

        newlist[i] = list[i];
        list[i].list = List<Node>();
    }

    delete[] list;
    list = newlist;

    list[max_vertex_count - 1].value = t;

    return max_vertex_count - 1;
}

template<typename T>
typename List_grapf<T>::Edge List_grapf<T>::insertEdge(List_grapf::Vertex w, List_grapf::Vertex v, T t) {
    list[w].list.push({v, t});
    list[v].list.push({w, t});
    return std::make_pair(w, v);
}

template<typename T>
void List_grapf<T>::removeVertex(List_grapf::Vertex ptr) {

    list[ptr].deleted = true;

    for (int i = 0; i < max_vertex_count; ++i) {
        list[i].list.remove_if([ptr](Node &a) -> bool { return a.connected == ptr; });
    }
}

template<typename T>
void List_grapf<T>::removeEdge(List_grapf::Edge ptr) {
    list[ptr.first].list.remove_if([ptr](Node &a) -> bool { return a.connected == ptr.second; });
    list[ptr.second].list.remove_if([ptr](Node &a) -> bool { return a.connected == ptr.first; });
}

template<typename T>
List<typename List_grapf<T>::Edge> List_grapf<T>::incidentEdges(List_grapf::Vertex ptr) {
    List<Edge> l;

    for (auto it = list[ptr].list.begin(); it != nullptr; it = it->next) {
        l.push(std::make_pair(ptr, it->value.connected));

    }

    return l;
}

template<typename T>
List<typename List_grapf<T>::Vertex> List_grapf<T>::verticles() {
    List<Vertex> l;

    for (int i = 0; i < max_vertex_count; ++i) {
        if (!list[i].deleted) {
            l.push(i);
        }
    }

    return l;
}

template<typename T>
List<typename List_grapf<T>::Edge> List_grapf<T>::edges() {
    List<Edge> l;

    for (int i = 0; i < max_vertex_count; ++i) {
        for (auto it = list[i].list.begin(); it != nullptr; it = it->next) {
            l.push(std::make_pair(i, it->value.connected));
        }
    }

    return l;
}


#endif //PROJECT_2_LIST_GRAPF_H
