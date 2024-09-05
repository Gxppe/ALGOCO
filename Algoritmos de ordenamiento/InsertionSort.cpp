// Insertion Sort en C++
// Función para ordenar un arreglo usando Insertion Sort
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void insertionSort(vector<int>& arr) {
    // Itera sobre cada elemento del arreglo comenzando desde el segundo
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i]; // Elemento a ser insertado en la sublista ordenada
        int j = i - 1; // Último índice de la sublista ordenada

        // Mueve los elementos de arr[0..i-1] que son mayores que la clave
        // a una posición adelante de su posición actual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Mueve el elemento un lugar adelante
            j = j - 1; // Decrementa el índice para comparar con el siguiente elemento hacia atrás
        }
        arr[j + 1] = key; // Inserta la clave en la posición correcta
    }
}



int main() {
    ifstream inputFile("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Middle_sorted_sorted.txt"); // Asegúrate de que el archivo 'input.txt' está en el directorio correcto
    ofstream outputFile("Tiempos Registrados/Middle_sorted_insertion_time.txt");

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

        insertionSort(array); // Ordena el arreglo

        auto end = chrono::high_resolution_clock::now(); // Detiene el cronómetro
        chrono::duration<double, milli> elapsed = end - start; // Calcula el tiempo transcurrido

        outputFile << n << " " << elapsed.count() << endl; // Escribe el resultado en el archivo de salida
    }

    inputFile.close();
    outputFile.close();

    return 0;
}