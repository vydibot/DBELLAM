#include <iostream>
#include "Grafo.hpp"

int main(){
    Grafo grafo;
    grafo.agregarNodo(1);
    grafo.agregarNodo(2);
    grafo.agregarNodo(3);
    grafo.agregarNodo(4);
    grafo.agregarNodo(5);
    grafo.agregarAristaPonderada(1, 2, 10);
    grafo.agregarAristaPonderada(1, 3, 5);
    grafo.agregarAristaPonderada(2, 4, 1);
    grafo.agregarAristaPonderada(2, 3, 2);
    grafo.agregarAristaPonderada(3, 4, 9);
    grafo.agregarAristaPonderada(5, 3, 2);
    grafo.mostrarGrafo();
    grafo.Dijkstra(1);
    grafo.BellmanFord(1);//Encontrar el camino
    grafo.BellmanFord(5);//Encontrar el camino
    grafo.BFS(1);
    return 0;
}