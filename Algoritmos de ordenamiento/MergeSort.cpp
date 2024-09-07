// Función para fusionar dos subarreglos de array[].
// El primer subarreglo es array[left..mid]
// El segundo subarreglo es array[mid+1..right]
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& array, int const left, int const mid, int const right) {
    // Tamaños de los dos subvectores que se van a fusionar
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Crear vectores temporales
    vector<int> leftArray(subArrayOne), rightArray(subArrayTwo);

    // Copiar datos a los vectores temporales leftArray y rightArray
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    // Índices iniciales de los primeros y segundos subvectores
    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left; // Índice inicial del vector fusionado

    // Fusionar los vectores temporales de nuevo en array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    // Copiar los elementos restantes de leftArray[], si los hay
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    // Copiar los elementos restantes de rightArray[], si los hay
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(vector<int>& array, int const begin, int const end) {
    if (begin >= end)
        return; // Condición base: Si el vector tiene un solo elemento o es inválido

    auto mid = begin + (end - begin) / 2; // Calcula el punto medio para dividir el vector
    mergeSort(array, begin, mid); // Ordena la primera mitad
    mergeSort(array, mid + 1, end); // Ordena la segunda mitad
    merge(array, begin, mid, end); // Fusiona las dos mitades ordenadas
}


int main() {
    ifstream inputFile("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Middle_sorted_sorted_70.txt"); // Asegúrate de que el archivo 'input.txt' está en el directorio correcto
    ofstream outputFile("Tiempos Registrados/Random_sorted_merge_time_70.txt");

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

        mergeSort(array, 0, n - 1); // Ordena el arreglo

        auto end = chrono::high_resolution_clock::now(); // Detiene el cronómetro
        chrono::duration<double, milli> elapsed = end - start; // Calcula el tiempo transcurrido

        outputFile << n << " " << elapsed.count() << endl; // Escribe el resultado en el archivo de salida
    }

    inputFile.close();
    outputFile.close();

    return 0;
}