#include "Nodo.hpp"

/**
 * @brief Constructor del nodo
 * @param dato Valor entero que identifica al nodo
 */
Nodo::Nodo(int dato) {
    this->dato = dato;
}

/**
 * @brief Obtiene el dato del nodo
 * @return Valor entero del nodo
 */
int Nodo::getDato() const {
    return dato;
}

/**
 * @brief Agrega un nodo adyacente con su peso
 * @param nodo Puntero al nodo adyacente
 * @param peso Peso de la arista hacia el nodo
 */
void Nodo::agregarAdyacente(Nodo* nodo, int peso){
    adyacentes[nodo] = peso;  // Usar map para almacenar (nodo, peso)
}

/**
 * @brief Obtiene los nodos adyacentes (sin pesos)
 * @return Vector de punteros a nodos adyacentes
 * 
 * Método legacy mantenido para compatibilidad con BFS/DFS
 * que no requieren información de pesos.
 */
const std::vector<Nodo*>& Nodo::getAdyacentes() const{
    static vector<Nodo*> resultado;
    resultado.clear();
    for (auto& par : adyacentes) {
        resultado.push_back(par.first);
    }
    return resultado;
}

/**
 * @brief Obtiene los nodos adyacentes con sus pesos
 * @return Mapa de punteros a nodos con sus respectivos pesos
 * 
 * Método para algoritmos de camino mínimo (Dijkstra, Bellman-Ford)
 * que necesitan conocer el peso de cada arista.
 */
const std::map<Nodo*, int>& Nodo::getAdyacentesConPeso() const{
    return adyacentes;
}