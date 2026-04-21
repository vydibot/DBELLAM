#include <iostream>
#include "Grafo.hpp"

int main(){
    Grafo grafo;
    grafo.agregarNodo(1);
    grafo.agregarNodo(2);
    grafo.agregarNodo(3);
    grafo.agregarNodo(4);
    grafo.conectar(1,2);
    grafo.conectar(1,4);
    grafo.conectar(2,3);
    grafo.conectar(2,4);
    grafo.mostrarGrafo();
    grafo.DFS(1);
    return 0;
}