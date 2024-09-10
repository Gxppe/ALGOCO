import numpy as np
import random as rd

def generar_matriz(n):
    """Genera una matriz NxN con valores enteros entre 1 y 10"""
    return np.random.randint(1, 11, size=(n, n))

def guardar_matriz_en_archivo(nombre_archivo, matriz, dimensiones):
    """Guarda la matriz en el archivo especificado junto con las dimensiones"""
    with open(nombre_archivo, 'a') as f:
        f.write(f"{dimensiones[0]} {dimensiones[1]}\n")
        np.savetxt(f, matriz, fmt='%d')

def generar_y_guardar_matrices_potencia_dos(n, archivo_A, archivo_B):
    """Genera y guarda dos matrices cuadradas de dimensiones N x N con N siendo potencia de 2"""
    
    # Generar matrices cuadradas aleatorias de tamaño N x N
    matriz_A = generar_matriz(n)
    matriz_B = generar_matriz(n)
    
    # Guardar las matrices en los archivos respectivos
    guardar_matriz_en_archivo(archivo_A, matriz_A, (n, n))
    guardar_matriz_en_archivo(archivo_B, matriz_B, (n, n))

# Nombres de los archivos donde se guardarán las matrices
archivo_A = '/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_A.txt'
archivo_B = '/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Cuadradas_2_B.txt'

# Limpiar los archivos si ya existen
open(archivo_A, 'w').close()
open(archivo_B, 'w').close()

# Generar matrices con N siendo una potencia de 2 entre 2 y 256
for i in range(100):
    N = 2**rd.randint(1, 8)  # Genera N como una potencia de 2 (2^1 a 2^8)
    generar_y_guardar_matrices_potencia_dos(N, archivo_A, archivo_B)

print(f"Matrices cuadradas generadas y guardadas en {archivo_A} y {archivo_B}.")
