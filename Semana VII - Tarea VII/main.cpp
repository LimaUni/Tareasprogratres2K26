//Nombre: Javier Lima
//Carne: 9941-22-9790
//Curso: Programacion III
//Semana VII - Tarea VII

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Pila {
    Nodo* tope = NULL;
};

void push(Pila &p, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = p.tope;
    p.tope = nuevo;
}

void pop(Pila &p) {
    if (p.tope == NULL) {
        cout << "Pila vacia\n";
        return;
    }
    Nodo* temp = p.tope;
    p.tope = p.tope->siguiente;
    delete temp;
}

int peekPila(Pila p) {
    if (p.tope == NULL) {
        cout << "Pila vacia\n";
        return -1;
    }
    return p.tope->dato;
}

void mostrarPila(Pila p) {
    Nodo* aux = p.tope;
    cout << "Pila (impares): ";
    while (aux != NULL) {
        cout << aux->dato << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL\n";
}

struct Cola {
    Nodo* frente = NULL;
    Nodo* final = NULL;
};

void enqueue(Cola &c, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (c.final == NULL) {
        c.frente = c.final = nuevo;
    } else {
        c.final->siguiente = nuevo;
        c.final = nuevo;
    }
}

void dequeue(Cola &c) {
    if (c.frente == NULL) {
        cout << "Cola vacia\n";
        return;
    }
    Nodo* temp = c.frente;
    c.frente = c.frente->siguiente;

    if (c.frente == NULL)
        c.final = NULL;

    delete temp;
}

int peekCola(Cola c) {
    if (c.frente == NULL) {
        cout << "Cola vacia\n";
        return -1;
    }
    return c.frente->dato;
}

void mostrarCola(Cola c) {
    Nodo* aux = c.frente;
    cout << "Cola (pares): ";
    while (aux != NULL) {
        cout << aux->dato << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL\n";
}

struct Lista {
    Nodo* cabeza = NULL;
};

void insertarLista(Lista &l, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = l.cabeza;
    l.cabeza = nuevo;
}

void mostrarLista(Lista l) {
    Nodo* aux = l.cabeza;
    cout << "Lista (negativos): ";
    while (aux != NULL) {
        cout << aux->dato << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL\n";
}

void liberarLista(Nodo* &nodo) {
    while (nodo != NULL) {
        Nodo* temp = nodo;
        nodo = nodo->siguiente;
        delete temp;
    }
}

int main() {
    Pila pila;
    Cola cola;
    Lista lista;

    int opcion, numero;
    int pares = 0, impares = 0;

    do {
        cout << "\n-------MENU-------\n";
        cout << "----Jeremy Lima----\n";
        cout << "--------------------\n";
        cout << "1. Ingresar numero\n";
        cout << "2. Mostrar pila\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Mostrar lista\n";
        cout << "5. Eliminar de pila\n";
        cout << "6. Eliminar de cola\n";
        cout << "7. Mostrar estadisticas\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida\n";
            continue;
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese numero (-1 para terminar): ";
                cin >> numero;

                if (numero == -1) break;

                if (numero < 0) {
                    insertarLista(lista, numero);
                } else if (numero % 2 == 0) {
                    enqueue(cola, numero);
                    pares++;
                } else {
                    push(pila, numero);
                    impares++;
                }
                break;

            case 2:
                mostrarPila(pila);
                break;

            case 3:
                mostrarCola(cola);
                break;

            case 4:
                mostrarLista(lista);
                break;

            case 5:
                pop(pila);
                break;

            case 6:
                dequeue(cola);
                break;

            case 7:
                cout << "Pares: " << pares << endl;
                cout << "Impares: " << impares << endl;
                break;

            case 8:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 8);

    liberarLista(pila.tope);
    liberarLista(cola.frente);
    liberarLista(lista.cabeza);

    return 0;
}
