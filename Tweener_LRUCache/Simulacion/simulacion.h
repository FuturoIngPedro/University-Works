#ifndef SIMULACION_H_INCLUDED
#define SIMULACION_H_INCLUDED

#include "../LruCache/lrucache.h"

#define NUM_POSTEOS 50000
#define MAX_POSTEO 141
#define NUM_USUARIOS 5000
#define MAX_FEED 20
#define MAX_NOMBRE_USUARIO 15

typedef struct
{
    char usuario[MAX_NOMBRE_USUARIO];
    int feed[MAX_FEED];
} UsuarioFeed;

typedef struct
{
    int id;
    char texto[MAX_POSTEO];
} Posteo;

void simularConCache(FILE* archivoPosteos, UsuarioFeed* usuarios, int numUsuarios, int tamCache);
void simularSinCache(FILE* archivoPosteos, UsuarioFeed* usuarios, int numUsuarios);

#endif // SIMULACION_H_INCLUDED
