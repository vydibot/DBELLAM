#pragma once
#include <vector>
#include <iostream>
#include <map>
using namespace std;

/**
 * @class Nodo
 * @brief Representa un nodo en un grafo ponderado
 * 
 * Cada nodo contiene un dato (identificador) y un mapa de nodos
 * adyacentes con sus respectivos pesos.
 */
class Nodo{
    private:
        int dato;  /**< Valor entero que identifica al nodo */
        map<Nodo*, int> adyacentes;  /**< Mapa de nodos adyacentes con sus pesos */
    public:
        /**
         * @brief Constructor del nodo
         * @param dato Valor entero que identifica al nodo
         */
        Nodo(int dato);
        
        /**
         * @brief Obtiene el dato del nodo
         * @return Valor entero del nodo
         */
        int getDato() const;
        
        /**
         * @brief Agrega un nodo adyacente con su peso
         * @param nodo Puntero al nodo adyacente
         * @param peso Peso de la arista hacia el nodo
         */
        void agregarAdyacente(Nodo* nodo, int peso);
        
        /**
         * @brief Obtiene los nodos adyacentes (sin pesos)
         * @return Vector de punteros a nodos adyacentes
         * @note Para usar con BFS/DFS que no requieren pesos
         */
        const vector<Nodo*>& getAdyacentes() const;
        
        /**
         * @brief Obtiene los nodos adyacentes con sus pesos
         * @return Mapa de punteros a nodos con sus respectivos pesos
         * @note Para usar con algoritmos de camino mínimo (Dijkstra, Bellman-Ford)
         */
        const map<Nodo*, int>& getAdyacentesConPeso() const;
};