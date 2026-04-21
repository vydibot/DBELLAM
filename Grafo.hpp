#pragma once
#include "Nodo.hpp"

class Grafo{
    private:
        vector<Nodo*> nodos;
    public:
        Grafo();
        Nodo* agregarNodo(int dato);
        void conectar(int valor1, int valor2, int peso = 1);  // Peso por defecto = 1
        void mostrarGrafo() const;
        Nodo* buscarNodo(int dato)  const;
        void BFS(int valorInicial);
        void DFS(int valorInicial);
        void Dijkstra(int origen) const;  // Nuevo método
};
