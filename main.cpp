#include <iostream>
#include "Grafo.hpp"

int main(){
    Grafo grafo;
    grafo.agregarNodo(1);
    grafo.agregarNodo(2);
    grafo.agregarNodo(3);
    grafo.agregarNodo(4);
    grafo.conectar(1, 2, 4);   // peso 4
    grafo.conectar(1, 4, 2);   // peso 2
    grafo.conectar(2, 3, 3);   // peso 3
    grafo.conectar(2, 4, 1);   // peso 1
    grafo.mostrarGrafo();
    grafo.DFS(1);
    grafo.Dijkstra(1);
    return 0;
}