#ifndef LRU_CACHE_H_INCLUDED
#define LRU_CACHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Nodo
{
    void* info;
    unsigned tamInfo;
    struct Nodo* sig;
} Nodo;

typedef struct
{
    Nodo* head;   // Apunta al nodo más recientemente usado
    int max;      // Capacidad máxima de la lista
    int size;     // Tamaño actual de la lista
} LRUCache;

void crear_lrucache(LRUCache* cache, int capacidad);
void agregar_lrucache(LRUCache* cache, const void* d, unsigned tamInfo, int (*Comparar)(const void*, const void*));
void* obtener_lrucache(LRUCache* cache, const void* d, int(Comparar)(const void*, const void*));
void borrar_lrucache(LRUCache* cache, const void* d, int(Comparar)(const void*, const void*));
void vaciar_lrucache(LRUCache* cache);

#endif // LRU_CACHE_H_INCLUDED
