#include "lrucache.h"

// Función auxiliar para crear un nuevo nodo
Nodo* crearNodo(const void* d, unsigned tamInfo)
{
    Nodo* nuevo;

    if((nuevo = (Nodo*)malloc(sizeof(Nodo))) == NULL ||
        (nuevo->info = malloc(tamInfo)) == NULL)
    {
        free(nuevo);
        return NULL;
    }

    memcpy(nuevo->info, d, tamInfo);
    nuevo->tamInfo = tamInfo;
    nuevo->sig = NULL;

    return nuevo;
}

// Crear la caché LRU
void crear_lrucache(LRUCache* cache, int capacidad)
{
    cache->head = NULL;
    cache->max = capacidad;
    cache->size = 0;
}

// Agregar un nuevo elemento a la caché
void agregar_lrucache(LRUCache* cache, const void* d, unsigned tamInfo, int (Comparar)(const void*, const void*))
{
    // Creo y agrego un nuevo nodo al frente
    Nodo** pl;
    Nodo* nodoDuplicado;
    Nodo* nuevo = crearNodo(d, tamInfo);

    if (!nuevo)
        return;

    nuevo->sig = cache->head;
    cache->head = nuevo;
    cache->size++;

    // Busco duplicados (empezando desde el segundo nodo en adelante) y elimino si los hay
    pl = &cache->head->sig;  // Comienzo a buscar desde el segundo nodo
    while (*pl)
    {
        if (Comparar((*pl)->info, d) == 0)
        {
            // Duplicado encontrado -> lo elimino
            nodoDuplicado = *pl;
            *pl = nodoDuplicado->sig;
            free(nodoDuplicado->info);
            free(nodoDuplicado);
            cache->size--;
            break;  // Termino la búsqueda al encontrar un duplicado
        }
        pl = &(*pl)->sig;
    }

    // Verifico si la caché excede el tamaño máximo y elimino el último nodo si es necesario
    if (cache->size > cache->max)
    {
        pl = &cache->head;
        while ((*pl)->sig)
            pl = &(*pl)->sig;

        free((*pl)->info);   // Libero la memoria de la info del último nodo
        free(*pl);           // Libero la memoria del nodo
        *pl = NULL;          // Ajusto el puntero del penúltimo nodo
        cache->size--;
    }
}

// Obtener un elemento de la caché
void* obtener_lrucache(LRUCache* cache, const void* d, int (Comparar)(const void*, const void*))
{
    Nodo** pl = &cache->head;
    Nodo* nodoEncontrado;

    while (*pl)
    {
        if (Comparar((*pl)->info, d) == 0)
        {
            nodoEncontrado = *pl;
            *pl = nodoEncontrado->sig;          // Desvinculo el nodo
            nodoEncontrado->sig = cache->head;  // Muevo al frente
            cache->head = nodoEncontrado;
            return nodoEncontrado->info;
        }
        pl = &(*pl)->sig;
    }

    return NULL;  // Elemento no encontrado
}

// Borrar un elemento de la caché
void borrar_lrucache(LRUCache* cache, const void* d, int (Comparar)(const void*, const void*))
{
    Nodo** pl = &cache->head;
    Nodo* nodoEliminar;

    while (*pl)
    {
        if (Comparar((*pl)->info, d) == 0)
        {
            nodoEliminar = *pl;           // Guardo el nodo actual antes de avanzar
            *pl = nodoEliminar->sig;      // Desvinculo el nodo
            free(nodoEliminar->info);     // Libero la memoria de los datos
            free(nodoEliminar);           // Libero el nodo
            cache->size--;
            return;
        }
        pl = &(*pl)->sig;
    }
}

// Vaciar toda la caché y liberar memoria
void vaciar_lrucache(LRUCache* cache)
{
    Nodo** pl = &cache->head;
    Nodo* temp;

    while (*pl)
    {
        temp = *pl;        // Guardo el nodo actual antes de avanzar
        *pl = (*pl)->sig;  // Avanzo al siguiente nodo
        free(temp->info);  // Libero la memoria de los datos
        free(temp);        // Libero el nodo
    }

    // Reinicio el estado de la caché
    cache->head = NULL;
    cache->size = 0;
}

