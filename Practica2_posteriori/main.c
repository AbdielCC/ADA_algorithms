#include "ordenamientos.h"
//"C:/Users/Rulig/OneDrive/Escritorio/apps/progra/Escom/ADA/Practica2_posteriori/numeros10millones.txt"

int main() {
    const char* path = "C:/Users/Rulig/OneDrive/Escritorio/apps/progra/Escom/ADA/Practica2_posteriori/numeros10millones.txt";
    int* datos;

    datos = cargardatos(path);
    if (datos == NULL) {
        printf("Error al cargar los datos desde el archivo\n");
        return 1;
    }
    printf("bublesort \n");
    medirTiempoAlgoritmo(bublesort, datos, TAM);
    printf("insertionsort \n");
    medirTiempoAlgoritmo(insertionsort, datos, TAM);
    printf("Selectionsort \n");
    medirTiempoAlgoritmo(selectonsort,datos,TAM);
    printf("Shell Sort \n");
    medirTiempoAlgoritmo(Shell,datos,TAM);
    printf("Arbol bin\n");
    medirTiempoAlgoritmo(ordenaArbolBinarioBusqueda,datos,TAM);
    printf("quicksort \n");
    medirTiempoAlgoritmoQuick(QuickSort,datos,0,TAM-1);
    // Liberar la memoria asignada al arreglo de datos
    free(datos);
    return 0;
}
