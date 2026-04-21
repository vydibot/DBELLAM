#include "Grafo.hpp"
#include <queue>
#include <map>
#include <stack>
#include <limits>
#include <vector>
using namespace std;
Grafo::Grafo(){}
Nodo* Grafo :: agregarNodo(int dato){
    Nodo* nodo=new Nodo(dato);
    nodos.push_back(nodo);
    return nodo;
}
Nodo* Grafo::buscarNodo(int dato) const{
    for(Nodo* nodo: nodos){
        if (nodo->getDato()==dato){
            return nodo;
        }
    }
    return nullptr;
}
void Grafo::conectar(int valor1, int valor2, int peso){
    Nodo* nodo1=buscarNodo(valor1);
    Nodo* nodo2=buscarNodo(valor2);
    if(nodo1 && nodo2){
        nodo1->agregarAdyacente(nodo2, peso);
        nodo2->agregarAdyacente(nodo1, peso);
    }
}
void Grafo::mostrarGrafo() const{
    for(Nodo* nodo: nodos){
        cout<< "Nodo: "<< nodo->getDato() << " Adyacentes: ";
        for(Nodo* adyacente: nodo->getAdyacentes()){
            cout<< adyacente->getDato() << " ";
        }
        cout<< endl;
    }
}
void Grafo::BFS(int valorInicial){
    Nodo* nodoInicial  = buscarNodo(valorInicial);
    if (!nodoInicial){
        cout<< "Nodo no encontrado "<< endl;
        return;
    }
    queue<Nodo*> cola;
    map<int, bool> visitado;
    cola.push(nodoInicial);
    visitado[nodoInicial->getDato()] = true;
    cout<< "Recorrido BFS: desde el nodo " << valorInicial << endl;
    while (!cola.empty()){
        Nodo* actual = cola.front();
        cola.pop();
        cout<< actual->getDato() << " ";
        for (Nodo* adyacente: actual->getAdyacentes()){
            int v=adyacente->getDato();
            if (!visitado[v]){
                cola.push(adyacente);
                visitado[v] = true;
            }
        }
    }
}

void Grafo::DFS(int valorInicial){
    Nodo* nodoInicial = buscarNodo(valorInicial);
    if (!nodoInicial){
        cout << "Nodo no encontrado " << endl;
        return;
    }

    stack<Nodo*> pila;
    map<int, bool> visitado;

    pila.push(nodoInicial);
    cout << "Recorrido DFS: desde el nodo " << valorInicial << endl;

    while (!pila.empty()){
        Nodo* actual = pila.top();
        pila.pop();

        int datoActual = actual->getDato();
        if (visitado[datoActual]){
            continue;
        }

        visitado[datoActual] = true;
        cout << datoActual << " ";

        const vector<Nodo*>& adyacentes = actual->getAdyacentes();
        for (auto it = adyacentes.rbegin(); it != adyacentes.rend(); ++it){
            int v = (*it)->getDato();
            if (!visitado[v]){
                pila.push(*it);
            }
        }
    }
}

void Grafo::Dijkstra(int origen) const {
    // Paso 1: verificar nodo inicial
    Nodo* inicio = buscarNodo(origen);
    if (!inicio) {
        cout << "El nodo inicial no existe." << endl;
        return;
    }

    // Paso 2: estructuras auxiliares
    map<int, int> distancia;
    map<int, bool> visitado;

    // Paso 3: inicializar distancias
    for (Nodo* n : nodos)
        distancia[n->getDato()] = numeric_limits<int>::max();
    distancia[origen] = 0;

    // Paso 4: cola de prioridad (min-heap)
    using P = pair<int, Nodo*>;  // (distancia, nodo)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, inicio});

    // Paso 5: ciclo principal
    while (!pq.empty()) {
        auto [distActual, nodoActual] = pq.top();
        pq.pop();

        int u = nodoActual->getDato();
        if (visitado[u]) continue;
        visitado[u] = true;

        // Recorrer vecinos con sus pesos
        const map<Nodo*, int>& adyacentes = nodoActual->getAdyacentesConPeso();
        for (auto& par : adyacentes) {
            Nodo* vecino = par.first;
            int peso = par.second;
            int v = vecino->getDato();
            int nuevaDist = distActual + peso;

            if (nuevaDist < distancia[v]) {
                distancia[v] = nuevaDist;
                pq.push({nuevaDist, vecino});
            }
        }
    }

    // Paso 6: mostrar resultado
    cout << "\nDistancias minimas desde el nodo " << origen << ":\n";
    for (auto& par : distancia) {
        int nodo = par.first;
        int dist = par.second;
        if (dist == numeric_limits<int>::max())
            cout << nodo << " -> Inalcanzable" << endl;
        else
            cout << nodo << " -> " << dist << endl;
    }
}
