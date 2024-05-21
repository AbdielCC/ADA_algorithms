/*
 * @autor Cabello Cardenas Ulises Abdiel
 * @version 1.0
 * Este programa ordena los elementos de una lista :)
 */
#include <stdio.h>

/**
 * Combina dos subarreglos de arr[].
 * El primer subarreglo es arr[l..m]
 * El segundo subarreglo es arr[m+1..r]
 * @param arr El arreglo que se va a ordenar
 * @param l   Índice izquierdo del primer subarreglo
 * @param m   Índice medio
 * @param r   Índice derecho del segundo subarreglo
 */
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Crea arreglos temporales */
    int L[n1], R[n2];

    /* Copia los datos a los arreglos temporales L[] y R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Combina los arreglos temporales de vuelta a arr[l..r] */
    i = 0; // Índice inicial del primer subarreglo
    j = 0; // Índice inicial del segundo subarreglo
    k = l; // Índice inicial del subarreglo combinado
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copia los elementos restantes de L[], si hay alguno */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copia los elementos restantes de R[], si hay alguno */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * Función principal que ordena arr[l..r] usando merge().
 * @param arr El arreglo que se va a ordenar
 * @param l   Índice izquierdo del subarreglo
 * @param r   Índice derecho del subarreglo
 */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Lo mismo que (l+r)/2, pero evita desbordamiento para l y h grandes
        int m = l + (r - l) / 2;

        // Ordena las primeras y segundas mitades
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Combina las mitades ordenadas
        merge(arr, l, m, r);
    }
}

/**
 * Función para imprimir un arreglo.
 * @param arr El arreglo que se va a imprimir
 * @param n   Tamaño del arreglo
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {38,27,43,3,9,82,10};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("El arreglo dado es \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nEl arreglo ordenado es \n");
    printArray(arr, arr_size);
    return 0;
}
