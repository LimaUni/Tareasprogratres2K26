//Nombre: Javier Lima
//Carne: 9941-22-9790
//Curso: Programacion III
//Semana X - Examen Parcial 2 Practica

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct NodoDoble {
    int dato;
    string tipo;
    int orden;
    NodoDoble* sig;
    NodoDoble* ant;
};

struct Cola {
    Nodo* frente = NULL;
    Nodo* final = NULL;
};

struct NodoBST {
    int dato;
    NodoBST* izq;
    NodoBST* der;
};

Nodo* pila = NULL;
Cola cola;
Nodo* listaNegativos = NULL;
NodoDoble* historial = NULL;
NodoBST* arbol = NULL;

int orden = 0;

int pares = 0, impares = 0, negativos = 0, ceros = 0;
int mayor = -999999, menor = 999999;
int totalValidos = 0;

void push(int val) {
    Nodo* nuevo = new Nodo{val, pila};
    pila = nuevo;
}

void encolar(int val) {
    Nodo* nuevo = new Nodo{val, NULL};
    if (!cola.frente) cola.frente = cola.final = nuevo;
    else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
}

void insertarNegativo(int val) {
    Nodo* nuevo = new Nodo{val, listaNegativos};
    listaNegativos = nuevo;
}

void insertarHistorial(int val, string tipo) {
    NodoDoble* nuevo = new NodoDoble{val, tipo, ++orden, NULL, NULL};
    if (!historial) historial = nuevo;
    else {
        NodoDoble* temp = historial;
        while (temp->sig) temp = temp->sig;
        temp->sig = nuevo;
        nuevo->ant = temp;
    }
}

void mostrar(Nodo* lista) {
    if (!lista) {
        cout << "Vacia\n";
        return;
    }
    while (lista) {
        cout << lista->dato << " ";
        lista = lista->siguiente;
    }
    cout << endl;
}

void mostrarHistorial() {
    NodoDoble* temp = historial;
    while (temp) {
        cout << temp->orden << ") " << temp->dato << " -> " << temp->tipo << endl;
        temp = temp->sig;
    }
}

NodoBST* insertarBST(NodoBST* r, int val) {
    if (!r) return new NodoBST{val, NULL, NULL};
    if (val < r->dato) r->izq = insertarBST(r->izq, val);
    else r->der = insertarBST(r->der, val);
    return r;
}

void inOrden(NodoBST* r) {
    if (r) {
        inOrden(r->izq);
        cout << r->dato << " ";
        inOrden(r->der);
    }
}

void preOrden(NodoBST* r) {
    if (r) {
        cout << r->dato << " ";
        preOrden(r->izq);
        preOrden(r->der);
    }
}

void postOrden(NodoBST* r) {
    if (r) {
        postOrden(r->izq);
        postOrden(r->der);
        cout << r->dato << " ";
    }
}

void construirBST() {
    arbol = NULL;
    NodoDoble* temp = historial;

    while (temp) {
        if (temp->dato > 0) {
            arbol = insertarBST(arbol, temp->dato);
        }
        temp = temp->sig;
    }
}

bool buscarBST(NodoBST* r, int val) {
    if (!r) return false;
    if (r->dato == val) return true;
    if (val < r->dato) return buscarBST(r->izq, val);
    return buscarBST(r->der, val);
}

void eliminarNegativos() {
    Nodo* actual = listaNegativos;
    Nodo* anterior = NULL;
    int eliminados = 0;

    while (actual) {
        if (abs(actual->dato) < 10) {
            Nodo* borrar = actual;
            if (!anterior)
                listaNegativos = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            actual = actual->siguiente;
            delete borrar;
            eliminados++;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    cout << "Eliminados: " << eliminados << endl;
}

void estadisticas() {
    cout << "Pares: " << pares << endl;
    cout << "Impares: " << impares << endl;
    cout << "Negativos: " << negativos << endl;
    cout << "Ceros rechazados: " << ceros << endl;
    cout << "Total validos: " << totalValidos << endl;
    cout << "Mayor: " << mayor << endl;
    cout << "Menor: " << menor << endl;
}

void ingresar() {
    int n, val;
    cout << "Cantidad de datos a ingresar"
            ": ";
    cin >> n;

    if (n <= 0) return;

    for (int i = 0; i < n; i++) {
        cin >> val;

        if (val == 0) {
            ceros++;
            continue;
        }

        totalValidos++;

        if (val > mayor) mayor = val;
        if (val < menor) menor = val;

        if (val > 0 && val % 2 == 0) {
            encolar(val);
            pares++;
            insertarHistorial(val, "COLA");
        } else if (val > 0) {
            push(val);
            impares++;
            insertarHistorial(val, "PILA");
        } else {
            insertarNegativo(val);
            negativos++;
            insertarHistorial(val, "LISTA");
        }
    }
}

void reorganizar() {
    Nodo* aux1 = NULL;
    Nodo* aux2 = NULL;

    while (pila) {
        Nodo* temp = pila;
        pila = pila->siguiente;
        temp->siguiente = aux1;
        aux1 = temp;
    }

    while (cola.frente) {
        Nodo* temp = cola.frente;
        cola.frente = cola.frente->siguiente;
        temp->siguiente = aux2;
        aux2 = temp;
    }

    cout << "Lista desde pila:\n";
    mostrar(aux1);

    cout << "Lista desde cola:\n";
    mostrar(aux2);

    arbol = NULL;

    Nodo* t = aux1;
    while (t) {
        arbol = insertarBST(arbol, t->dato);
        t = t->siguiente;
    }

    t = aux2;
    while (t) {
        arbol = insertarBST(arbol, t->dato);
        t = t->siguiente;
    }
}

int main() {
    int op, val;

    do {
        cout <<"\n----- MENU -----\n";
        cout <<"---Jeremy Lima---\n\n";
        cout <<"1 - Ingresar datos\n";
        cout <<"2 - Ver pila\n";
        cout <<"3 - Ver cola\n";
        cout <<"4 - Ver negativos\n";
        cout <<"5 - Ver historial\n";
        cout <<"6 - Ver Arbol binario de busqueda (BST)\n";
        cout <<"7 - Eliminar Negativos\n";
        cout <<"8 - Buscar BST\n";
        cout <<"9 - Estadisticas\n";
        cout <<"10 - Reorganizar\n";
        cout <<"0 - Salir\n";
        cin >> op;

        switch (op) {
        case 1: ingresar(); break;
        case 2: mostrar(pila); break;
        case 3: mostrar(cola.frente); break;
        case 4: mostrar(listaNegativos); break;
        case 5: mostrarHistorial(); break;
        case 6:
            construirBST();
            cout << "InOrden: "; inOrden(arbol);
            cout << "\nPreOrden: "; preOrden(arbol);
            cout << "\nPostOrden: "; postOrden(arbol);
            cout << endl;
            break;
        case 7: eliminarNegativos(); break;
        case 8:
            cout << "Valor: "; cin >> val;
            cout << (buscarBST(arbol, val) ? "Encontrado\n" : "No encontrado\n");
            break;
        case 9: estadisticas(); break;
        case 10: reorganizar(); break;
        }

    } while (op != 0);

    return 0;
}