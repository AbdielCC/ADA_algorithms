#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>

/**
 * @brief Estructura para un nodo en el árbol de Huffman o lista de árboles.
 */
typedef struct nodo
{
   char letra;              /**< Letra a la que hace referencia el nodo */
   int frecuencia;          /**< Veces que aparece la letra en el texto o las letras de los nodos de las ramas cero y uno */
   struct nodo *sig;        /**< Puntero a siguiente nodo de una lista enlazada */
   struct nodo *cero;       /**< Puntero a la rama cero de un árbol */
   struct nodo *uno;        /**< Puntero a la rama uno de un árbol */
} tipoNodo;

/**
 * @brief Estructura para un nodo en la tabla de códigos.
 */
typedef struct tabla
{
   char letra;                    /**< Letra a la que hace referencia el nodo */
   unsigned long int bits;        /**< Valor de la codificación de la letra */
   char nbits;                    /**< Número de bits de la codificación */
   struct tabla *sig;             /**< Siguiente elemento de la tabla */
} tipoTabla;

/* Variables globales */
extern tipoTabla *Tabla;

/* Prototipos de funciones */

/**
 * @brief Actualiza la cuenta de frecuencia del carácter c en la lista.
 * @param Lista Puntero a la lista de nodos.
 * @param c Carácter a actualizar.
 */
void Cuenta(tipoNodo **Lista, char c);

/**
 * @brief Ordena la lista de menor a mayor por frecuencias.
 * @param Lista Puntero a la lista de nodos.
 */
void Ordenar(tipoNodo **Lista);

/**
 * @brief Inserta el elemento e en la lista ordenada por frecuencia de menor a mayor.
 * @param Cabeza Puntero a la cabeza de la lista.
 * @param e Nodo a insertar.
 */
void InsertarOrden(tipoNodo **Cabeza, tipoNodo *e);

/**
 * @brief Borra un árbol de Huffman.
 * @param n Puntero a la raíz del árbol a borrar.
 */
void BorrarArbol(tipoNodo *n);

/**
 * @brief Recorre el árbol cuya raíz es n y le asigna el código v de l bits.
 * @param n Puntero a la raíz del árbol.
 * @param l Número de bits del código.
 * @param v Código binario.
 */
void CrearTabla(tipoNodo *n, int l, int v);

/**
 * @brief Inserta un elemento en la tabla de códigos.
 * @param c Carácter a insertar.
 * @param l Número de bits del código.
 * @param v Código binario.
 */
void InsertarTabla(char c, int l, int v);

/**
 * @brief Busca un carácter en la tabla y devuelve un puntero al elemento.
 * @param Tabla Puntero a la tabla de códigos.
 * @param c Carácter a buscar.
 * @return Puntero al nodo en la tabla que contiene el carácter.
 */
tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c);
#endif // HUFFMAN_H
