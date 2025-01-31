#include "generacionDatos.h"
#include "../Simulacion/simulacion.h"

#include <string.h>
#include <stdio.h>
#include <time.h>

//Funciones utiles para los archivos de los lotes de prueba
void mostrarContenidoArchivo(const char *rutaArchivo, const char *tipoEstructura)
{
    Posteo posteo;
    UsuarioFeed usuario;
    int i;

    FILE *archivo = fopen(rutaArchivo, "rb");
    if (!archivo)
    {
        perror("Error al abrir el archivo");
        return;
    }

    if (strcmp(tipoEstructura, "Posteo") == 0)
    {
        printf("Contenido del archivo de posteos:\n");
        while (fread(&posteo, sizeof(Posteo), 1, archivo) == 1)
        {
            printf("ID: %d\n", posteo.id);
            printf("Texto: %s\n\n", posteo.texto);
        }
    }
    else
        if (strcmp(tipoEstructura, "Usuario") == 0)
        {
            printf("Contenido del archivo de usuarios:\n");
            while (fread(&usuario, sizeof(UsuarioFeed), 1, archivo))
            {
                printf("Usuario: %s\n", usuario.usuario);
                printf("Feed: ");
                for (i = 0; i < MAX_FEED; i++) {
                    printf("%d ", usuario.feed[i]);
                }
                printf("\n\n");
        }
    }
    else
        printf("Tipo de estructura no reconocido.\n");

    fclose(archivo);
}

void generarTextoAleatorio(char *texto, int longitud)
{
    char caracteres[] = "!\"·$%&/()=_-.,abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int tam = rand() % (longitud - 1);
    int i, j;

    if(tam < 5)
        tam += 5;

    for (i = 0; i < tam; i++)
    {
        j = rand() % (int)(sizeof(caracteres) - 1);
        texto[i] = caracteres[j];
    }
    texto[tam] = '\0';
}

void generarPosteos(const char* nombreArchivo)
{
    Posteo p;
    int i;

    FILE *fp = fopen(nombreArchivo, "wb");
    if (!fp)
    {
        printf("Error al crear el archivo de posteos.\n");
        return;
    }

    for (i = 0; i < NUM_POSTEOS; i++)
    {
        p.id = i;
        generarTextoAleatorio(p.texto, MAX_POSTEO);
        fwrite(&p, sizeof(Posteo), 1, fp);
    }

    fclose(fp);
    printf("Archivo de posteos generado correctamente.\n");
}

void generarFeedsAltaDispersion(const char* nombreArchivo)
{
    UsuarioFeed u;
    int i, j;

    FILE *fp = fopen(nombreArchivo, "wb");
    if (!fp)
    {
        printf("Error al crear el archivo de feeds.\n");
        return;
    }

    srand(time(NULL));  // Para generar números aleatorios basados en el tiempo actual

    for (i = 0; i < NUM_USUARIOS; i++)
    {
        // Genero un nombre de usuario aleatorio
        generarTextoAleatorio(u.usuario, MAX_NOMBRE_USUARIO);

        // Genero un feed con IDs de Posteos aleatorios
        for (j = 0; j < MAX_FEED; j++)
            u.feed[j] = rand() % NUM_POSTEOS;

        fwrite(&u, sizeof(UsuarioFeed), 1, fp);
    }

    fclose(fp);
    printf("Archivo de feeds con alta dispersion generado correctamente.\n");
}

void generarFeedsBajaDispersion(const char* nombreArchivo, int numPosteosPopulares)
{
    UsuarioFeed u;
    int* posteosPopulares, i, j, offset, postId;

    FILE *fp = fopen(nombreArchivo, "wb");
    if (!fp)
    {
        printf("Error al crear el archivo de feeds.\n");
        return;
    }

    srand(time(NULL));  // Para generar números aleatorios basados en el tiempo actual

    // Creo el conjunto de posteos populares
    posteosPopulares = malloc(numPosteosPopulares * sizeof(int));
    if (!posteosPopulares)
    {
        printf("Error de memoria al crear el conjunto de posteos populares.\n");
        fclose(fp);
        return;
    }

    for (i = 0; i < numPosteosPopulares; i++)
        posteosPopulares[i] = rand() % NUM_POSTEOS;  // IDs de posteos populares aleatorios

    for (i = 0; i < NUM_USUARIOS; i++)
    {
        // Genero un nombre de usuario aleatorio
        generarTextoAleatorio(u.usuario, MAX_NOMBRE_USUARIO);

        // Genero un feed con cierta variación
        for (j = 0; j < MAX_FEED; j++)
        {
            // Para dar un poco de variación, elijo uno de los posteos populares
            // y le añado un pequeño desplazamiento aleatorio.
            offset = (rand() % 5) - 2;  // Desplazamiento aleatorio entre -2 y +2

            postId = posteosPopulares[rand() % numPosteosPopulares] + offset;
            //Elijo un posteo popular random y le agrego un offset

            // Me aseguro de que el ID no sea negativo ni exceda el número de posteos
            if (postId < 1)
                postId = 1;
            if (postId > NUM_POSTEOS)
                postId = NUM_POSTEOS;

            u.feed[j] = postId;  // Asigno el ID del posteo modificado
        }

        fwrite(&u, sizeof(UsuarioFeed), 1, fp);
    }

    free(posteosPopulares);
    fclose(fp);
    printf("Archivo de feeds con baja dispersion generado correctamente.\n");
}
