## Resumen del Código

El sistema fue desarrollado utilizando Programación Orientada a Objetos en C++ y está compuesto por varias estructuras de datos implementadas manualmente para cumplir con los requisitos del proyecto.

La clase `Student` representa a cada estudiante de la red académica y almacena información como ID, nombre, carrera, semestre, promedio académico y puntaje de habilidades. Además, cada estudiante posee una lista enlazada de proyectos académicos.

La búsqueda rápida de estudiantes se realiza mediante una Tabla Hash con resolución de colisiones por encadenamiento separado (Separate Chaining). Esta estructura permite insertar, buscar y eliminar estudiantes utilizando su identificador único.

El ranking académico se administra mediante un Árbol AVL, el cual mantiene los estudiantes ordenados según su `skill_score` y garantiza un rendimiento eficiente gracias a su balanceo automático.

Las relaciones entre estudiantes se representan mediante un Grafo no dirigido. Esta estructura permite conectar estudiantes, verificar conexiones y realizar recorridos BFS (Breadth First Search) y DFS (Depth First Search).

Para la gestión de proyectos se implementó una Lista Enlazada, permitiendo agregar, buscar, mostrar y eliminar proyectos asociados a cada estudiante.

El sistema también incorpora un módulo de benchmark que mide el tiempo de ejecución de las principales operaciones sobre las estructuras implementadas en C++. Los resultados se almacenan automáticamente en un archivo CSV para su posterior análisis y comparación con las estructuras nativas de Java.

Finalmente, el programa incluye un menú interactivo que permite al usuario acceder a todas las funcionalidades del sistema, administrar la información académica y visualizar estadísticas relacionadas con las estructuras de datos utilizadas.
