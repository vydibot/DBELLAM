#pragma once
#include "Nodo.hpp"

class Grafo{
    private:
        vector<Nodo*> nodos;
    public:
        Grafo();
        Nodo* agregarNodo(int dato);
        void conectar(int valor1, int valor2);
        void mostrarGrafo() const;
        Nodo* buscarNodo(int dato)  const;
        void BFS(int valorInicial);
        void DFS(int valorInicial);
};
