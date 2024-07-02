#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "huffman.h"

int main(int argc, char *argv[])
{
    // Variables para medir el tiempo
    clock_t start, end;
    double cpu_time_used;

    tipoNodo *Lista;       /* Lista de letras y frecuencias */
    tipoNodo *Arbol;       /* Arbol de letras y frecuencias */

    FILE *fe, *fs;         /* Ficheros de entrada y salida */
    char c;                /* variables auxiliares */
    tipoNodo *p;
    tipoTabla *t;
    int nElementos;        /* Número de elementos en tabla */
    long int Longitud = 0; /* Longitud del fichero original */

    unsigned long int dWORD; /* Doble palabra usada durante la codificación */
    int nBits;               /* Número de bits usados de dWORD */

    if(argc < 3)
    {
        printf("Usar:\n%s <fichero_entrada> <fichero_salida>\n", argv[0]);
        return 1;
    }

    Lista = NULL;
    /* Fase 1: contar frecuencias */
    fe = fopen(argv[1], "r");
    if (fe == NULL)
    {
        perror("Error al abrir el fichero de entrada");
        return 1;
    }

    start = clock(); // Iniciar medición de tiempo
    while((c = fgetc(fe)) != EOF)
    {
        Longitud++;       /* Actualiza la cuenta de la longitud del fichero */
        Cuenta(&Lista, c); /* Actualiza la lista de frecuencias */
    }
    fclose(fe);
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para contar frecuencias: %f segundos\n", cpu_time_used);

    /* Ordenar la lista de menor a mayor */
    start = clock(); // Iniciar medición de tiempo
    Ordenar(&Lista);
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para ordenar la lista: %f segundos\n", cpu_time_used);

    /* Crear el arbol */
    start = clock(); // Iniciar medición de tiempo
    Arbol = Lista;
    while(Arbol && Arbol->sig) /* Mientras existan al menos dos elementos en la lista */
    {
        p = (tipoNodo *)malloc(sizeof(tipoNodo)); /* Un nuevo árbol */
        p->letra = 0;                             /* No corresponde a ninguna letra */
        p->uno = Arbol;                           /* Rama uno */
        Arbol = Arbol->sig;                       /* Siguiente nodo en */
        p->cero = Arbol;                          /* Rama cero */
        Arbol = Arbol->sig;                       /* Siguiente nodo */
        p->frecuencia = p->uno->frecuencia + p->cero->frecuencia; /* Suma de frecuencias */
        InsertarOrden(&Arbol, p);                 /* Inserta en nuevo nodo */
    }                                            /* orden de frecuencia */
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para crear el árbol de Huffman: %f segundos\n", cpu_time_used);

    /* Construir la tabla de códigos binarios */
    start = clock(); // Iniciar medición de tiempo
    Tabla = NULL;
    CrearTabla(Arbol, 0, 0);
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para crear la tabla de códigos: %f segundos\n", cpu_time_used);

    /* Crear fichero comprimido */
    fs = fopen(argv[2], "wb");
    if (fs == NULL)
    {
        perror("Error al abrir el fichero de salida");
        return 1;
    }

    start = clock(); // Iniciar medición de tiempo
    /* Escribir la longitud del fichero */
    fwrite(&Longitud, sizeof(long int), 1, fs);
    /* Cuenta el número de elementos de tabla */
    nElementos = 0;
    t = Tabla;
    while(t)
    {
        nElementos++;
        t = t->sig;
    }
    /* Escribir el número de elementos de tabla */
    fwrite(&nElementos, sizeof(int), 1, fs);
    /* Escribir tabla en fichero */
    t = Tabla;
    while(t)
    {
        fwrite(&t->letra, sizeof(char), 1, fs);
        fwrite(&t->bits, sizeof(unsigned long int), 1, fs);
        fwrite(&t->nbits, sizeof(char), 1, fs);
        t = t->sig;
    }

    /* Codificación del fichero de entrada */
    fe = fopen(argv[1], "r");
    if (fe == NULL)
    {
        perror("Error al abrir el fichero de entrada");
        return 1;
    }
    dWORD = 0; /* Valor inicial. */
    nBits = 0; /* Ningún bit */
    while((c = fgetc(fe)) != EOF)
    {
        /* Busca c en tabla: */
        t = BuscaCaracter(Tabla, c);
        /* Si nBits + t->nbits > 32, sacar un byte */
        while(nBits + t->nbits > 32)
        {
            c = dWORD >> (nBits-8);           /* Extrae los 8 bits de mayor peso */
            fwrite(&c, sizeof(char), 1, fs);  /* Y lo escribe en el fichero */
            nBits -= 8;                       /* Ya tenemos hueco para 8 bits más */
        }
        dWORD <<= t->nbits; /* Hacemos sitio para el nuevo caracter */
        dWORD |= t->bits;   /* Insertamos el nuevo caracter */
        nBits += t->nbits;  /* Actualizamos la cuenta de bits */
    }
    /* Extraer los cuatro bytes que quedan en dWORD */
    while(nBits > 0)
    {
        if(nBits >= 8) c = dWORD >> (nBits-8);
        else c = dWORD << (8-nBits);
        fwrite(&c, sizeof(char), 1, fs);
        nBits -= 8;
    }

    fclose(fe);  /* Cierra los ficheros */
    fclose(fs);
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para codificar el fichero de entrada: %f segundos\n", cpu_time_used);

    /* Borrar Arbol */
    start = clock(); // Iniciar medición de tiempo
    BorrarArbol(Arbol);
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para borrar el árbol: %f segundos\n", cpu_time_used);

    /* Borrar Tabla */
    start = clock(); // Iniciar medición de tiempo
    while(Tabla)
    {
        t = Tabla;
        Tabla = t->sig;
        free(t);
    }
    end = clock(); // Fin de medición de tiempo
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo para borrar la tabla: %f segundos\n", cpu_time_used);

    return 0;
}

