import numpy as np
import random as rd

def generar_matriz(n, m):
    """Genera una matriz aleatoria de NxM con valores enteros entre 1 y 10"""
    return np.random.randint(1, 11, size=(n, m))

def guardar_matriz_en_archivo(nombre_archivo, matriz, dimensiones):
    """Guarda la matriz en el archivo especificado junto con las dimensiones"""
    with open(nombre_archivo, 'a') as f:
        f.write(f"{dimensiones[0]} {dimensiones[1]}\n")
        np.savetxt(f, matriz, fmt='%d')

def generar_y_guardar_matrices(n, m, p, archivo_A, archivo_B):
    """Genera y guarda dos matrices que sean multiplicables"""
    
    # Generar matrices aleatorias
    matriz_A = generar_matriz(n, m)
    matriz_B = generar_matriz(m, p)
    
    # Guardar las matrices en los archivos respectivos
    guardar_matriz_en_archivo(archivo_A, matriz_A, (n, m))
    guardar_matriz_en_archivo(archivo_B, matriz_B, (m, p))

# Nombres de los archivos donde se guardarán las matrices
archivo_A = '/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Rectangular_A.txt'
archivo_B = '/home/gxuseppe/Tareasolol/ALGOCO/Datasets/Rectangular_B.txt'

# Limpiar los archivos si ya existen
open(archivo_A, 'w').close()
open(archivo_B, 'w').close()
for i in range(100):
    # Parámetros para las dimensiones de las matrices
    N = rd.randint(1,256) # Filas de la matriz A
    M = rd.randint(1,256) # Columnas de la matriz A y filas de la matriz B
    P = rd.randint(1,256)  # Columnas de la matriz B
    # Generar y guardar matrices
    generar_y_guardar_matrices(N, M, P, archivo_A, archivo_B)

print(f"Matrices generadas y guardadas en {archivo_A} y {archivo_B}.")
