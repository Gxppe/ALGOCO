// Insertion Sort en C++
// Función para ordenar un arreglo usando Insertion Sort
void insertionSort(int arr[], int n) {
    // Itera sobre cada elemento del arreglo comenzando desde el segundo
    for (int i = 1; i < n; ++i) {
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
