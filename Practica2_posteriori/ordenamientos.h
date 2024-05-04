#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H
#define TAM 50000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
// Definición de estructuras
struct Nodo {
    int dato;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

struct Nodo* nuevoNodo(int valor) {
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->dato = valor;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}

// Prototipos de funciones
int* bublesort(int* arr, int tam);
int* insertionsort(int* arr, int tam);
int* selectonsort(int* arr, int tam);
int pivot(int A[], int p, int r);
void muestra(int* arr, int tam);
void QuickSort(int A[], int p, int r);
void intercambiar(int A[], int i, int j);
struct Nodo* insertar(struct Nodo* nodo, int valor);
void guardarRecorridoInOrden(struct Nodo* nodo, int A[], int* indice);
void ordenaArbolBinarioBusqueda(int A[], int n);
void Shell(int A[], int n);
int* cargardatos(const char *path);
void medirTiempoAlgoritmo(void* algoritmo(int*, int), int arr[], int tam);
void medirTiempoAlgoritmoQuick(void algoritmo(int*, int, int), int arr[], int p, int r);
// Desarrollo
int* bublesort(int* arr, int tam) {
    int* aux;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                aux = &arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = *aux;
            }
        }
    }
    return arr;
}

int* insertionsort(int* arr, int tam) {
    int j = 0;
    int aux;
    for (int i = 0; i < tam - 1; i++) {
        j = i;
        aux = arr[i];
        while ((j > 0) && (aux < arr[j - 1])) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = aux;
    }
    return arr;
}

int* selectonsort(int* arr, int tam) {
    int p;
    int aux = 0;
    for (int k = 0; k < tam - 1; k++) {
        p = k;
        for (int i = k + 1; i < tam; i++) {
            if (arr[i] < arr[p]) {
                p = i;
            }
        }
        aux = arr[p];
        arr[p] = arr[k];
        arr[k] = aux;
    }
    return arr;
}

void intercambiar(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void QuickSort(int A[], int p, int r) {
    if (p < r) {
        int j = pivot(A, p, r);
        QuickSort(A, p, j - 1);
        QuickSort(A, j + 1, r);
    }
}

int pivot(int A[], int p, int r) {
    int piv = A[p];
    int i = p + 1;
    int j = r;
    while (1) {
        while (i <= r && A[i] < piv) {
            i++;
        }
        while (A[j] > piv) {
            j--;
        }
        if (i < j) {
            intercambiar(A, i, j);
        } else {
            intercambiar(A, p, j);
            return j;
        }
    }
}

void muestra(int* arr, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d,", arr[i]);
    }
}

struct Nodo* insertar(struct Nodo* nodo, int valor) {
    if (nodo == NULL) {
        nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
        nodo->dato = valor;
        nodo->izquierda = NULL;
        nodo->derecha = NULL;
    } else {
        if (valor < nodo->dato) {
            nodo->izquierda = insertar(nodo->izquierda, valor);
        } else {
            nodo->derecha = insertar(nodo->derecha, valor);
        }
    }
    return nodo;
}

void guardarRecorridoInOrden(struct Nodo* nodo, int A[], int* indice) {
    if (nodo != NULL) {
        guardarRecorridoInOrden(nodo->izquierda, A, indice);
        A[(*indice)++] = nodo->dato;
        guardarRecorridoInOrden(nodo->derecha, A, indice);
    }
}

void ordenaArbolBinarioBusqueda(int A[], int n) {
    struct Nodo* arbolBinBusqueda = NULL;
    for (int i = 0; i < n; i++) {
        arbolBinBusqueda = insertar(arbolBinBusqueda, A[i]);
    }
    int indice = 0;
    guardarRecorridoInOrden(arbolBinBusqueda, A, &indice);
}
void Shell(int A[], int n) {
    int k = n / 2;
    while (k >= 1) {
        int b = 1;
        while (b != 0) {
            b = 0;
            for (int i = k; i < n; i++) {
                if (A[i - k] > A[i]) {
                    int temp = A[i];
                    A[i] = A[i - k];
                    A[i - k] = temp;
                    b = b + 1;
                }
            }
        }
        k = k / 2;
    }
}

int* cargardatos(const char *path) {
    int* datos = (int*)malloc(TAM * sizeof(int)); // Asignar memoria para el arreglo de datos
    FILE* archivo;
    int numdatos = 0;
    char linea[100];

    archivo = fopen(path, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Convertir la línea a entero y almacenarla en el arreglo de datos
        datos[numdatos] = atoi(linea);
        numdatos++;
        if (numdatos >= TAM) {
            printf("max num datos permitidos %d\n",TAM);
            break;
        }
    }

    fclose(archivo);
    return datos;
}
void medirTiempoAlgoritmo(void* algoritmo(int*, int), int arr[], int tam) {
    printf("midiendo el tiempo del algoritmo");
    LARGE_INTEGER inicio_real, fin_real,frecuencia;
    clock_t inicio_cpu, fin_cpu;
    double real_time;
    // Medir tiempo real
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&inicio_real);
    // Medir tiempo de CPU
    inicio_cpu = clock();

    // Llamar al algoritmo con el arreglo proporcionado
    algoritmo(arr, tam);
    //int* resultado = algoritmo(arr, tam);
    //free(resultado); // Liberar la memoria asignada si es necesario

    // Finalizar la medición del tiempo de CPU
    fin_cpu = clock();

    // Medir tiempo real
    QueryPerformanceCounter(&fin_real);
    real_time=(double)(fin_real.QuadPart-inicio_real.QuadPart)/frecuencia.QuadPart;

    // Calcular tiempo de ejecución en segundos para cada medida
    double tiempo_cpu = (double)(fin_cpu - inicio_cpu) / CLOCKS_PER_SEC;

    // Imprimir resultados
    printf("Tiempo real: %f segundos\n", real_time);
    printf("Tiempo de CPU: %f segundos\n", tiempo_cpu);
}
void medirTiempoAlgoritmoQuick(void algoritmo(int*, int, int), int arr[], int p, int r) {
    LARGE_INTEGER inicio_real, fin_real, frecuencia;
    clock_t inicio_cpu, fin_cpu;

    // Medir tiempo real
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&inicio_real);

    // Medir tiempo de CPU
    inicio_cpu = clock();

    // Llamar al algoritmo con el arreglo proporcionado
    algoritmo(arr, p, r);

    // Finalizar la medición del tiempo de CPU
    fin_cpu = clock();

    // Medir tiempo real
    QueryPerformanceCounter(&fin_real);
    double real_time = (double)(fin_real.QuadPart - inicio_real.QuadPart) / frecuencia.QuadPart;

    // Calcular tiempo de ejecución en segundos para cada medida
    double tiempo_cpu = (double)(fin_cpu - inicio_cpu) / CLOCKS_PER_SEC;

    // Imprimir resultados
    printf("Tiempo real: %f segundos\n", real_time);
    printf("Tiempo de CPU: %f segundos\n", tiempo_cpu);
}
#endif // ORDENAMIENTOS_H
