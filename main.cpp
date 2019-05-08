#include <iostream>
#include <cstdio>
#include <random>
#include <unordered_map>
#include "Linkink_table.h"
#include "Linear_sampling_table.h"
#include "Double_table.h"
#include "List_grapf.h"
#include "Macierz_graf.h"

bool pierwsza(int n) {

    if (n < 2) {
        return false; //gdy liczba jest mniejsza niż 2 to nie jest pierwszą
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false; //gdy znajdziemy dzielnik, to dana liczba nie jest pierwsza
        }
    }

    return true;
}

int main() {
    /*int n;
    int added;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 20000);
    std::unordered_map<int, int> generated;

    do {
        printf("Podaj wielkosc tablicy: \n");

        scanf("%i", &n);
    }while(!pierwsza(n));

    do {
        printf("Podaj ilosc elementow do wprawadzenia: \n");

        scanf("%i", &added);
    }while(!pierwsza(added));

    Hash_vector* hash_type[3];
    printf("1: Linkink_table\n");
    printf("2: Linear_sampling_table\n");
    printf("3: Double_table\n");
    hash_type[0] = new Linkink_table(n);
    hash_type[1] = new Linear_sampling_table(n);
    hash_type[2] = new Double_table(n);


    for(int i = 0; i < added; ++i){
        int value = dis(gen);

        while(generated.find(value) != generated.end()){
            value = dis(gen);
        }
        generated.emplace(value, value);

        for(int j = 0; j < 3; ++j){
            printf("%i: ", j);
            hash_type[j]->add(value);
        }
    }

    int v2 = dis(gen);
    while(generated.find(v2) != generated.end()){
        v2 = dis(gen);
    }
    generated.emplace(v2, v2);
    generated.emplace_hint(generated.begin(), v2, v2);

    int i = 0;
    for(auto it = generated.begin(); it != generated.end(); ++it){
        int value = it->first;

        for(int j = 0; j < 3; ++j){
            printf("%i: ", j);
            hash_type[j]->search(value);
        }
        ++i;
        if(i > 10){break;}
    }

    i = 0;
    for(auto it = generated.cbegin(); it != generated.cend(); ++it){
        int value = it->first;

        for(int j = 0; j < 3; ++j){
            printf("%i: ", j);
            hash_type[j]->remove(value);
        }
        ++i;
        if(i > 10){break;}
    }




    for(int i = 0; i < 3; ++i){
        delete hash_type[i];
    }



*/



    ///*******************************grafs********************************///



    Macierz_graf<int> graf;
    //List_grapf<int> graf;

    auto v1 = graf.insertVertex(5);

    for (int i = 0; i < 10; ++i) {
        graf.insertVertex(i);
    }
    auto v2 = graf.insertVertex(6);

    auto e1 = graf.insertEdge(v1, v2, 7);
    graf.insertEdge(2, 4, 0);
    graf.insertEdge(11, 11, 0);
    graf.insertEdge(0, 5, 0);


    graf.endVerticles(e1);
    graf.oposite(v1, e1);
    graf.replace(v1, -5);
    graf.incidentEdges(v1);
    graf.edges();


    graf.removeEdge(std::make_pair(4, 2));
    graf.removeVertex(3);

    auto v = graf.verticles();

    printf("   ");
    for (auto it = v.begin(); it != v.end(); it = it->next) {
        printf("%i ", it->value);
    }
    printf("\n");

    for (auto it = v.begin(); it != v.end(); it = it->next) {
        printf("%i: ", it->value);
        for (auto it2 = v.begin(); it2 != v.end(); it2 = it2->next) {
            if (graf.areAdjacent(it->value, it2->value)) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }


    return 0;
}