#pragma once
#include <vector>
#include <iostream>
using namespace std;

class  Nodo{
    private:
        int dato;
        vector<Nodo*> adyacentes;
    public:
        Nodo(int dato);
        int getDato() const;
        void agregarAdyacente(Nodo* nodo);
        const vector<Nodo*>& getAdyacentes() const;
};