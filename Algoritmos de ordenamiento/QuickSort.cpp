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

int main() {
    ifstream inputFile("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Random_sorted_sorted.txt"); // Asegúrate de que el archivo 'input.txt' está en el directorio correcto
    ofstream outputFile("Tiempos Registrados/Random_sorted_quick_time.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        return 1;
    }

    int n;
    while (inputFile >> n) {
        vector<int> array(n); // Pre-reserva el espacio para el vector
        
        for (int &num : array) {
            inputFile >> num; // Leer directamente en el vector pre-reservado
        }

        auto start = chrono::high_resolution_clock::now(); // Inicia el cronómetro

        quickSort(array, 0, n - 1); // Ordena el arreglo

        auto end = chrono::high_resolution_clock::now(); // Detiene el cronómetro
        chrono::duration<double, milli> elapsed = end - start; // Calcula el tiempo transcurrido

        outputFile << n << " " << elapsed.count() << endl; // Escribe el resultado en el archivo de salida
    }

    inputFile.close();
    outputFile.close();

    return 0;
}