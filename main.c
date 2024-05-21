#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_VERTICES 100

// Структура для представления графа
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Инициализация графа
void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

// Добавление ребра в граф
void addEdge(Graph* graph, int src, int dest) {
    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}

// Удаление вершины из графа
void removeVertex(Graph* graph, int vertex) {
    if (vertex >= graph->numVertices) {
        printf("Ошибка: Недопустимая вершина\n");
        exit(EXIT_FAILURE);
    }

    // Сдвигаем все вершины после удаляемой вершины на одну позицию влево
    for (int i = vertex; i < graph->numVertices - 1; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            graph->matrix[j][i] = graph->matrix[j][i + 1];
        }
    }

    // Сдвигаем все вершины после удаляемой вершины на одну позицию вверх
    for (int i = vertex; i < graph->numVertices - 1; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            graph->matrix[i][j] = graph->matrix[i + 1][j];
        }
    }

    // Уменьшаем количество вершин в графе
    graph->numVertices--;
}

// Получение степени вершины
int getDegree(Graph* graph, int vertex) {
    int degree = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->matrix[vertex][i] == 1) {
            degree++;
        }
    }
    return degree;
}

// Сортировка вершин по возрастанию степени
void sortVerticesByDegreeAsc(Graph* graph, int* sortedVertices) {
    // Инициализация массива отсортированных вершин
    for (int i = 0; i < graph->numVertices; i++) {
        sortedVertices[i] = i;
    }

    // Сортировка массива отсортированных вершин по возрастанию степени
    for (int i = 0; i < graph->numVertices - 1; i++) {
        for (int j = 0; j < graph->numVertices - i - 1; j++) {
            if (getDegree(graph, sortedVertices[j]) > getDegree(graph, sortedVertices[j + 1])) {
                int temp = sortedVertices[j];
                sortedVertices[j] = sortedVertices[j + 1];
                sortedVertices[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    printf("Введите количество ребер: ");
    int n = 0;
    scanf("%d", &n);
    Graph graph;
    initGraph(&graph, n);

    // Добавляем ребра в граф
    addEdge(&graph, 0, 2);
    for (int i = 1; i <= n; i++) {
        addEdge(&graph, i - 1, i);
    }


    printf("Исходный граф:\n");
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }
    printf("Какую вершину хотите удалить?\n ");
    int vertexToRemove = 0;
    scanf("%d", &vertexToRemove);
    removeVertex(&graph, vertexToRemove);

    printf("\nГраф после удаления вершины %d:\n", vertexToRemove);
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }

    // Получаем массив отсортированных вершин по возрастанию степени
    int sortedVertices[MAX_VERTICES];
    sortVerticesByDegreeAsc(&graph, sortedVertices);

    printf("\nВершины, отсортированные по возрастанию степени:\n");
    for (int i = 0; i < graph.numVertices; i++) {
        printf("%d ", sortedVertices[i]);
    }

    return 0;
}
