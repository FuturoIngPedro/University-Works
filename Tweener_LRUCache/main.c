#include <time.h>

#include "LruCache/lrucache.h"
#include "Simulacion/simulacion.h"
#include "GeneracionDatos/generacionDatos.h"

#define ERROR_MEM 1
#define ERROR_ARCH 2

#define CON_CACHE
#define SIN_CACHE
#define GENERAR_ARCHIVOS
#define MOSTRAR_ARCHIVOS

int main()
{
    FILE* archivoPosteos;
    FILE* archivoFeeds;
    UsuarioFeed* usuarios;
    double tiempoInicio;
    double tiempoFinal;


    #ifdef GENERAR_ARCHIVOS
    generarPosteos("posteos.bin");
    generarFeedsBajaDispersion("feeds.bin", 25);
    //generarFeedsAltaDispersion("feeds.bin");
    #endif // GENERAR_ARCHIVOS


    #ifdef MOSTRAR_ARCHIVOS
    //mostrarContenidoArchivo("posteos.bin", "Posteo");
    mostrarContenidoArchivo("feeds.bin", "Usuario");
    #endif // MOSTRAR_ARCHIVOS

    archivoPosteos = fopen("posteos.bin", "rb");
    if (!archivoPosteos)
    {
        printf("Error al abrir el archivo de Posteos.\n");
        return ERROR_ARCH;
    }

    archivoFeeds = fopen("feeds.bin", "rb");
    if (!archivoFeeds)
    {
        printf("Error al abrir el archivo de feeds.\n");
        fclose(archivoPosteos);
        return ERROR_ARCH;
    }

    usuarios = malloc(NUM_USUARIOS * sizeof(UsuarioFeed));
    if(!usuarios)
    {
        fclose(archivoPosteos);
        fclose(archivoFeeds);
        return ERROR_MEM;
    }

    fread(usuarios, sizeof(UsuarioFeed), NUM_USUARIOS, archivoFeeds);
    fclose(archivoFeeds);

    #ifdef SIN_CACHE
    tiempoInicio = clock();
    printf("Simulacion sin cache:\n");
    simularSinCache(archivoPosteos, usuarios, NUM_USUARIOS);
    tiempoFinal = (double)(clock() - tiempoInicio) / CLOCKS_PER_SEC;
    printf("Tiempo total sin cache: %.5f segundos\n", tiempoFinal);
    #endif // SIN_CACHE


    #ifdef CON_CACHE
    //CACHE TAMAÑO 10
    tiempoInicio = clock();
    printf("\nSimulacion con cache de tamano 10:\n");
    simularConCache(archivoPosteos, usuarios, NUM_USUARIOS, 10);
    tiempoFinal = (double)(clock() - tiempoInicio) / CLOCKS_PER_SEC;
    printf("Tiempo total con cache: %.5f segundos\n", tiempoFinal);

    //CACHE TAMAÑO 50
    tiempoInicio = clock();
    printf("\nSimulacion con cache de tamano 50:\n");
    simularConCache(archivoPosteos, usuarios, NUM_USUARIOS, 50);
    tiempoFinal = (double)(clock() - tiempoInicio) / CLOCKS_PER_SEC;
    printf("Tiempo total con cache: %.5f segundos\n", tiempoFinal);

    //CACHE TAMAÑO 100
    tiempoInicio = clock();
    printf("\nSimulacion con cache de tamano 100:\n");
    simularConCache(archivoPosteos, usuarios, NUM_USUARIOS, 100);
    tiempoFinal = (double)(clock() - tiempoInicio) / CLOCKS_PER_SEC;
    printf("Tiempo total con cache: %.5f segundos\n", tiempoFinal);

    //CACHE TAMAÑO 1000
    tiempoInicio = clock();
    printf("\nSimulacion con cache de tamano 1000:\n");
    simularConCache(archivoPosteos, usuarios, NUM_USUARIOS, 1000);
    tiempoFinal = (double)(clock() - tiempoInicio) / CLOCKS_PER_SEC;
    printf("Tiempo total con cache: %.5f segundos\n", tiempoFinal);
    #endif // CON_CACHE

    free(usuarios);
    fclose(archivoPosteos);

    return 0;
}
