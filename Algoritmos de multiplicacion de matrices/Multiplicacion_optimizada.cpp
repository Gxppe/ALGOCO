#include <bits/stdc++.h>
#include <chrono>  // Para medir el tiempo

using namespace std;

// Función para trasponer una matriz
vector<vector<int>> transponer(const vector<vector<int>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<int>> transpuesta(columnas, vector<int>(filas));

    // Transponer la matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            transpuesta[j][i] = matriz[i][j];
        }
    }

    return transpuesta;
}

// Función para multiplicar dos matrices (la segunda matriz ya debe estar transpuesta)
void mulMat(const vector<vector<int>>& matrizA, const vector<vector<int>>& matrizB, vector<vector<int>>& rslt) {
    int R1 = matrizA.size();       // Filas de la matriz A
    int C1 = matrizA[0].size();    // Columnas de la matriz A (debe coincidir con las filas originales de B antes de transponer)
    int R2 = matrizB.size();       // Filas de la matriz B (después de la transposición, son las columnas originales)
    int C2 = matrizB[0].size();    // Columnas de la matriz B (después de la transposición, son las filas originales)

    // Inicializar la matriz de resultado con ceros
    rslt.resize(R1, vector<int>(R2, 0));

    // Realizar la multiplicación de matrices con la matrizB ya transpuesta
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < R2; j++) {
            for (int k = 0; k < C1; k++) {
                rslt[i][j] += matrizA[i][k] * matrizB[j][k];  // Usamos B traspuesta, por lo que cambiamos los índices
            }
        }
    }
}

int main() {
    ifstream inputFileA("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_A.txt");  // Archivo de entrada para las matrices A
    ifstream inputFileB("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_B.txt");  // Archivo de entrada para las matrices B
    ofstream outputFile("Tiempos Registrados/Cuadradas_2_optimizado_time.txt");  // Archivo de salida para los tiempos

    // Verificar si los archivos se abrieron correctamente
    if (!inputFileA.is_open() || !inputFileB.is_open() || !outputFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        return 1;
    }

    int nA, mA, nB, mB;  // Dimensiones de las matrices
    while (inputFileA >> nA >> mA && inputFileB >> nB >> mB) {
        // Leer la matriz A
        vector<vector<int>> matrizA(nA, vector<int>(mA));
        for (int i = 0; i < nA; ++i) {
            for (int j = 0; j < mA; ++j) {
                inputFileA >> matrizA[i][j];
            }
        }

        // Leer la matriz B
        vector<vector<int>> matrizB(nB, vector<int>(mB));
        for (int i = 0; i < nB; ++i) {
            for (int j = 0; j < mB; ++j) {
                inputFileB >> matrizB[i][j];
            }
        }

        // Verificar si las matrices son multiplicables
        if (mA != nB) {
            cerr << "Error: las matrices no son multiplicables." << endl;
            continue;  // Saltar a la siguiente iteración si no son multiplicables
        }

        // Inicializar la matriz de resultado
        vector<vector<int>> resultado;

        // Medir el tiempo de la multiplicación
        auto start = chrono::high_resolution_clock::now();  // Iniciar el cronómetro
        mulMat(matrizA, matrizB, resultado);  // Multiplicar las matrices
        auto end = chrono::high_resolution_clock::now();  // Detener el cronómetro
        chrono::duration<double, milli> elapsed = end - start;  // Calcular el tiempo transcurrido

        // Calcular el área de la matriz resultante (filas * columnas)
        int area = nA * mB;

        // Guardar los resultados en el archivo de salida
        outputFile << area << " " << elapsed.count() << endl;
    }

    // Cerrar los archivos
    inputFileA.close();
    inputFileB.close();
    outputFile.close();

    return 0;
}
