#include "Nodo.hpp"

Nodo::Nodo(int dato) {
    this->dato = dato;
}
int Nodo::getDato()const{
    return dato;
}
void Nodo::agregarAdyacente(Nodo*nodo){
    adyacentes.push_back(nodo);
}
const std::vector<Nodo*>& Nodo::getAdyacentes() const{
    return adyacentes;
}