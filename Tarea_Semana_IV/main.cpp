#include <iostream>
#include <string>

using namespace std;

struct Producto {
    int codigo;
    string nombre;
    double precio;
};

struct Nodo {
    Producto datos;
    Nodo* siguiente;
};

int main() {

    cout << "Nombre: Jeremy Javier Lima Guitron" << endl << endl;

    Nodo* cabeza = nullptr;
    Nodo* nuevo = nullptr;
    Nodo* auxiliar = nullptr;

    for (int i = 0; i < 3; i++) {

        nuevo = new Nodo;

        cout << "Producto " << i + 1 << endl;
        cout << "Codigo: ";
        cin >> nuevo->datos.codigo;

        cin.ignore();

        cout << "Nombre: ";
        getline(cin, nuevo->datos.nombre);

        cout << "Precio: ";
        cin >> nuevo->datos.precio;

        nuevo->siguiente = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            auxiliar = cabeza;
            while (auxiliar->siguiente != nullptr) {
            }
            auxiliar->siguiente = nuevo;
        }

        cout << "--------------------" << endl;
    }

    auxiliar = cabeza;
    double total = 0;

    cout << endl << "Lista de productos:" << endl;

    while (auxiliar != nullptr) {
        cout << "Codigo: " << auxiliar->datos.codigo << endl;
        cout << "Nombre: " << auxiliar->datos.nombre << endl;
        cout << "Precio: Q" << auxiliar->datos.precio << endl;
        cout << "--------------------" << endl;

        total += auxiliar->datos.precio;
        auxiliar = auxiliar->siguiente;
    }

    cout << "Total acumulado: Q" << total << endl;

    while (cabeza != nullptr) {
        auxiliar = cabeza;
        cabeza = cabeza->siguiente;
        delete auxiliar;
    }

    return 0;
}