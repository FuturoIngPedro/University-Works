#include "simulacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparador de IDs de Posteos para usar en la caché
int compararIDs(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

// Simulación sin caché: busca los posteos directamente en el archivo
void simularSinCache(FILE* archivoPosteos, UsuarioFeed* usuarios, int numUsuarios)
{
    Posteo p;
    double tiempoPosteo, tiempoUsuario, tiempoTotalPosteos, tiempoTotalUsuarios;
    double tiempoInicioUsuario, tiempoInicioPosteo;
    int totalPosteos, totalUsuarios, i, j;

    totalPosteos = 0;
    totalUsuarios = 0;
    tiempoTotalPosteos = 0.0;
    tiempoTotalUsuarios = 0.0;

    for (i = 0; i < numUsuarios; i++)
    {
        tiempoInicioUsuario = (double)clock();
        for (j = 0; j < MAX_FEED; j++)
        {
            tiempoInicioPosteo = (double)clock();

            // Accedo al posteo de manera directa
            fseek(archivoPosteos, usuarios[i].feed[j] * sizeof(Posteo), SEEK_SET);
            fread(&p, sizeof(Posteo), 1, archivoPosteos);

            // Simulo la busqueda
            tiempoPosteo = ((double)clock() - tiempoInicioPosteo) / CLOCKS_PER_SEC;
            tiempoTotalPosteos += tiempoPosteo;
            totalPosteos++;
        }
        tiempoUsuario = ((double)clock() - tiempoInicioUsuario) / CLOCKS_PER_SEC;
        tiempoTotalUsuarios += tiempoUsuario;
        totalUsuarios++;
    }

    printf("Tiempo promedio por posteo sin cache: %.10f segundos\n", tiempoTotalPosteos / totalPosteos);
    printf("Tiempo promedio por usuario sin cache: %.10f segundos\n", tiempoTotalUsuarios / totalUsuarios);
}

// Simulación con caché: utiliza el LRU Cache para buscar posteos
void simularConCache(FILE* archivoPosteos, UsuarioFeed* usuarios, int numUsuarios, int tamCache)
{
    Posteo p;
    LRUCache cache;
    int aciertos, fallos, totalPosteos, totalUsuarios, i, j, posteoID;
    double tiempoPosteo, tiempoUsuario, tiempoTotalPosteos, tiempoTotalUsuarios;
    double tiempoInicioUsuario, tiempoInicioPosteo;
    Posteo* posteoGuardado;

    aciertos = 0;
    fallos = 0;
    totalPosteos = 0;
    totalUsuarios = 0;
    tiempoTotalPosteos = 0.0;
    tiempoTotalUsuarios = 0.0;

    crear_lrucache(&cache, tamCache);

    for (i = 0; i < numUsuarios; i++)
    {
        tiempoInicioUsuario = (double)clock();
        for (j = 0; j < MAX_FEED; j++)
        {
            tiempoInicioPosteo = (double)clock();
            posteoID = usuarios[i].feed[j];
            posteoGuardado = obtener_lrucache(&cache, &posteoID, compararIDs);

            if(posteoGuardado == NULL)
            {
                // No está en la caché, busco en el archivo
                fseek(archivoPosteos, posteoID * sizeof(Posteo), SEEK_SET);
                fread(&p, sizeof(Posteo), 1, archivoPosteos);
                fallos++;

                // Agrego el elemento a la caché
                agregar_lrucache(&cache, &p.id, sizeof(int), compararIDs);
            }
            else
                aciertos++;

            tiempoPosteo = ((double)clock() - tiempoInicioPosteo) / CLOCKS_PER_SEC;
            tiempoTotalPosteos += tiempoPosteo;
            totalPosteos++;
        }
        tiempoUsuario = ((double)clock() - tiempoInicioUsuario) / CLOCKS_PER_SEC;
        tiempoTotalUsuarios += tiempoUsuario;
        totalUsuarios++;
    }

    printf("Tasa de aciertos (hit): %.2f%%\n", (aciertos / (double)(aciertos + fallos)) * 100);
    printf("Tasa de fallos (miss): %.2f%%\n", (fallos / (double)(aciertos + fallos)) * 100);
    printf("Tiempo promedio por posteo con cache: %.10f segundos\n", tiempoTotalPosteos / totalPosteos);
    printf("Tiempo promedio por usuario con cache: %.10f segundos\n", tiempoTotalUsuarios / totalUsuarios);

    vaciar_lrucache(&cache);
}
