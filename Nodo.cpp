#include "Nodo.hpp"

Nodo::Nodo(int dato) {
    this->dato = dato;
}
int Nodo::getDato()const{
    return dato;
}
void Nodo::agregarAdyacente(Nodo* nodo, int peso){
    adyacentes[nodo] = peso;  // Usar map en lugar de push_back
}
const std::vector<Nodo*>& Nodo::getAdyacentes() const{
    // Método legacy mantenido para compatibilidad con BFS/DFS
    static vector<Nodo*> resultado;
    resultado.clear();
    for (auto& par : adyacentes) {
        resultado.push_back(par.first);
    }
    return resultado;
}
const std::map<Nodo*, int>& Nodo::getAdyacentesConPeso() const{
    return adyacentes;
}