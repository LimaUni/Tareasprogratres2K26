#include <iostream>
using namespace std;

struct NodoAdyacente {
    int destino;
    NodoAdyacente* siguiente;
};

struct Vertice {
    int id;
    NodoAdyacente* lista;
};

struct NodoCola {
    int dato;
    NodoCola* siguiente;
};

class Cola {
private:
    NodoCola* frente;
    NodoCola* final;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    bool estaVacia() {
        return frente == nullptr;
    }

    void encolar(int valor) {
        NodoCola* nuevo = new NodoCola;
        nuevo->dato = valor;
        nuevo->siguiente = nullptr;

        if (final == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    int desencolar() {
        if (estaVacia()) {
            return -1;
        }

        NodoCola* temp = frente;
        int valor = temp->dato;

        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr;
        }

        delete temp;
        return valor;
    }
};

class Grafo {
private:
    Vertice* vertices;
    int cantidad;

public:
    Grafo(int n) {
        cantidad = n;
        vertices = new Vertice[n];

        for (int i = 0; i < n; i++) {
            vertices[i].id = i;
            vertices[i].lista = nullptr;
        }
    }

    void agregarArista(int origen, int destino) {
        NodoAdyacente* nuevo = new NodoAdyacente;
        nuevo->destino = destino;
        nuevo->siguiente = vertices[origen].lista;
        vertices[origen].lista = nuevo;

        NodoAdyacente* nuevo2 = new NodoAdyacente;
        nuevo2->destino = origen;
        nuevo2->siguiente = vertices[destino].lista;
        vertices[destino].lista = nuevo2;
    }

    void bfs(int inicio) {
        bool* visitado = new bool[cantidad];

        for (int i = 0; i < cantidad; i++) {
            visitado[i] = false;
        }

        Cola cola;
        visitado[inicio] = true;
        cola.encolar(inicio);

        cout << "BFS: ";

        while (!cola.estaVacia()) {
            int actual = cola.desencolar();
            cout << actual << " ";

            NodoAdyacente* aux = vertices[actual].lista;

            while (aux != nullptr) {
                int vecino = aux->destino;

                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    cola.encolar(vecino);
                }

                aux = aux->siguiente;
            }
        }

        delete[] visitado;
        cout << endl;
    }

    void dfs(int inicio) {
        bool* visitado = new bool[cantidad];

        for (int i = 0; i < cantidad; i++) {
            visitado[i] = false;
        }

        cout << "DFS: ";
        dfsRecursivo(inicio, visitado);
        cout << endl;

        delete[] visitado;
    }

    void dfsRecursivo(int actual, bool visitado[]) {
        visitado[actual] = true;
        cout << actual << " ";

        NodoAdyacente* aux = vertices[actual].lista;

        while (aux != nullptr) {
            int vecino = aux->destino;

            if (!visitado[vecino]) {
                dfsRecursivo(vecino, visitado);
            }

            aux = aux->siguiente;
        }
    }

    ~Grafo() {
        for (int i = 0; i < cantidad; i++) {
            NodoAdyacente* actual = vertices[i].lista;

            while (actual != nullptr) {
                NodoAdyacente* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }

        delete[] vertices;
    }
};

int main() {
    Grafo grafo(8);

    grafo.agregarArista(1, 2);
    grafo.agregarArista(1, 3);
    grafo.agregarArista(2, 5);
    grafo.agregarArista(3, 4);
    grafo.agregarArista(4, 6);
    grafo.agregarArista(5, 6);
    grafo.agregarArista(6, 7);

    grafo.bfs(1);
    grafo.dfs(1);

    return 0;
}