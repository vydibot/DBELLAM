#pragma once
#include <vector>
#include <iostream>
#include <map>
using namespace std;

class  Nodo{
    private:
        int dato;
        map<Nodo*, int> adyacentes;  // Cambiado a map para almacenar (nodo, peso)
    public:
        Nodo(int dato);
        int getDato() const;
        void agregarAdyacente(Nodo* nodo, int peso);
        const vector<Nodo*>& getAdyacentes() const;
        const map<Nodo*, int>& getAdyacentesConPeso() const;  // Nuevo método
};