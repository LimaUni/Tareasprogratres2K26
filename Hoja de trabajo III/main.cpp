//Nombre: Javier Lima
//Carne: 9941-22-9790
//Curso: Programacion III
//Semana VII - Hoja de trabajo III

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

void push(Nodo*& tope, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = tope;
    tope = nuevo;

    cout << "Elemento insertado correctamente\n";
}

void pop(Nodo*& tope) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
        return;
    }

    Nodo* aux = tope;
    cout << "Elemento eliminado: " << aux->dato << endl;
    tope = tope->siguiente;
    delete aux;
}

// Ver tope (peek)
void peek(Nodo* tope) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
    } else {
        cout << "Elemento en el tope (ultimo que entro): " << tope->dato << endl;
    }
}

void mostrar(Nodo* tope) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
        return;
    }

    Nodo* aux = tope;
    cout << "Elementos de la pila:\n";
    while (aux != NULL) {
        cout << aux->dato << endl;
        aux = aux->siguiente;
    }
}

int contarElementos(Nodo* tope) {
    int contador = 0;
    Nodo* aux = tope;

    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }

    return contador;
}

void buscarElemento(Nodo* tope, int valor) {
    if (tope == NULL) {
        cout << "La pila esta vacia\n";
        return;
    }

    Nodo* aux = tope;
    int posicion = 1;
    bool encontrado = false;

    while (aux != NULL) {
        if (aux->dato == valor) {
            cout << "Elemento encontrado en la posicion: " << posicion << endl;
            encontrado = true;
            break;
        }
        aux = aux->siguiente;
        posicion++;
    }

    if (!encontrado) {
        cout << "Elemento no encontrado\n";
    }
}

void vaciarPila(Nodo*& tope) {
    if (tope == NULL) {
        cout << "La pila ya esta vacia\n";
        return;
    }

    while (tope != NULL) {
        Nodo* aux = tope;
        tope = tope->siguiente;
        delete aux;
    }

    cout << "Pila vaciada correctamente\n";
}
int main() {
    Nodo* tope = NULL;
    int opcion, valor;

    do {
        cout << "\n----- MENU PILA -----";
        cout << "\n-Alumno: Javier Lima-\n\n";
        cout << "1. Insertar un elemento en la pila.\n";
        cout << "2. Eliminar el elemento del tope.\n";
        cout << "3. Mostrar el elemento en el tope.\n";
        cout << "4. Mostrar todos los elementos de la pila.\n";
        cout << "5. Contar cuantos elementos hay en la pila.\n";
        cout << "6. Buscar un valor dentro de la pila.\n";
        cout << "7. Vaciar completamente la pila.\n";
        cout << "8. Salir del programa.\n\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                push(tope, valor);
                break;

            case 2:
                pop(tope);
                break;

            case 3:
                peek(tope);
                break;

            case 4:
                mostrar(tope);
                break;

            case 5:
                cout << "Cantidad de elementos: " << contarElementos(tope) << endl;
                break;

            case 6:
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                buscarElemento(tope, valor);
                break;

            case 7:
                vaciarPila(tope);
                break;

            case 8:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 8);

    return 0;
}