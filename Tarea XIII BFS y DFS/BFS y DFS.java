import java.util.*;

public class Grafo {
    private Map<Integer, List<Integer>> grafo;

    public Grafo() {
        grafo = new HashMap<>();
    }

    public void agregarArista(int origen, int destino) {
        grafo.putIfAbsent(origen, new ArrayList<>());
        grafo.putIfAbsent(destino, new ArrayList<>());

        grafo.get(origen).add(destino);
        grafo.get(destino).add(origen);
    }

    public void bfs(int inicio) {
        Set<Integer> visitado = new HashSet<>();
        Queue<Integer> cola = new LinkedList<>();

        visitado.add(inicio);
        cola.add(inicio);

        System.out.print("BFS: ");

        while (!cola.isEmpty()) {
            int actual = cola.poll();
            System.out.print(actual + " ");

            for (int vecino : grafo.get(actual)) {
                if (!visitado.contains(vecino)) {
                    visitado.add(vecino);
                    cola.add(vecino);
                }
            }
        }

        System.out.println();
    }

    public void dfs(int inicio) {
        Set<Integer> visitado = new HashSet<>();

        System.out.print("DFS: ");
        dfsRecursivo(inicio, visitado);
        System.out.println();
    }

    private void dfsRecursivo(int actual, Set<Integer> visitado) {
        visitado.add(actual);
        System.out.print(actual + " ");

        for (int vecino : grafo.get(actual)) {
            if (!visitado.contains(vecino)) {
                dfsRecursivo(vecino, visitado);
            }
        }
    }

    public static void main(String[] args) {
        Grafo grafo = new Grafo();

        grafo.agregarArista(1, 2);
        grafo.agregarArista(1, 3);
        grafo.agregarArista(2, 5);
        grafo.agregarArista(3, 4);
        grafo.agregarArista(4, 6);
        grafo.agregarArista(5, 6);
        grafo.agregarArista(6, 7);

        grafo.bfs(1);
        grafo.dfs(1);
    }
}
