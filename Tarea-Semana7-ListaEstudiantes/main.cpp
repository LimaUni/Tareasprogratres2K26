//Nombre: Javier Lima
//Carne: 9941-22-9790
//Curso: Programacion III
//Semana VII - Tarea V

#include <iostream>
#include <string>

using namespace std;
struct Nodo {
    int carne;
    string nombre;
    string apellido;
    string carrera;
    Nodo* siguiente;
};
Nodo* head = NULL;

void insertarInicio() {
    Nodo* nuevo = new Nodo;

    cout << "Ingrese carne: ";
    cin >> nuevo->carne;
    cin.ignore();

    cout << "Ingrese nombre: ";
    getline(cin, nuevo->nombre);

    cout << "Ingrese apellido: ";
    getline(cin, nuevo->apellido);

    cout << "Ingrese carrera: ";
    getline(cin, nuevo->carrera);

    nuevo->siguiente = head;
    head = nuevo;

    cout << "Estudiante agregado al inicio.\n";
}

void insertarFinal() {
    Nodo* nuevo = new Nodo;

    cout << "Ingrese carne: ";
    cin >> nuevo->carne;
    cin.ignore();

    cout << "Ingrese nombre: ";
    getline(cin, nuevo->nombre);

    cout << "Ingrese apellido: ";
    getline(cin, nuevo->apellido);

    cout << "Ingrese carrera: ";
    getline(cin, nuevo->carrera);

    nuevo->siguiente = NULL;

    if (head == NULL) {
        head = nuevo;
    } else {
        Nodo* temp = head;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    cout << "Estudiante agregado al final.\n";
}

void mostrar() {
    Nodo* temp = head;

    if (temp == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    while (temp != NULL) {
        cout << "Carne: " << temp->carne << endl;
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Apellido: " << temp->apellido << endl;
        cout << "Carrera: " << temp->carrera << endl;
        cout << "-----------------------------\n";

        temp = temp->siguiente;
    }
}

void buscar() {
    int carne;
    cout << "Ingrese carne a buscar: ";
    cin >> carne;

    Nodo* temp = head;

    while (temp != NULL) {
        if (temp->carne == carne) {
            cout << "\nEstudiante encontrado:\n";
            cout << "Nombre: " << temp->nombre << endl;
            cout << "Apellido: " << temp->apellido << endl;
            cout << "Carrera: " << temp->carrera << endl;
            return;
        }
        temp = temp->siguiente;
    }

    cout << "Estudiante no encontrado.\n";
}

void eliminar() {
    int carne;
    cout << "Ingrese carne a eliminar: ";
    cin >> carne;

    Nodo* temp = head;
    Nodo* anterior = NULL;

    if (temp != NULL && temp->carne == carne) {
        head = temp->siguiente;
        delete temp;
        cout << "Estudiante eliminado.\n";
        return;
    }

    while (temp != NULL && temp->carne != carne) {
        anterior = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL) {
        cout << "Estudiante no encontrado.\n";
        return;
    }

    anterior->siguiente = temp->siguiente;
    delete temp;

    cout << "Estudiante eliminado.\n";
}

int main() {
    int opcion;

    do {
        cout << "\n------- MENU -------";
        cout << "\n-Alumno: Javier Lima-\n\n";
        cout << "1. Insertar estudiante al inicio\n";
        cout << "2. Insertar estudiante al final\n";
        cout << "3. Mostrar estudiantes\n";
        cout << "4. Buscar estudiante\n";
        cout << "5. Eliminar estudiante\n";
        cout << "6. Salir\n\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertarInicio();
                break;
            case 2:
                insertarFinal();
                break;
            case 3:
                mostrar();
                break;
            case 4:
                buscar();
                break;
            case 5:
                eliminar();
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}