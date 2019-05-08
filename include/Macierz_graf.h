//
// Created by MacBook on 2019-05-08.
//

#ifndef PROJECT_2_MACIERZ_GRAF_H
#define PROJECT_2_MACIERZ_GRAF_H

#include <utility>
#include <memory.h>
#include "List.h"
#include "Vector.h"

template<typename T>
class Macierz_graf {

public:
    typedef std::pair<int, int> Edge;
    typedef std::pair<int, int> Vertixes;
    typedef int Vertex;

    Macierz_graf();

    ~Macierz_graf();

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
    struct Node {
        Node() {
            connected = false;
        }

        bool connected;
        T value;
    };

    Node *tab;
    struct VData {
        T value;
        bool deleted = false;
    };
    VData *vertex_data;
    int max_vertex_count = 0;
};

template<typename T>
Macierz_graf<T>::Macierz_graf() : tab(nullptr), vertex_data(nullptr) {

}

template<typename T>
Macierz_graf<T>::~Macierz_graf() {
    if (tab) {
        delete[] tab;
    }
    if (vertex_data) {
        delete[] vertex_data;
    }
}

template<typename T>
typename Macierz_graf<T>::Vertixes Macierz_graf<T>::endVerticles(Macierz_graf::Edge e) {
    return e;
}

template<typename T>
typename Macierz_graf<T>::Vertex Macierz_graf<T>::oposite(Macierz_graf::Vertex v, Macierz_graf::Edge e) {
    if (tab[e.first + max_vertex_count * e.second].connected == 0) {
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
bool Macierz_graf<T>::areAdjacent(Macierz_graf::Vertex v, Macierz_graf::Vertex w) {
    if (tab[v + max_vertex_count * w].connected) {
        return true;
    }

    return false;
}

template<typename T>
void Macierz_graf<T>::replace(Macierz_graf::Vertex v, T t) {
    vertex_data[v].value = t;
}

template<typename T>
void Macierz_graf<T>::replace(Macierz_graf::Edge ptr, T t) {
    tab[ptr.first + max_vertex_count * ptr.second] = t;
    tab[ptr.second + max_vertex_count * ptr.first] = t;
}

template<typename T>
typename Macierz_graf<T>::Vertex Macierz_graf<T>::insertVertex(T t) {
    ++max_vertex_count;
    Node *newtab = new Node[max_vertex_count * 2];

    memcpy(newtab, tab, sizeof(Node) * (max_vertex_count - 1) * 2);

    delete[] tab;
    tab = newtab;

    auto *newvertexdata = new VData[max_vertex_count];

    memcpy(newvertexdata, vertex_data, sizeof(VData) * (max_vertex_count - 1));

    delete[] vertex_data;
    vertex_data = newvertexdata;

    vertex_data[max_vertex_count - 1].value = t;

    return max_vertex_count - 1;
}

template<typename T>
typename Macierz_graf<T>::Edge Macierz_graf<T>::insertEdge(Macierz_graf::Vertex w, Macierz_graf::Vertex v, T t) {
    tab[w + max_vertex_count * v].connected = true;
    tab[w + max_vertex_count * v].value = t;

    tab[v + max_vertex_count * w].connected = true;
    tab[v + max_vertex_count * w].value = t;
    return std::make_pair(w, v);
}

template<typename T>
void Macierz_graf<T>::removeVertex(Macierz_graf::Vertex ptr) {
    for (int i = 0; i < max_vertex_count; ++i) {
        tab[ptr + max_vertex_count * i].connected = false;
        tab[i + max_vertex_count * ptr].connected = false;
    }
    vertex_data[ptr].deleted = true;
}

template<typename T>
void Macierz_graf<T>::removeEdge(Macierz_graf::Edge ptr) {
    tab[ptr.first + max_vertex_count * ptr.second].connected = false;
    tab[ptr.second + max_vertex_count * ptr.first].connected = false;
}

template<typename T>
List<typename Macierz_graf<T>::Edge> Macierz_graf<T>::incidentEdges(Macierz_graf::Vertex ptr) {
    List<Edge> l;

    for (int i = 0; i < max_vertex_count; ++i) {
        if (tab[i + max_vertex_count * ptr].connected)
            l.push(std::make_pair(ptr, i));
    }

    return l;
}

template<typename T>
List<typename Macierz_graf<T>::Vertex> Macierz_graf<T>::verticles() {
    List<Vertex> l;

    for (int i = 0; i < max_vertex_count; ++i) {
        if (!vertex_data[i].deleted) {
            l.push(i);
        }
    }


    return l;
}

template<typename T>
List<typename Macierz_graf<T>::Edge> Macierz_graf<T>::edges() {
    List<Edge> l;

    for (int i = 0; i < max_vertex_count * 2; ++i) {
        if (tab[i].connected) {
            l.push(std::make_pair(i, i % max_vertex_count));
            l.push(std::make_pair(i % max_vertex_count, i));
        }
    }


    return l;
}

#endif //PROJECT_2_MACIERZ_GRAF_H
