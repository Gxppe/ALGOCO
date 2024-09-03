#include <bits/stdc++.h>
using namespace std;

// Función para realizar la partición del arreglo para Quick Sort
int partition(vector<int> &vec, int low, int high) {
    // Seleccionando el último elemento como pivote
    int pivot = vec[high];

    // Índice del elemento más pequeño encontrado
    int i = (low - 1); 

    // Recorre desde el primer elemento hasta el penúltimo
    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (vec[j] <= pivot) {
            i++; // Incrementa el índice de los elementos más pequeños
            swap(vec[i], vec[j]); // Intercambia los elementos vec[i] y vec[j]
        }
    }

    // Coloca el pivote en su posición correcta
    swap(vec[i + 1], vec[high]);

    // Devuelve el índice de partición
    return (i + 1);
}

// Función principal para implementar Quick Sort
void quickSort(vector<int> &vec, int low, int high) {
    // Caso base: mientras el índice inicial sea menor que el índice final
    if (low < high) {
        // p es el índice de partición; vec[p] está en su lugar correcto
        int p = partition(vec, low, high);

        // Ordena recursivamente los elementos antes y después del índice de partición
        quickSort(vec, low, p - 1);
        quickSort(vec, p + 1, high);
    }
}
