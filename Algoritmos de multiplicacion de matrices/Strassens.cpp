#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;  // Para medir tiempos
typedef long long lld;  // Definir 'lld' como alias de 'long long' para manejar números grandes


// Función auxiliar que realiza la multiplicación tradicional de matrices
inline lld **MatrixMultiply(lld **a, lld **b, int n, int l, int m) {
    // Crear la matriz de resultado de tamaño n x m
    lld **c = new lld *[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];  // Reservar espacio para las filas de la matriz de resultado

    // Realizar la multiplicación de matrices tradicional (n x l) * (l x m) = (n x m)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = 0;  // Inicializar cada elemento en 0
            for (int k = 0; k < l; k++) {
                // Sumar el producto de los elementos correspondientes de a y b
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;  // Retornar la matriz de resultado
}

// Función principal que implementa el algoritmo de Strassen para multiplicar matrices
inline lld **Strassen(lld **a, lld **b, int n, int l, int m) {
    // Caso base: si cualquiera de las dimensiones es 1, realizar la multiplicación tradicional
    if (n == 1 || l == 1 || m == 1)
        return MatrixMultiply(a, b, n, l, m);  // Utilizar la multiplicación directa

    // Crear la matriz de resultado de tamaño n x m
    lld **c = new lld *[n];
    for (int i = 0; i < n; i++)
        c[i] = new lld[m];  // Reservar espacio para la matriz de resultado

    // Calcular las dimensiones ajustadas para dividir las matrices en submatrices
    int adjN = (n >> 1) + (n & 1);  // Ajustar n al dividir entre 2
    int adjL = (l >> 1) + (l & 1);  // Ajustar l al dividir entre 2
    int adjM = (m >> 1) + (m & 1);  // Ajustar m al dividir entre 2

    // Dividir la matriz A en 4 submatrices As[2][2]
    lld ****As = new lld ***[2];  // As[2][2] será una matriz de 4 submatrices
    for (int x = 0; x < 2; x++) {
        As[x] = new lld **[2];
        for (int y = 0; y < 2; y++) {
            As[x][y] = new lld *[adjN];  // Reservar espacio para las filas de cada submatriz
            for (int i = 0; i < adjN; i++) {
                As[x][y][i] = new lld[adjL];  // Reservar espacio para las columnas
                for (int j = 0; j < adjL; j++) {
                    // Llenar las submatrices, asegurándose de manejar los índices fuera de rango
                    int I = i + (x & 1) * adjN;
                    int J = j + (y & 1) * adjL;
                    As[x][y][i][j] = (I < n && J < l) ? a[I][J] : 0;  // Evitar acceso fuera de la matriz
                }
            }
        }
    }

    // Dividir la matriz B en 4 submatrices Bs[2][2]
    lld ****Bs = new lld ***[2];  // Bs[2][2] será una matriz de 4 submatrices
    for (int x = 0; x < 2; x++) {
        Bs[x] = new lld **[2];
        for (int y = 0; y < 2; y++) {
            Bs[x][y] = new lld *[adjL];  // Reservar espacio para las filas de cada submatriz
            for (int i = 0; i < adjL; i++) {
                Bs[x][y][i] = new lld[adjM];  // Reservar espacio para las columnas
                for (int j = 0; j < adjM; j++) {
                    // Llenar las submatrices, asegurándose de manejar los índices fuera de rango
                    int I = i + (x & 1) * adjL;
                    int J = j + (y & 1) * adjM;
                    Bs[x][y][i][j] = (I < l && J < m) ? b[I][J] : 0;  // Evitar acceso fuera de la matriz
                }
            }
        }
    }

    // Calcular las matrices intermedias 's' necesarias para la multiplicación de Strassen
    lld ***s = new lld **[10];  // 10 matrices intermedias que almacenan resultados temporales
    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
            // s0 = B12 - B22
            s[i] = new lld *[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][1][j][k] - Bs[1][1][j][k];  // Restar los elementos de las submatrices B
                }
            }
            break;
        case 1:
            // s1 = A11 + A12
            s[i] = new lld *[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[0][1][j][k];  // Sumar los elementos de las submatrices A
                }
            }
            break;
        case 2:
            // s2 = A21 + A22
            s[i] = new lld *[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[1][0][j][k] + As[1][1][j][k];  // Sumar los elementos de las submatrices A
                }
            }
            break;
        case 3:
            // s3 = B21 - B11
            s[i] = new lld *[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] - Bs[0][0][j][k];  // Restar los elementos de las submatrices B
                }
            }
            break;
        case 4:
            // s4 = A11 + A22
            s[i] = new lld *[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] + As[1][1][j][k];  // Sumar los elementos de las submatrices A
                }
            }
            break;
        case 5:
            // s5 = B11 + B22
            s[i] = new lld *[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[1][1][j][k];  // Sumar los elementos de las submatrices B
                }
            }
            break;
        case 6:
            // s6 = A12 - A22
            s[i] = new lld *[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][1][j][k] - As[1][1][j][k];  // Restar los elementos de las submatrices A
                }
            }
            break;
        case 7:
            // s7 = B21 + B22
            s[i] = new lld *[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[1][0][j][k] + Bs[1][1][j][k];  // Sumar los elementos de las submatrices B
                }
            }
            break;
        case 8:
            // s8 = A11 - A21
            s[i] = new lld *[adjN];
            for (int j = 0; j < adjN; j++) {
                s[i][j] = new lld[adjL];
                for (int k = 0; k < adjL; k++) {
                    s[i][j][k] = As[0][0][j][k] - As[1][0][j][k];  // Restar los elementos de las submatrices A
                }
            }
            break;
        case 9:
            // s9 = B11 + B12
            s[i] = new lld *[adjL];
            for (int j = 0; j < adjL; j++) {
                s[i][j] = new lld[adjM];
                for (int k = 0; k < adjM; k++) {
                    s[i][j][k] = Bs[0][0][j][k] + Bs[0][1][j][k];  // Sumar los elementos de las submatrices B
                }
            }
            break;
        }
    }

    // Recursivamente aplicar Strassen a las submatrices y matrices intermedias 's'
    lld ***p = new lld **[7];
    p[0] = Strassen(As[0][0], s[0], adjN, adjL, adjM);  // Calcular P1
    p[1] = Strassen(s[1], Bs[1][1], adjN, adjL, adjM);  // Calcular P2
    p[2] = Strassen(s[2], Bs[0][0], adjN, adjL, adjM);  // Calcular P3
    p[3] = Strassen(As[1][1], s[3], adjN, adjL, adjM);  // Calcular P4
    p[4] = Strassen(s[4], s[5], adjN, adjL, adjM);      // Calcular P5
    p[5] = Strassen(s[6], s[7], adjN, adjL, adjM);      // Calcular P6
    p[6] = Strassen(s[8], s[9], adjN, adjL, adjM);      // Calcular P7

    // Reconstruir la matriz resultado combinando las submatrices P1...P7
    for (int i = 0; i < adjN; i++) {
        for (int j = 0; j < adjM; j++) {
            c[i][j] = p[4][i][j] + p[3][i][j] - p[1][i][j] + p[5][i][j];  // Elementos superiores izquierdos
            if (j + adjM < m)
                c[i][j + adjM] = p[0][i][j] + p[1][i][j];  // Elementos superiores derechos
            if (i + adjN < n)
                c[i + adjN][j] = p[2][i][j] + p[3][i][j];  // Elementos inferiores izquierdos
            if (i + adjN < n && j + adjM < m)
                c[i + adjN][j + adjM] = p[4][i][j] + p[0][i][j] - p[2][i][j] - p[6][i][j];  // Elementos inferiores derechos
        }
    }

    // Liberar la memoria utilizada para las submatrices As y Bs
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjN; i++) {
                delete[] As[x][y][i];
            }
            delete[] As[x][y];
        }
        delete[] As[x];
    }
    delete[] As;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int i = 0; i < adjL; i++) {
                delete[] Bs[x][y][i];
            }
            delete[] Bs[x][y];
        }
        delete[] Bs[x];
    }
    delete[] Bs;

    // Liberar la memoria utilizada para las matrices intermedias 's'
    for (int i = 0; i < 10; i++) {
        switch (i) {
        case 0:
        case 3:
        case 5:
        case 7:
        case 9:
            for (int j = 0; j < adjL; j++) {
                delete[] s[i][j];
            }
            break;
        case 1:
        case 2:
        case 4:
        case 6:
        case 8:
            for (int j = 0; j < adjN; j++) {
                delete[] s[i][j];
            }
            break;
        }
        delete[] s[i];
    }
    delete[] s;

    // Liberar la memoria utilizada para las matrices P1...P7
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (n >> 1); j++) {
            delete[] p[i][j];
        }
        delete[] p[i];
    }
    delete[] p;

    return c;  // Retornar la matriz resultado
}


lld** leer_matriz(ifstream &archivo, int &n, int &m) {
    archivo >> n >> m;
    lld **matriz = new lld*[n];
    for (int i = 0; i < n; ++i) {
        matriz[i] = new lld[m];
        for (int j = 0; j < m; ++j) {
            archivo >> matriz[i][j];
        }
    }
    return matriz;
}

int main() {
    ifstream inputFileA("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_A.txt");  // Archivo de entrada para las matrices A
    ifstream inputFileB("/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_B.txt");  // Archivo de entrada para las matrices B
    ofstream outputFile("Tiempos Registrados/Cuadradas_2_strassens_time.txt");  // Archivo de salida para los tiempos

    if (!inputFileA.is_open() || !inputFileB.is_open() || !outputFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        return 1;
    }

    int nA, mA, nB, mB;

    for (int matrixCount = 0; matrixCount < 100; ++matrixCount) {
        // Leer la matriz A
        lld **matrizA = leer_matriz(inputFileA, nA, mA);
        
        // Leer la matriz B
        lld **matrizB = leer_matriz(inputFileB, nB, mB);

        // Validar si las matrices pueden multiplicarse
        if (mA != nB) {
            cerr << "Error: las matrices no son multiplicables." << endl;
            continue;  // Saltar este par de matrices y continuar con el siguiente
        }

        // Medir el tiempo de multiplicación utilizando Strassen
        auto start = high_resolution_clock::now();
        lld **resultado = Strassen(matrizA, matrizB, nA, mA, mB);  // Multiplicar usando Strassen
        auto end = high_resolution_clock::now();

        // Calcular tiempo transcurrido en milisegundos
        chrono::duration<double, milli> elapsed = end - start;

        // Calcular el área de la matriz resultante
        int area = nA * mB;

        // Guardar los resultados en el archivo de salida en el formato: "área tiempo"
        outputFile << area << " " << elapsed.count() << endl;

        // Liberar memoria de las matrices
        for (int i = 0; i < nA; ++i) delete[] matrizA[i];
        delete[] matrizA;

        for (int i = 0; i < nB; ++i) delete[] matrizB[i];
        delete[] matrizB;

        for (int i = 0; i < nA; ++i) delete[] resultado[i];
        delete[] resultado;
    }

    inputFileA.close();
    inputFileB.close();
    outputFile.close();

    return 0;
}