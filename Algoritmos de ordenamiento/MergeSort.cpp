// Función para fusionar dos subarreglos de array[].
// El primer subarreglo es array[left..mid]
// El segundo subarreglo es array[mid+1..right]
void merge(int array[], int const left, int const mid, int const right) {
    // Tamaños de los dos subarreglos que se van a fusionar
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    // Crear arreglos temporales
    auto *leftArray = new int[subArrayOne], *rightArray = new int[subArrayTwo];
 
    // Copiar datos a los arreglos temporales leftArray[] y rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    // Índices iniciales de los primeros y segundos subarreglos
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left; // Índice inicial del arreglo fusionado
 
    // Fusionar los arreglos temporales de nuevo en array[left..right]
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

    // Liberar la memoria asignada dinámicamente
    delete[] leftArray;
    delete[] rightArray;
}
 
// Función principal que implementa Merge Sort
// array[] es el arreglo a ordenar, begin es el índice izquierdo y end es el índice derecho
void mergeSort(int array[], int const begin, int const end) {
    if (begin >= end)
        return; // Condición base: Si el arreglo tiene un solo elemento o es inválido

    auto mid = begin + (end - begin) / 2; // Calcula el punto medio para dividir el arreglo
    mergeSort(array, begin, mid); // Ordena la primera mitad
    mergeSort(array, mid + 1, end); // Ordena la segunda mitad
    merge(array, begin, mid, end); // Fusiona las dos mitades ordenadas
}
