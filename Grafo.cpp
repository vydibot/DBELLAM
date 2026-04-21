#include "Grafo.hpp"
#include <queue>
#include <map>
#include <stack>
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
void Grafo::conectar(int valor1, int valor2){
    Nodo* nodo1=buscarNodo(valor1);
    Nodo* nodo2=buscarNodo(valor2);
    if(nodo1 && nodo2){
        nodo1->agregarAdyacente(nodo2);
        nodo2->agregarAdyacente(nodo1);
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
