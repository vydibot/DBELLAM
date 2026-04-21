#pragma once
#include "Nodo.hpp"

/**
 * @class Grafo
 * @brief Clase que representa un grafo ponderado no dirigido
 * 
 * Implementa algoritmos de recorrido (BFS, DFS) y algoritmos de
 * camino mínimo (Dijkstra, Bellman-Ford)
 */
class Grafo{
    private:
        vector<Nodo*> nodos;  /**< Vector de nodos del grafo */
    public:
        /**
         * @brief Constructor por defecto del grafo
         */
        Grafo();
        
        /**
         * @brief Agrega un nuevo nodo al grafo
         * @param dato Valor entero que identifica al nodo
         * @return Puntero al nodo creado
         */
        Nodo* agregarNodo(int dato);
        
        /**
         * @brief Conecta dos nodos con una arista ponderada
         * @param valor1 Valor del primer nodo
         * @param valor2 Valor del segundo nodo
         * @param peso Peso de la arista (por defecto 1)
         */
        void conectar(int valor1, int valor2, int peso = 1);
        
        /**
         * @brief Alias para conectar - crea arista ponderada
         * @param valor1 Valor del primer nodo
         * @param valor2 Valor del segundo nodo
         * @param peso Peso de la arista
         */
        void agregarAristaPonderada(int valor1, int valor2, int peso);
        
        /**
         * @brief Muestra el grafo por consola
         */
        void mostrarGrafo() const;
        
        /**
         * @brief Busca un nodo por su valor
         * @param dato Valor del nodo a buscar
         * @return Puntero al nodo encontrado o nullptr
         */
        Nodo* buscarNodo(int dato) const;
        
        /**
         * @brief Recorrido en anchura (Breadth-First Search)
         * @param valorInicial Nodo desde donde开始 recorrido
         */
        void BFS(int valorInicial);
        
        /**
         * @brief Recorrido en profundidad (Depth-First Search)
         * @param valorInicial Nodo desde donde开始 recorrido
         */
        void DFS(int valorInicial);
        
        /**
         * @brief Algoritmo de Dijkstra para camino mínimo
         * @param origen Nodo de origen para calcular distancias
         */
        void Dijkstra(int origen) const;
        
        /**
         * @brief Algoritmo de Bellman-Ford para camino mínimo
         * @param origen Nodo de origen para calcular distancias
         * @note Puede manejar pesos negativos (sin ciclos negativos)
         */
        void BellmanFord(int origen) const;
};
