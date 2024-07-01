#include "huffman.h"
#include <stdlib.h>

/* Variables globales */
tipoTabla *Tabla;

void Cuenta(tipoNodo **Lista, char c)
{
   tipoNodo *p, *a, *q;

   if(!(*Lista))  /* Si la lista está vacía, el nuevo nodo será Lista */
   {
      *Lista = (tipoNodo *)malloc(sizeof(tipoNodo)); /* Un nodo nuevo */
      (*Lista)->letra = c;                           /* Para c */
      (*Lista)->frecuencia = 1;                      /* en su 1ª aparición */
      (*Lista)->sig = (*Lista)->cero = (*Lista)->uno = NULL;
   }
   else
   {
      /* Buscar el caracter en la lista (ordenada por letra) */
      p = *Lista;
      a = NULL;
      while(p && p->letra < c)
      {
         a = p;      /* Guardamos el elemento actual para insertar */
         p = p->sig; /* Avanzamos al siguiente */
      }
      /* Dos casos: */
      /* 1) La letra es c se encontró */
      if(p && p->letra == c) p->frecuencia++; /* Actualizar frecuencia */
      else
      /* 2) La letra c no se encontró*/
      {
         /* Insertar un elemento nuevo */
         q = (tipoNodo *)malloc(sizeof(tipoNodo));
         q->letra = c;
         q->frecuencia = 1;
         q->cero = q->uno = NULL;
         q->sig = p;        /* Insertar entre los nodos p */
         if(a) a->sig = q;  /* y a */
         else *Lista = q;   /* Si a es NULL el nuevo es el primero */
      }
   }
}

void Ordenar(tipoNodo **Lista)
{
   tipoNodo *Lista2, *a;

   if(!(*Lista)) return; /* Lista vacia */
   Lista2 = *Lista;
   *Lista = NULL;
   while(Lista2)
   {
      a = Lista2;              /* Toma los elementos de Lista2 */
      Lista2 = a->sig;
      InsertarOrden(Lista, a); /* Y los inserta por orden en Lista */
   }
}

void InsertarOrden(tipoNodo **Cabeza, tipoNodo *e)
{
   tipoNodo *p, *a;

   if(!(*Cabeza)) /* Si Cabeza en NULL, e es el primer elemento */
   {
      *Cabeza = e;
      (*Cabeza)->sig = NULL;
   }
   else
   {
       /* Buscar el caracter en la lista (ordenada por frecuencia) */
       p = *Cabeza;
       a = NULL;
       while(p && p->frecuencia < e->frecuencia)
       {
          a = p;      /* Guardamos el elemento actual para insertar */
          p = p->sig; /* Avanzamos al siguiente */
       }
       /* Insertar el elemento */
       e->sig = p;
       if(a) a->sig = e;   /* Insertar entre a y p */
       else *Cabeza = e;   /* el nuevo es el primero */
    }
}

void CrearTabla(tipoNodo *n, int l, int v)
{
   if(n->uno)  CrearTabla(n->uno, l+1, (v<<1)|1);
   if(n->cero) CrearTabla(n->cero, l+1, v<<1);
   if(!n->uno && !n->cero) InsertarTabla(n->letra, l, v);
}

void InsertarTabla(char c, int l, int v)
{
   tipoTabla *t, *p, *a;

   t = (tipoTabla *)malloc(sizeof(tipoTabla)); /* Crea un elemento de tabla */
   t->letra = c;                               /* Y lo inicializa */
   t->bits = v;
   t->nbits = l;

   if(!Tabla)         /* Si tabla es NULL, entonces el elemento t es el 1º */
   {
      Tabla = t;
      Tabla->sig = NULL;
   }
   else
   {
       /* Buscar el caracter en la lista (ordenada por frecuencia) */
       p = Tabla;
       a = NULL;
       while(p && p->letra < t->letra)
       {
          a = p;      /* Guardamos el elemento actual para insertar */
          p = p->sig; /* Avanzamos al siguiente */
       }
       /* Insertar el elemento */
       t->sig = p;
       if(a) a->sig = t;  /* Insertar entre a y p */
       else Tabla = t;    /* el nuevo es el primero */
    }
}

tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c)
{
   tipoTabla *t;

   t = Tabla;
   while(t && t->letra != c) t = t->sig;
   return t;
}

void BorrarArbol(tipoNodo *n)
{
   if(n->cero) BorrarArbol(n->cero);
   if(n->uno)  BorrarArbol(n->uno);
   free(n);
}
