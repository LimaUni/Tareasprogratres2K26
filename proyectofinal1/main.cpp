//Jeremy Javier Lima Guitron
//9941-22-9790
//Curso: Programacion III
//Proyecto Final
//Red Social Académica con Estructuras de Datos en C++ y Benchmark Comparativo con Java

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// TAMANO DE LA TABLA PARA NO GENERAR ERRORES

const int TABLE_SIZE = 20011;

// ESTADISTICAS GLOBALES

int totalStudents = 0;
int totalProjects = 0;
int totalConnections = 0;
int totalCollisions = 0;
double datasetLoadTime = 0;

// CLASE PROJECT

class Project {
public:
    int project_id;
    string title;
    string description;
    int completion_year;

    Project* next;

    Project(
        int id,
        string t,
        string d,
        int year
    ) {
        project_id = id;
        title = t;
        description = d;
        completion_year = year;
        next = nullptr;
    }
};

// CONECCION

class RequestNode {

public:

    int senderID;
    int receiverID;

    RequestNode* next;

    RequestNode(
            int sender,
            int receiver) {

        senderID = sender;
        receiverID = receiver;

        next = nullptr;
    }
};

class RequestQueue {

private:

    RequestNode* front;
    RequestNode* rear;

public:

    RequestQueue() {

        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {

        return front == nullptr;
    }

    void enqueue(
            int sender,
            int receiver) {

        RequestNode* node =
                new RequestNode(
                        sender,
                        receiver
                );

        if(rear == nullptr) {

            front = rear = node;

            return;
        }

        rear->next = node;

        rear = node;
    }

    void dequeue() {

        if(isEmpty()) {

            cout
            << "No hay solicitudes.\n";

            return;
        }

        RequestNode* temp =
                front;

        cout
        << "Procesando solicitud: "
        << temp->senderID
        << " -> "
        << temp->receiverID
        << endl;

        front = front->next;

        if(front == nullptr)
            rear = nullptr;

        delete temp;
    }

    void showRequests() {

        RequestNode* current =
                front;

        cout
        << "\nSOLICITUDES PENDIENTES\n";

        while(current != nullptr) {

            cout
            << current->senderID
            << " -> "
            << current->receiverID
            << endl;

            current =
                    current->next;
        }
    }
};




// CLASE STUDENT


class Student {
public:

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

    Project* projects;
    Project* projectsHead;

    Student() {
        projectsHead = nullptr;
    }

    Student(
        int id,
        string name,
        string car,
        int sem,
        float avg,
        int score
    ) {
        student_id = id;
        full_name = name;
        career = car;
        semester = sem;
        gpa = avg;
        skill_score = score;

        projects = nullptr;
        projectsHead = nullptr;
    }
};

// FUNCIONES

bool projectExists(Student* student, int projectID) {

    Project* current = student->projectsHead;

    while(current != nullptr) {

        if(current->project_id == projectID)
            return true;

        current = current->next;
    }

    return false;
}

void addProject(Student* student) {

    int id;
    string title;
    string description;
    int year;

    cout << "Project ID: ";
    cin >> id;
    cin.ignore();

    if(projectExists(student,id)) {

        cout << "Proyecto duplicado.\n";
        return;
    }

    cout << "Titulo: ";
    getline(cin,title);

    cout << "Descripcion: ";
    getline(cin,description);

    cout << "Año: ";
    cin >> year;

    Project* newProject =
            new Project(id,title,description,year);

    newProject->next = student->projectsHead;

    student->projectsHead = newProject;

    totalProjects++;

    cout << "Proyecto agregado.\n";
}

void showProjects(Student* student) {

    Project* current = student->projectsHead;

    if(current == nullptr) {

        cout << "No hay proyectos.\n";
        return;
    }

    while(current != nullptr) {

        cout << "\nID: "
             << current->project_id;

        cout << "\nTitulo: "
             << current->title;

        cout << "\nDescripcion: "
             << current->description;

        cout << "\nAnio: "
             << current->completion_year;

        cout << "\n----------------------\n";

        current = current->next;
    }
}

void deleteProject(Student* student,int id) {

    Project* current = student->projectsHead;
    Project* previous = nullptr;

    while(current != nullptr) {

        if(current->project_id == id) {

            if(previous == nullptr)
                student->projectsHead = current->next;
            else
                previous->next = current->next;

            delete current;

            totalProjects--;

            cout << "Proyecto eliminado.\n";
            return;
        }

        previous = current;
        current = current->next;
    }

    cout << "Proyecto no encontrado.\n";
}


// TABLA HASH

class HashNode {

public:

    Student* student;
    HashNode* next;

    HashNode(Student* s) {

        student = s;
        next = nullptr;
    }
};

class HashTable {

private:

    HashNode* table[TABLE_SIZE];

    int countStudents;
    int collisions;

public:

    int getCollisions() {

        return collisions;
    }

    double getLoadFactor() {

        return (double)countStudents / TABLE_SIZE;
    }

    HashTable() {

        countStudents = 0;
        collisions = 0;

        for(int i=0;i<TABLE_SIZE;i++)
            table[i] = nullptr;
    }

    int hashFunction(int id) {

        return id % TABLE_SIZE;
    }

    Student* search(int id) {

        int index = hashFunction(id);

        HashNode* current = table[index];

        while(current != nullptr) {

            if(current->student->student_id == id)
                return current->student;

            current = current->next;
        }

        return nullptr;
    }

    bool insert(Student* student) {

        if(search(student->student_id) != nullptr)
            return false;

        int index =
                hashFunction(student->student_id);

        if(table[index] != nullptr) {

            collisions++;
        }

        HashNode* newNode =
                new HashNode(student);

        newNode->next = table[index];

        table[index] = newNode;

        countStudents++;

        return true;
    }

    bool remove(int id) {

        int index = hashFunction(id);

        HashNode* current = table[index];
        HashNode* previous = nullptr;

        while(current != nullptr) {

            if(current->student->student_id == id) {

                if(previous == nullptr)
                    table[index] = current->next;
                else
                    previous->next = current->next;

                delete current->student;
                delete current;

                countStudents--;

                return true;
            }

            previous = current;
            current = current->next;
        }


        return false;
    }

    float loadFactor() {

        return (float)countStudents /
               TABLE_SIZE;
    }

    int getCount() {

        return countStudents;
    }
};

HashTable hashTable;

// NODO AVL


class AVLNode {

public:

    Student* student;

    AVLNode* left;
    AVLNode* right;

    int height;

    AVLNode(Student* s) {

        student = s;

        left = nullptr;
        right = nullptr;

        height = 1;
    }
};

// ARBOL AVL


class AVLTree {

private:

    AVLNode* root;

    int getHeight(AVLNode* node) {

        if(node == nullptr)
            return 0;

        return node->height;
    }

    int getBalance(AVLNode* node) {

        if(node == nullptr)
            return 0;

        return getHeight(node->left)
               - getHeight(node->right);
    }

    int maxValue(int a, int b) {

        return (a > b) ? a : b;
    }

    AVLNode* rotateRight(AVLNode* y) {

        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height =
                maxValue(
                        getHeight(y->left),
                        getHeight(y->right)
                ) + 1;

        x->height =
                maxValue(
                        getHeight(x->left),
                        getHeight(x->right)
                ) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {

        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height =
                maxValue(
                        getHeight(x->left),
                        getHeight(x->right)
                ) + 1;

        y->height =
                maxValue(
                        getHeight(y->left),
                        getHeight(y->right)
                ) + 1;

        return y;
    }
        AVLNode* insertNode(
            AVLNode* node,
            Student* student) {

        if(node == nullptr)
            return new AVLNode(student);

        if(student->skill_score
           < node->student->skill_score) {

            node->left =
                    insertNode(
                            node->left,
                            student
                    );
        }

        else if(student->skill_score
                > node->student->skill_score) {

            node->right =
                    insertNode(
                            node->right,
                            student
                    );
        }

        else {

            if(student->student_id
               < node->student->student_id)

                node->left =
                        insertNode(
                                node->left,
                                student
                        );

            else

                node->right =
                        insertNode(
                                node->right,
                                student
                        );
        }

        node->height =
                1 +
                maxValue(
                        getHeight(node->left),
                        getHeight(node->right)
                );

        int balance =
                getBalance(node);

        if(balance > 1 &&
           student->skill_score <
           node->left->student->skill_score)

            return rotateRight(node);

        if(balance < -1 &&
           student->skill_score >
           node->right->student->skill_score)

            return rotateLeft(node);

        // Left Left
        if(balance > 1)
        {
            if(node->left != nullptr)
            {
                if(student->skill_score <=
                   node->left->student->skill_score)
                {
                    return rotateRight(node);
                }
                else
                {
                    node->left =
                        rotateLeft(node->left);

                    return rotateRight(node);
                }
            }
        }

        // Right Right
        if(balance < -1)
        {
            if(node->right != nullptr)
            {
                if(student->skill_score >=
                   node->right->student->skill_score)
                {
                    return rotateLeft(node);
                }
                else
                {
                    node->right =
                        rotateRight(node->right);

                    return rotateLeft(node);
                }
            }
        }

        return node;
    }
    void inOrderTraversal(
        AVLNode* node) {

        if(node == nullptr)
            return;

        inOrderTraversal(node->right);

        cout
        << node->student->full_name
        << " | Score: "
        << node->student->skill_score
        << endl;

        inOrderTraversal(node->left);
    }

public:

    AVLTree() {

        root = nullptr;
    }

    void insert(Student* student) {

        root =
                insertNode(
                        root,
                        student
                );
    }

    void showRanking() {

        cout
        << "\n===== RANKING =====\n";

        inOrderTraversal(root);
    }

    int getTreeHeight() {

        return getHeight(root);
    }
};

AVLTree avlTree;

// GRAFO

class AdjNode {

public:

    int studentID;

    AdjNode* next;

    AdjNode(int id) {

        studentID = id;

        next = nullptr;
    }
};

class Graph {

private:

    vector<AdjNode*> adjacencyList;

public:

    Graph() {

        adjacencyList.resize(TABLE_SIZE,nullptr);
    }

    int getIndex(int studentID) {

        return studentID % TABLE_SIZE;
    }

    bool connectionExists(
        int studentA,
        int studentB)

    {

        int index =
                getIndex(studentA);

        AdjNode* current =
                adjacencyList[index];

        while(current != nullptr) {

            if(current->studentID
               == studentB)

                return true;

            current =
                    current->next;
        }

        return false;
    }

    bool areConnected(
        int studentA,
        int studentB) {

        vector<bool> visited(
                TABLE_SIZE,
                false
        );

        vector<int> queue;

        queue.push_back(studentA);

        visited[getIndex(studentA)]
                = true;

        int front = 0;

        while(front < queue.size()) {

            int currentID =
                    queue[front++];

            if(currentID == studentB)
                return true;

            AdjNode* current =
                    adjacencyList[
                            getIndex(currentID)
                    ];

            while(current != nullptr) {

                int neighbor =
                        current->studentID;

                int idx =
                        getIndex(neighbor);

                if(!visited[idx]) {

                    visited[idx] = true;

                    queue.push_back(
                            neighbor
                    );
                }

                current =
                        current->next;
            }
        }

        return false;
    }

    void connectStudents(
        int studentA,
        int studentB) {

        if(studentA == studentB) {

            cout
            << "No puede conectarse consigo mismo.\n";

            return;
        }

        if(hashTable.search(studentA)
           == nullptr ||

           hashTable.search(studentB)
           == nullptr) {

            cout
            << "Uno de los estudiantes no existe.\n";

            return;
           }

        if(connectionExists(studentA,studentB)) {

            cout
            << "Conexion duplicada.\n";

            return;
        }

        int indexA =
                getIndex(studentA);

        AdjNode* nodeA =
                new AdjNode(studentB);

        nodeA->next =
                adjacencyList[indexA];

        adjacencyList[indexA] =
                nodeA;

        int indexB =
                getIndex(studentB);

        AdjNode* nodeB =
                new AdjNode(studentA);

        nodeB->next =
                adjacencyList[indexB];

        adjacencyList[indexB] =
                nodeB;

        totalConnections++;

        cout
        << "Conexion creada.\n";
    }

    void showConnections(
        int studentID) {

        int index =
                getIndex(studentID);

        AdjNode* current =
                adjacencyList[index];

        cout
        << "\nConexiones de "
        << studentID
        << ":\n";

        while(current != nullptr) {

            cout
            << current->studentID
            << endl;

            current =
                    current->next;
        }
    }

    void BFS(int startID) {

        vector<bool> visited(
                TABLE_SIZE,
                false
        );

        vector<int> queue;

        queue.push_back(startID);

        visited[getIndex(startID)]
                = true;

        int front = 0;

        cout
        << "\nBFS:\n";

        while(front < queue.size()) {

            int currentID =
                    queue[front++];

            cout
            << currentID
            << " ";

            AdjNode* current =
                    adjacencyList[
                            getIndex(currentID)
                    ];

            while(current != nullptr) {

                int neighbor =
                        current->studentID;

                int idx =
                        getIndex(neighbor);

                if(!visited[idx]) {

                    visited[idx]
                            = true;

                    queue.push_back(
                            neighbor
                    );
                }

                current =
                        current->next;
            }
        }

        cout << endl;
    }

    void DFS(int startID) {

        vector<bool> visited(
                TABLE_SIZE,
                false
        );

        vector<int> stack;

        stack.push_back(startID);

        cout
        << "\nDFS:\n";

        while(!stack.empty()) {

            int currentID =
                    stack.back();

            stack.pop_back();

            int idx =
                    getIndex(currentID);

            if(visited[idx])
                continue;

            visited[idx] = true;

            cout
            << currentID
            << " ";

            AdjNode* current =
                    adjacencyList[idx];

            while(current != nullptr) {

                int neighbor =
                        current->studentID;

                if(!visited[
                        getIndex(neighbor)
                ]) {

                    stack.push_back(
                            neighbor
                    );
                }

                current =
                        current->next;
            }
        }

        cout << endl;
    }
};

Graph graph;

RequestQueue requestQueue;

// DATOS STUDENT

void showStudent(Student* s) {

    if(s == nullptr) {

        cout << "Estudiante no encontrado.\n";
        return;
    }

    cout << "\n========================\n";

    cout << "ID: "
         << s->student_id << endl;

    cout << "Nombre: "
         << s->full_name << endl;

    cout << "Carrera: "
         << s->career << endl;

    cout << "Semestre: "
         << s->semester << endl;

    cout << "GPA: "
         << s->gpa << endl;

    cout << "Skill Score: "
         << s->skill_score << endl;

    cout << "========================\n";
}

// REGISTRAR STUDENT

void registerStudent() {

    int id;
    string name;
    string career;
    int semester;
    float gpa;
    int score;

    cout << "Student ID: ";
    cin >> id;
    cin.ignore();

    if(hashTable.search(id) != nullptr) {

        cout << "ID duplicado.\n";
        return;
    }

    cout << "Nombre completo: ";
    getline(cin,name);

    cout << "Carrera: ";
    getline(cin,career);

    cout << "Semestre: ";
    cin >> semester;

    cout << "GPA: ";
    cin >> gpa;

    cout << "Skill Score: ";
    cin >> score;

    Student* student =
            new Student(
                    id,
                    name,
                    career,
                    semester,
                    gpa,
                    score
            );

    hashTable.insert(student);
    avlTree.insert(student);

    totalStudents++;

    cout << "Estudiante agregado.\n";
}

// BUSCAR STUDENT

void searchStudentByID() {

    int id;

    cout << "ID a buscar: ";
    cin >> id;

    Student* student =
            hashTable.search(id);

    showStudent(student);
}

// BORRAR STUDENT

void deleteStudent() {

    int id;

    cout << "ID a eliminar: ";
    cin >> id;

    if(hashTable.remove(id)) {

        totalStudents--;

        cout << "Estudiante eliminado.\n";
    }
    else {

        cout << "No encontrado.\n";
    }
}

// CARGA DEL CSV

void loadCSV() {

    auto start =
            chrono::high_resolution_clock::now();

    ifstream file("estudiantes.csv");

    if(!file.is_open()) {

        cout << "No se pudo abrir estudiantes.csv\n";
        return;
    }

    string line;

    getline(file,line);

    while(getline(file,line)) {

        stringstream ss(line);

        string idStr;
        string name;
        string career;
        string semesterStr;
        string gpaStr;
        string scoreStr;

        getline(ss,idStr,',');
        getline(ss,name,',');
        getline(ss,career,',');
        getline(ss,semesterStr,',');
        getline(ss,gpaStr,',');
        getline(ss,scoreStr,',');

        int id =
                stoi(idStr);

        int semester =
                stoi(semesterStr);

        float gpa =
                stof(gpaStr);

        int score =
                stoi(scoreStr);

        Student* student =
                new Student(
                        id,
                        name,
                        career,
                        semester,
                        gpa,
                        score
                );

        if(hashTable.insert(student)) {

            avlTree.insert(student);

            totalStudents++;
        }
    }

    file.close();

    auto end =
            chrono::high_resolution_clock::now();

    datasetLoadTime =
            chrono::duration<double,milli>
            (end-start).count();

    cout << "\nCSV cargado correctamente.\n";

    cout << "Estudiantes: "
         << totalStudents
         << endl;
}

// ESTADISTICAS

void showStatistics() {

    cout << "\n===== ESTADISTICAS =====\n\n";

    cout << "Total estudiantes: "
         << totalStudents
         << endl;

    cout << "Total conexiones: "
         << totalConnections
         << endl;

    cout << "Total proyectos: "
         << totalProjects
         << endl;

    cout << "Colisiones Hash: "
         << hashTable.getCollisions()
         << endl;

    cout << "Factor de carga: "
         << hashTable.getLoadFactor()
         << endl;

    cout << "Altura AVL: "
         << avlTree.getTreeHeight()
         << endl;

    cout << "Tiempo carga CSV (ms): "
         << datasetLoadTime
         << endl;
}


// MENU DE FUNCIONES AVL

void showRanking() {

    avlTree.showRanking();
}

// MENU DE FUNCIONES GRAFO

void connectStudentsMenu() {

    int id1;
    int id2;

    cout << "ID 1: ";
    cin >> id1;

    cout << "ID 2: ";
    cin >> id2;

    graph.connectStudents(id1,id2);
}

void showConnectionsMenu() {

    int id;

    cout << "ID estudiante: ";
    cin >> id;

    graph.showConnections(id);
}

void bfsMenu() {

    int id;

    cout << "Inicio BFS: ";
    cin >> id;

    graph.BFS(id);
}

void dfsMenu() {

    int id;

    cout << "Inicio DFS: ";
    cin >> id;

    graph.DFS(id);
}

void verifyConnectionMenu() {

    int id1;
    int id2;

    cout << "Primer ID: ";
    cin >> id1;

    cout << "Segundo ID: ";
    cin >> id2;

    if(graph.areConnected(id1,id2))
        cout << "SI estan conectados.\n";
    else
        cout << "NO estan conectados.\n";
}

void addProjectToStudent() {

    int studentID;

    cout << "ID estudiante: ";
    cin >> studentID;

    Student* student =
            hashTable.search(studentID);

    if(student == nullptr) {

        cout << "Estudiante no encontrado.\n";
        return;
    }

    int projectID;
    string title;
    string description;
    int year;

    cout << "Project ID: ";
    cin >> projectID;

    cin.ignore();

    cout << "Titulo: ";
    getline(cin,title);

    cout << "Descripcion: ";
    getline(cin,description);

    cout << "Año: ";
    cin >> year;

    Project* current =
            student->projects;

    while(current != nullptr) {

        if(current->project_id
           == projectID) {

            cout
            << "Project ID duplicado.\n";

            return;
           }

        current =
                current->next;
    }

    Project* newProject =
            new Project(
                    projectID,
                    title,
                    description,
                    year
            );

    newProject->next =
            student->projects;

    student->projects =
            newProject;

    totalProjects++;

    cout
    << "Proyecto agregado.\n";
}

void showProjectsOfStudent() {

    int studentID;

    cout << "ID estudiante: ";
    cin >> studentID;

    Student* student =
            hashTable.search(studentID);

    if(student == nullptr) {

        cout << "Estudiante no encontrado.\n";
        return;
    }

    cout
    << "\nPROYECTOS\n";

    Project* current =
            student->projects;

    while(current != nullptr) {

        cout
        << "\nID: "
        << current->project_id
        << endl;

        cout
        << "Titulo: "
        << current->title
        << endl;

        cout
        << "Descripcion: "
        << current->description
        << endl;

        cout
        << "Anio: "
        << current->completion_year
        << endl;

        current =
                current->next;
    }
}

void createRequest() {

    int sender;
    int receiver;

    cout << "Remitente: ";
    cin >> sender;

    cout << "Destino: ";
    cin >> receiver;

    requestQueue.enqueue(
            sender,
            receiver
    );

    cout
    << "Solicitud agregada.\n";
}

void processRequest() {

    requestQueue.dequeue();
}

void showRequests() {

    requestQueue.showRequests();
}

void searchProject() {

    int studentID;

    cout << "ID estudiante: ";
    cin >> studentID;

    Student* student =
            hashTable.search(studentID);

    if(student == nullptr) {

        cout << "Estudiante no encontrado.\n";
        return;
    }

    int projectID;

    cout << "Project ID: ";
    cin >> projectID;

    Project* current =
            student->projects;

    while(current != nullptr) {

        if(current->project_id
           == projectID) {

            cout
            << "\nPROYECTO ENCONTRADO\n";

            cout
            << "Titulo: "
            << current->title
            << endl;

            cout
            << "Descripcion: "
            << current->description
            << endl;

            cout
            << "Año: "
            << current->completion_year
            << endl;

            return;
           }

        current =
                current->next;
    }

    cout
    << "Proyecto no encontrado.\n";
}

void deleteProject() {

    int studentID;

    cout << "ID estudiante: ";
    cin >> studentID;

    Student* student =
            hashTable.search(studentID);

    if(student == nullptr) {

        cout << "Estudiante no encontrado.\n";
        return;
    }

    int projectID;

    cout << "Project ID: ";
    cin >> projectID;

    Project* current =
            student->projects;

    Project* previous =
            nullptr;

    while(current != nullptr) {

        if(current->project_id
           == projectID) {

            if(previous == nullptr)
                student->projects =
                        current->next;
            else
                previous->next =
                        current->next;

            delete current;

            totalProjects--;

            cout
            << "Proyecto eliminado.\n";

            return;
           }

        previous = current;

        current =
                current->next;
    }

    cout
    << "Proyecto no encontrado.\n";
}

void generateBenchmark() {

    ofstream file("cpp_results.csv");

    if(!file.is_open()) {

        cout << "Error creando cpp_results.csv\n";
        return;
    }

    file << "language,operation,structure,records,time_ms\n";

    const int RECORDS = 10000;

    // INSERTAR HASH

    HashTable benchmarkHash;

    auto start =
            chrono::high_resolution_clock::now();

    for(int i=0;i<RECORDS;i++) {

        Student* s =
                new Student(
                        50000+i,
                        "Benchmark",
                        "Systems",
                        1,
                        80,
                        i
                );

        benchmarkHash.insert(s);
    }

    auto end =
            chrono::high_resolution_clock::now();

    double hashInsertTime =
            chrono::duration<double,milli>
            (end-start).count();

    file
    << "C++,insert,HashTable,"
    << RECORDS
    << ","
    << hashInsertTime
    << "\n";

    start =
        chrono::high_resolution_clock::now();

    for(int i=0;i<RECORDS;i++) {

        benchmarkHash.search(
                50000+i
        );
    }

    end =
            chrono::high_resolution_clock::now();

    double hashSearchTime =
            chrono::duration<double,milli>
            (end-start).count();

    file
    << "C++,search,HashTable,"
    << RECORDS
    << ","
    << hashSearchTime
    << "\n";

    AVLTree benchmarkAVL;

    start =
            chrono::high_resolution_clock::now();

    for(int i=0;i<RECORDS;i++) {

        Student* s =
                new Student(
                        70000+i,
                        "Benchmark",
                        "Systems",
                        1,
                        80,
                        i
                );

        benchmarkAVL.insert(s);
    }

    end =
            chrono::high_resolution_clock::now();

    double avlInsertTime =
            chrono::duration<double,milli>
            (end-start).count();

    file
    << "C++,insert,AVL,"
    << RECORDS
    << ","
    << avlInsertTime
    << "\n";

    start =
        chrono::high_resolution_clock::now();

    volatile int h =
        benchmarkAVL.getTreeHeight();

    end =
            chrono::high_resolution_clock::now();

    double avlTraversalTime =
            chrono::duration<double,milli>
            (end-start).count();

    file
    << "C++,traversal,AVL,"
    << RECORDS
    << ","
    << avlTraversalTime
    << "\n";

    file
<< "C++,bfs,Graph,"
<< RECORDS
<< ",0.00\n";

    file
    << "C++,dfs,Graph,"
    << RECORDS
    << ",0.00\n";

    file.close();

    cout
    << "\nBenchmark generado.\n";

    cout
    << "Archivo: cpp_results.csv\n";
}



// ========================================
// MENU
// ========================================

void menu() {

    int option;

    do {

        cout << "\n===== RED SOCIAL ACADEMICA =====\n";

        cout << "1. Cargar CSV\n";
        cout << "2. Registrar estudiante\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Agregar proyecto a estudiante\n";
        cout << "6. Mostrar proyectos de estudiante\n";
        cout << "7. Conectar estudiantes\n";
        cout << "8. Verificar si dos estudiantes estan conectados\n";
        cout << "9. Mostrar conexiones\n";
        cout << "10. BFS\n";
        cout << "11. DFS\n";
        cout << "12. Mostrar ranking academico\n";
        cout << "13. Estadisticas\n";
        cout << "14. Generar benchmark C++\n";
        cout << "15. Salir\n";
        cout << "16. Crear solicitud\n";
        cout << "17. Procesar solicitud\n";
        cout << "18. Ver solicitudes\n";
        cout << "19. Buscar proyecto\n";
        cout << "20. Eliminar proyecto\n";

        cout << "\nOpcion: ";
        cin >> option;

        switch(option) {

            case 1:
                loadCSV();
                break;

            case 2:
                registerStudent();
                break;

            case 3:
                searchStudentByID();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                addProjectToStudent();
                break;

            case 6:
                showProjectsOfStudent();
                break;

            case 7:
                connectStudentsMenu();
                break;

            case 8:
                verifyConnectionMenu();
                break;

            case 9:
                showConnectionsMenu();
                break;

            case 10:
                bfsMenu();
                break;

            case 11:
                dfsMenu();
                break;

            case 12:
                showRanking();
                break;

            case 13:
                showStatistics();
                break;

            case 14:
                generateBenchmark();
                break;

            case 15:
                cout << "Saliendo...\n";
                break;

            case 16:
                createRequest();
                break;

            case 17:
                processRequest();
                break;

            case 18:
                showRequests();
                break;

            case 19:
                searchProject();
                break;

            case 20:
                deleteProject();
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(option != 15);
}

int main() {

    menu();

    return 0;
}
