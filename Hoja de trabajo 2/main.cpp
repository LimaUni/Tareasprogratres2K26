//Nombre: Javier Lima
//Carne: 9941-22-9790
//Curso: Programacion III
//Semana IV - Hoja de trabajo 2

#include <iostream>
using namespace std;

struct producto {
    int codigo;
    string nombre;
    double precio;
};

struct Nodo {
    producto data;
    Nodo* siguiente;
};
int main() {
    Nodo* primero = new Nodo;
    primero->data.codigo = 101;
    primero->data.nombre = "Laptop";
    primero->data.precio = 5500.50;
    primero->siguiente = nullptr;

    Nodo* segundo = new Nodo;
    segundo->data.codigo = 102;
    segundo->data.nombre = "Mouse";
    segundo->data.precio = 150.75;
    segundo->siguiente = nullptr;

    primero->siguiente = segundo;

    Nodo* tercero = new Nodo;
    tercero->data.codigo = 103;
    tercero->data.nombre = "Teclado";
    tercero->data.precio = 300.00;
    tercero->siguiente = nullptr;

    segundo->siguiente = tercero;

    cout << "Nombre: Jeremy Javier Lima Guitron" << endl;

    Nodo* actual = primero;
    while (actual != nullptr) {
        cout << " Codigo: " << actual->data.codigo
             << " Nombre: " << actual->data.nombre
             << " Precio: Q" << actual->data.precio << endl;

        actual = actual->siguiente;
    }
    actual = primero;

    while (actual != nullptr) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    primero = nullptr;

    return 0;
}

