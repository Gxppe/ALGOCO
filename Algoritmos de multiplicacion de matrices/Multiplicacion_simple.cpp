#include <bits/stdc++.h>
using namespace std;

void mulMat(vector<vector<int>> matrizA, vector<vector<int>> matrizB)
{
    int R1 = matrizA.size();
    int C1 = matrizA[0].size();
    int R2 = matrizB.size();
    int C2 = matrizB[0].size();

    // Inicializar la matriz de resultado con ceros
    vector<vector<int>> rslt(R1, vector<int>(C2, 0));
    
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            for (int k = 0; k < R2; k++) {
                rslt[i][j] += matrizA[i][k] * matrizB[k][j];
            }
            cout << rslt[i][j] << "\t";
        }
        cout << endl;
    }
}
