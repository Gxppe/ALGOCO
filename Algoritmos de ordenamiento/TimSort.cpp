#include <bits/stdc++.h> 
using namespace std; 
const int RUN = 32; 

// Función de ordenación por inserción
void insertionSort(vector<int>& arr, int left, int right) { 
    for (int i = left + 1; i <= right; i++) { 
        int temp = arr[i]; 
        int j = i - 1; 
        while (j >= left && arr[j] > temp) { 
            arr[j + 1] = arr[j]; 
            j--; 
        } 
        arr[j + 1] = temp; 
    } 
} 

// Función de combinación (merge)
void merge(vector<int>& arr, int l, int m, int r) { 
    int len1 = m - l + 1, len2 = r - m; 
    vector<int> left(len1), right(len2); 
    
    for (int i = 0; i < len1; i++) 
        left[i] = arr[l + i]; 
    for (int i = 0; i < len2; i++) 
        right[i] = arr[m + 1 + i]; 

    int i = 0, j = 0, k = l; 
    while (i < len1 && j < len2) { 
        if (left[i] <= right[j]) { 
            arr[k] = left[i]; 
            i++; 
        } else { 
            arr[k] = right[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < len1) { 
        arr[k] = left[i]; 
        k++; 
        i++; 
    } 
    while (j < len2) { 
        arr[k] = right[j]; 
        k++; 
        j++; 
    } 
} 

// Función principal para implementar Timsort
void timSort(vector<int>& arr, int n) { 
    for (int i = 0; i < n; i += RUN) 
        insertionSort(arr, i, min((i + RUN - 1), (n - 1))); 

    for (int size = RUN; size < n; size = 2 * size) { 
        for (int left = 0; left < n; left += 2 * size) { 
            int mid = left + size - 1; 
            int right = min((left + 2 * size - 1), (n - 1)); 
            if (mid < right) 
                merge(arr, left, mid, right); 
        } 
    } 
} 


int main() {
    ifstream inputFile("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Middle_sorted_sorted_70.txt"); // Asegúrate de que el archivo 'input.txt' está en el directorio correcto
    ofstream outputFile("Tiempos Registrados/Middle_sorted_tim_time_70.txt");

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

        timSort(array, n); // Ordena el arreglo

        auto end = chrono::high_resolution_clock::now(); // Detiene el cronómetro
        chrono::duration<double, milli> elapsed = end - start; // Calcula el tiempo transcurrido

        outputFile << n << " " << elapsed.count() << endl; // Escribe el resultado en el archivo de salida
    }

    inputFile.close();
    outputFile.close();

    return 0;
}