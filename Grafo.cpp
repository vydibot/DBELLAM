#include "Grafo.hpp"
#include <queue>
#include <map>
#include <stack>
#include <limits>
#include <vector>
using namespace std;

/**
 * @brief Constructor por defecto
 * Inicializa un grafo vacío
 */
Grafo::Grafo(){}

/**
 * @brief Agrega un nuevo nodo al grafo
 * @param dato Valor entero que identifica al nodo
 * @return Puntero al nodo creado
 * 
 * Crea un nuevo nodo con el dato proporcionado y lo agrega
 * al vector de nodos del grafo.
 */
Nodo* Grafo::agregarNodo(int dato){
    Nodo* nodo = new Nodo(dato);
    nodos.push_back(nodo);
    return nodo;
}

/**
 * @brief Busca un nodo por su valor
 * @param dato Valor del nodo a buscar
 * @return Puntero al nodo encontrado o nullptr si no existe
 */
Nodo* Grafo::buscarNodo(int dato) const{
    for(Nodo* nodo : nodos){
        if (nodo->getDato() == dato){
            return nodo;
        }
    }
    return nullptr;
}

/**
 * @brief Conecta dos nodos con una arista ponderada
 * @param valor1 Valor del primer nodo
 * @param valor2 Valor del segundo nodo  
 * @param peso Peso de la arista (por defecto 1)
 * 
 * Crea una arista bidireccional entre los dos nodos.
 * Si algún nodo no existe, no se crea la conexión.
 */
void Grafo::conectar(int valor1, int valor2, int peso){
    Nodo* nodo1 = buscarNodo(valor1);
    Nodo* nodo2 = buscarNodo(valor2);
    if(nodo1 && nodo2){
        nodo1->agregarAdyacente(nodo2, peso);
        nodo2->agregarAdyacente(nodo1, peso);
    }
}

/**
 * @brief Alias para conectar - crea arista ponderada
 * @param valor1 Valor del primer nodo
 * @param valor2 Valor del segundo nodo
 * @param peso Peso de la arista
 */
void Grafo::agregarAristaPonderada(int valor1, int valor2, int peso) {
    conectar(valor1, valor2, peso);
}

/**
 * @brief Muestra el grafo por consola
 * 
 * Imprime cada nodo junto con sus adyacentes y el peso
 * de las aristas que los conectan.
 */
void Grafo::mostrarGrafo() const{
    cout << "=== Representacion del Grafo ===" << endl;
    for(Nodo* nodo : nodos){
        cout << "Nodo " << nodo->getDato() << " -> ";
        const map<Nodo*, int>& ady = nodo->getAdyacentesConPeso();
        for(const auto& par : ady){
            cout << par.first->getDato() << "(" << par.second << ") ";
        }
        cout << endl;
    }
}
/**
 * @brief Algoritmo de búsqueda en anchura (BFS)
 * @param valorInicial Nodo desde donde comenzar el recorrido
 * 
 * Explora el grafo nivel por nivel usando una cola.
 * Tiempo: O(V + E), Espacio: O(V)
 */
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

/**
 * @brief Algoritmo de búsqueda en profundidad (DFS)
 * @param valorInicial Nodo desde donde comenzar el recorrido
 * 
 * Explora el grafo en profundidad usando una pila.
 * Tiempo: O(V + E), Espacio: O(V)
 */
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

/**
 * @brief Algoritmo de Dijkstra para caminos mínimos
 * @param origen Nodo de origen para calcular distancias
 * 
 * Usa una cola de prioridad (min-heap) para encontrar
 * el camino más corto desde el origen a todos los demás nodos.
 * No funciona con pesos negativos.
 * Tiempo: O((V + E) log V), Espacio: O(V)
 */
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
    cout << "\n--- Algoritmo de Dijkstra ---" << endl;
    cout << "Desde el nodo " << origen << ":\n" << endl;
    for (auto& par : distancia) {
        int nodo = par.first;
        int dist = par.second;
        if (dist == numeric_limits<int>::max())
            cout << "Nodo " << nodo << " -> Inalcanzable" << endl;
        else
            cout << "Nodo " << nodo << " -> " << dist << endl;
    }
}

/**
 * @brief Algoritmo de Bellman-Ford para encontrar caminos mínimos
 * @param origen Nodo de origen para calcular distancias mínimas
 * 
 * Este algoritmo es similar a Dijkstra pero puede manejar pesos negativos.
 * Funciona relajando todas las aristas V-1 veces, donde V es el número de nodos.
 * También detecta ciclos negativos partiendo del origen.
 */
void Grafo::BellmanFord(int origen) const {
    // Paso 1: verificar nodo inicial
    Nodo* inicio = buscarNodo(origen);
    if (!inicio) {
        cout << "El nodo inicial no existe." << endl;
        return;
    }

    // Paso 2: estructuras auxiliares
    // distancia[u] = distancia mínima desde el origen hasta el nodo u
    map<int, int> distancia;
    // predecessor[u] = nodo anterior a u en el camino mínimo
    map<int, int> predecessor;

    // Paso 3: inicializar distancias
    // Todas las distancias se inicializan a infinito excepto el origen
    for (Nodo* n : nodos) {
        distancia[n->getDato()] = numeric_limits<int>::max();
        predecessor[n->getDato()] = -1;
    }
    distancia[origen] = 0;

    // Paso 4: relajación de aristas (V-1 veces)
    // En cada iteración, intentamos mejorar las distancias conocidas
    int V = nodos.size();
    for (int i = 1; i < V; i++) {
        // Recorrer todos los nodos del grafo
        for (Nodo* nodoActual : nodos) {
            int u = nodoActual->getDato();
            
            // Solo procesamos nodos con distancia conocida
            if (distancia[u] == numeric_limits<int>::max())
                continue;

            // Obtener todos los vecinos del nodo actual
            const map<Nodo*, int>& adyacentes = nodoActual->getAdyacentesConPeso();
            
            // Relajar cada arista
            for (const auto& par : adyacentes) {
                Nodo* vecino = par.first;
                int peso = par.second;
                int v = vecino->getDato();

                // Si hay un camino mejor a través de u, actualizar
                if (distancia[u] != numeric_limits<int>::max() && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecessor[v] = u;
                }
            }
        }
    }

    // Paso 5: detectar ciclos negativos
    // Una iteración adicional para verificar si hay ciclos negativos
    bool hayCicloNegativo = false;
    for (Nodo* nodoActual : nodos) {
        int u = nodoActual->getDato();
        if (distancia[u] == numeric_limits<int>::max())
            continue;

        const map<Nodo*, int>& adyacentes = nodoActual->getAdyacentesConPeso();
        for (const auto& par : adyacentes) {
            Nodo* vecino = par.first;
            int peso = par.second;
            int v = vecino->getDato();

            if (distancia[u] != numeric_limits<int>::max() &&
                distancia[u] + peso < distancia[v]) {
                hayCicloNegativo = true;
                break;
            }
        }
        if (hayCicloNegativo) break;
    }

    // Paso 6: mostrar resultados
    cout << "\nAlgoritmo de Bellman-Ford " << endl;
    cout << "Desde el nodo " << origen << ":\n" << endl;
    
    if (hayCicloNegativo) {
        cout << "Se detecto un ciclo de peso negativo!" << endl;
        cout << "Los resultados pueden no ser validos.\n" << endl;
    }

    // Mostrar distancias mínimas
    for (const auto& par : distancia) {
        int nodo = par.first;
        int dist = par.second;
        
        if (dist == numeric_limits<int>::max()) {
            cout << "Nodo " << nodo << " -> Inalcanzable" << endl;
        } else {
            cout << "Nodo " << nodo << " -> " << dist;
            
            // Reconstruir el camino
            if (predecessor[nodo] != -1) {
                cout << " (Camino: ";
                vector<int> camino;
                int actual = nodo;
                while (actual != -1) {
                    camino.push_back(actual);
                    actual = predecessor[actual];
                }
                // Invertir para mostrar desde origen
                for (int i = camino.size() - 1; i >= 0; i--) {
                    cout << camino[i];
                    if (i > 0) cout << " -> ";
                }
                cout << ")";
            }
            cout << endl;
        }
    }
}
