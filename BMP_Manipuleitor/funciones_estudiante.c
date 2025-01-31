#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>
#include"funciones_estudiante.h"

//////////////////////////////////////////////////////////////////////
//FUNCIONES PRINCIPALES
int solucion(int argc, char* argv[])
{
    puts("\t\t\t\t||  BMPMANIPULEITOR  ||");
    procesarArgumentos(argc, argv);
    return TODO_OK;
}

void procesarArgumentos(int argc, char* argv[])
{
    char imagenes[MAX_IMAGENES][LARGO_PALABRA];
    int cantImagenes;
    unsigned short int comandos = 0; // Acá vamos a guardar todos los comandos que hay que ejecutar

    if(argc > 1)
    {
        cantImagenes = buscarImagenes(argc, argv, imagenes);
        if(cantImagenes > 0)
        {
            comandos = buscarComandos(argc, argv);
            if(comandos)
                realizarModificaciones(comandos, imagenes, cantImagenes);
            else
                printf("No se cargo ningun comando\n");
        }
        else
            printf("No se cargo ninguna imagen\n");
    }
    else
        printf("No hay argumentos\n");
}

unsigned short int buscarComandos(int argc, char* argv[])
{
    int indexComandosEncontrados = 0;
    int i = 1;
    unsigned short int comandos = 0;
    char comando[LARGO_PALABRA];

    do
    {
        //PREGUNTO SI EMPIEZA CON '--', QUE QUIERE DECIR QUE ES UN COMANDO
        if(argv[i][0] == '-' && argv[i][1] == '-')
        {
            obtenerPalabra(2, strlen(argv[i]), argv[i], comando);

            if(!strcmp(comando, "negativo"))
                comandos |= COMANDO_NEGATIVO;

            else if(!strcmp(comando, "rotar-derecha"))
                comandos |= COMANDO_ROTAR_D;

            else if(!strcmp(comando, "rotar-izquierda"))
                comandos |= COMANDO_ROTAR_I;

            else if(!strcmp(comando, "escala-de-grises"))
                comandos |= COMANDO_GRIS;

            else if(!strcmp(comando, "aumentar-contraste"))
                comandos |= COMANDO_A_CONTRASTE;

            else if(!strcmp(comando, "reducir-contraste"))
                comandos |= COMANDO_R_CONTRASTE;

            else if(!strcmp(comando, "tonalidad-azul"))
                comandos |= COMANDO_AZUL;

            else if(!strcmp(comando, "tonalidad-verde"))
                comandos |= COMANDO_VERDE;

            else if(!strcmp(comando, "tonalidad-roja"))
                comandos |= COMANDO_ROJO;

            else if(!strcmp(comando, "recortar"))
                comandos |= COMANDO_RECORTAR;

            else if(!strcmp(comando, "comodin"))
                comandos |= COMANDO_COMODIN;

            else if(!strcmp(comando, "concatenar"))
                comandos |= COMANDO_CONCATENAR;

            else if(!strcmp(comando, "achicar"))
                comandos |= COMANDO_ACHICAR;

            else if(!strcmp(comando, "monocromo"))
                comandos |= COMANDO_MONOCROMO;

            else if(!strcmp(comando, "pixelar"))
                comandos |= COMANDO_PIXELAR;

            else if(!strcmp(comando, "rotar180"))
                comandos |= COMANDO_ROTAR_180;

            indexComandosEncontrados++;
        }
        i++;

    }while(i < argc);

    return comandos;
}

int buscarImagenes(int argc, char* argv[], char imagenes[][LARGO_PALABRA])
{
    int i = 1, cantImagenesEncontradas = 0, indexPunto;
    char extension[LARGO_PALABRA];
    char nombreImagen[LARGO_PALABRA];

    do
    {
        //Busco imagen encontrando un '.' por la extension BMP
        indexPunto = encontrarCaracter(argv[i], 0, '.');
        if(indexPunto != -1)
        {
            obtenerPalabra(indexPunto+1, strlen(argv[i]), argv[i], extension);
            if(!strcmp(extension, "bmp"))
            {
                obtenerPalabra(0, strlen(argv[i]), argv[i], nombreImagen);

                strcpy(imagenes[cantImagenesEncontradas], nombreImagen);

                printf("IMAGEN SELECCIONADA: %s\n", imagenes[cantImagenesEncontradas]);

                cantImagenesEncontradas++;
            }
        }
        i++;
    }while(i < argc && cantImagenesEncontradas < MAX_IMAGENES);
    if(cantImagenesEncontradas == MAX_IMAGENES)
        printf("El maximo de imagenes es %d, imagenes adicionales seran ignoradas\n", MAX_IMAGENES);

    return cantImagenesEncontradas;
}

void realizarModificaciones(unsigned short int comandos, char imagenes[][LARGO_PALABRA], int cantImagenes)
{
    bool seModifico;

    puts("\nFILTROS SELECCIONADOS: ");

    if(comandos & COMANDO_NEGATIVO)
        seModifico = negativo(imagenes[0]);

    if(comandos & COMANDO_ROTAR_D)
        seModifico = rotarDerecha(imagenes[0]);

    if(comandos & COMANDO_ROTAR_I)
        seModifico = rotarIzquierda(imagenes[0]);

    if(comandos & COMANDO_GRIS)
        seModifico = escalaGrises(imagenes[0]);

    if(comandos & COMANDO_A_CONTRASTE)
        seModifico = aumentarContraste(imagenes[0]);

    if(comandos & COMANDO_R_CONTRASTE)
        seModifico = reducirContraste(imagenes[0]);

    if(comandos & COMANDO_AZUL)
        seModifico = tonalidadAzul(imagenes[0]);

    if(comandos & COMANDO_VERDE)
        seModifico = tonalidadVerde(imagenes[0]);

    if(comandos & COMANDO_ROJO)
        seModifico = tonalidadRoja(imagenes[0]);

    if(comandos & COMANDO_RECORTAR)
        seModifico = recortar(imagenes[0]);

    if(comandos & COMANDO_COMODIN)
        seModifico = comodin(imagenes[0]);

    if(comandos & COMANDO_CONCATENAR)
        seModifico = concatenar(imagenes, cantImagenes);

    if(comandos & COMANDO_ACHICAR)
        seModifico = achicar(imagenes[0]);

    if(comandos & COMANDO_MONOCROMO)
        seModifico = monocromo(imagenes[0]);

    if(comandos & COMANDO_PIXELAR)
        seModifico = pixelar(imagenes[0]);

    if(comandos & COMANDO_ROTAR_180)
        seModifico = rotar180(imagenes[0]);

    if(!seModifico)
        puts("\t(Error al crear la imagen)");
}

//////////////////////////////////////////////////////////////////////
//FUNCIONES PARA LAS MODIFICACIONES
bool rotar180(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img, imgAux;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Rotar 180 \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    if(!crearImagen(&imgAux, imagenAncho(&img), imagenAlto(&img), 24))
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);
            colorearPixel(&imgAux, &color, anchoDeImagen - 1 - i, altoDeImagen - 1 - j);
       }
    }

    declararNombre(nombreNuevaImagen, "rotar180");

    guardarImagen(&imgAux, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgAux);

    return true;
}


bool pixelar(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Pixelar \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    int k, l, x, y, radio = 10;
    int sumR, sumG, sumB, cont;

    for(i = 0; i < anchoDeImagen; i += radio)
    {
       for(j = 0; j < altoDeImagen; j += radio)
       {
           cont = 0;
           sumR = 0;
           sumG = 0;
           sumB = 0;
           for(k = -radio; k <= radio; k++)
           {
               for(l = -radio; l <= radio; l++)
               {
                   x = i + k;
                   y = j + l;
                   if(x >= 0 && x < anchoDeImagen && y >= 0 && y < altoDeImagen)
                   {
                       obtenerPixel(&img, &color, x, y);
                       sumR += color.r;
                       sumG += color.g;
                       sumB += color.b;
                       cont++;
                   }
               }
           }
           color.r = sumR / cont;
           color.g = sumG / cont;
           color.b = sumB / cont;

           for(k = -radio; k <= radio; k++)
           {
               for(l = -radio; l <= radio; l++)
               {
                   x = i + k;
                   y = j + l;
                   if(x >= 0 && x < anchoDeImagen && y >= 0 && y < altoDeImagen)
                       colorearPixel(&img, &color, x, y);
               }
           }
       }
    }

    declararNombre(nombreNuevaImagen, "pixelar");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;

}

bool negativo(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Negativo \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            color.r = 255 - color.r;
            color.g = 255 - color.g;
            color.b = 255 - color.b;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "negativo");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool rotarDerecha(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img, imgRotada;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Rotar a la derecha ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;
    if(!crearImagen(&imgRotada, imagenAlto(&img), imagenAncho(&img), 24))
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);
            colorearPixel(&imgRotada, &color, j, (imagenAncho(&img)-1) - i);
       }
    }

    declararNombre(nombreNuevaImagen, "rotar-derecha");

    guardarImagen(&imgRotada, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgRotada);

    return true;
}

bool rotarIzquierda(char imagen[])
{
    int i, j, anchoImagen, altoImagen;
    t_color color;
    t_imagen img, imgRotada;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Rotar a la izquierda ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    if(!crearImagen(&imgRotada, imagenAlto(&img), imagenAncho(&img), 24))
        return false;

    anchoImagen = imagenAncho(&img);
    altoImagen = imagenAlto(&img);

    for(i = 0; i < anchoImagen; i++)
    {
        for(j = 0; j < altoImagen; j++)
        {
            obtenerPixel(&img, &color, i, j);
            colorearPixel(&imgRotada, &color, altoImagen - 1 - j, i);
        }
    }

    declararNombre(nombreNuevaImagen, "rotar-izquierda");

    guardarImagen(&imgRotada, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgRotada);

    return true;
}

bool escalaGrises(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    unsigned char prom;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Escala de grises ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            prom = (color.r + color.g + color.b) / 3;
            color.r = prom;
            color.g = prom;
            color.b = prom;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "escala-de-grises");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool aumentarContraste(char imagen[])
{
    int i, j, nuevoRojo, nuevoVerde, nuevoAzul, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Aumentar contraste ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            nuevoRojo = (color.r * 1.25) - (127.0 * 0.25);
            nuevoVerde = (color.g * 1.25) - (127.0 * 0.25);
            nuevoAzul = (color.b * 1.25) - (127.0 * 0.25);

            if(nuevoRojo > 255)
                nuevoRojo = 255;
            if(nuevoRojo < 0)
                nuevoRojo = 0;
            if(nuevoVerde > 255)
                nuevoVerde = 255;
            if(nuevoVerde < 0)
                nuevoVerde = 0;
            if(nuevoAzul > 255)
                nuevoAzul = 255;
            if(nuevoAzul < 0)
                nuevoAzul = 0;

            color.r = nuevoRojo;
            color.g = nuevoVerde;
            color.b = nuevoAzul;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "aumentar-contraste");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool reducirContraste(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Reducir contraste ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            color.r = (color.r * 0.75) + (127.0 * 0.25);
            color.g = (color.g * 0.75) + (127.0 * 0.25);
            color.b = (color.b * 0.75) + (127.0 * 0.25);

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "reducir-contraste");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool tonalidadAzul(char imagen[])
{
    int i, j, azul, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Tonalidad azul ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            azul = color.b * 1.5;

            if(azul > 255)
                azul = 255;
            color.b = azul;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "tonalidad-azul");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool tonalidadVerde(char imagen[])
{
    int i, j, verde, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Tonalidad verde ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            verde = color.g * 1.5;
            if(verde > 255)
                verde = 255;
            color.g = verde;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "tonalidad-verde");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool tonalidadRoja(char imagen[])
{
    int i, j, rojo, anchoDeImagen, altoDeImagen;
    t_imagen img;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Tonalidad roja ");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen; i++)
    {
       for(j = 0; j < altoDeImagen; j++)
       {
            obtenerPixel(&img, &color, i, j);

            rojo = color.r * 1.5;
            if(rojo > 255)
                rojo = 255;
            color.r = rojo;

            colorearPixel(&img, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "tonalidad-roja");

    guardarImagen(&img, nombreNuevaImagen);

    eliminarImagen(&img);

    return true;
}

bool recortar(char imagen[])
{
    int i, j, anchoDeImagen, altoDeImagen;
    t_imagen img, imgRecortada;
    t_color color;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Recortar \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;

    if(!crearImagen(&imgRecortada, imagenAncho(&img)/2, imagenAlto(&img)/2, 24))
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < anchoDeImagen/2; i++)
    {
       for(j = 0; j < altoDeImagen/2; j++)
       {
            obtenerPixel(&img, &color, i, j);
            colorearPixel(&imgRecortada, &color, i, j);
       }
    }

    declararNombre(nombreNuevaImagen, "recortar");

    guardarImagen(&imgRecortada, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgRecortada);

    return true;
}

bool comodin(char imagen[])
{
    // Para el comodin decidimos hacer un efecto de deteccion de bordes. Para esto vamos a desenfocar la imagen dos veces usando un desenfoque gaussiano, y restar los pixeles de ambas imagenes.
    // El desenfoque gaussiano se obtiene al hacer una suma ponderada de los pixeles al rededor del pixel actual.
    // Los pesos son definidos por una matriz llamada "Kernel" o "nucleo", y sus valores tienen que tener una distribucion normal (normal de Gauss, no de "comun")
    // Como el calculo de esta matriz es complejo, lo vamos a hacer en una funcion a parte y una unica vez.
    int i, j, anchoDeImagen, altoDeImagen;
    int progreso = 0;
    int progresoAnterior = 0;
    t_imagen img, imgAux, imgFinal;
    char nombreNuevaImagen[LARGO_PALABRA] = {};
    double matrizKernel1[MATRIZ_DESENFOQUE][MATRIZ_DESENFOQUE];
    double matrizKernel2[MATRIZ_DESENFOQUE][MATRIZ_DESENFOQUE];

    generarMatrizKernel(matrizKernel1, 1);
    generarMatrizKernel(matrizKernel2, 2);

    printf("- Comodin\t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;
    if(!crearImagen(&imgAux, imagenAncho(&img), imagenAlto(&img), 24))
        return false;
    if(!crearImagen(&imgFinal, imagenAncho(&img), imagenAlto(&img), 24))
        return false;

    puts("");

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < altoDeImagen; i++)
    {
        for(j = 0; j < anchoDeImagen; j++)
        {
            t_color color;
            color = convolucionarMatrizKernel(&img, matrizKernel1, j, i);
            colorearPixel(&imgAux, &color, j, i);
            color = convolucionarMatrizKernel(&img, matrizKernel2, j, i);
            colorearPixel(&imgFinal, &color, j, i);
            progreso = (10. / imagenAlto(&img)) * i;
            if(j == 0 && progreso != progresoAnterior)
            {
                printf("Calculando... %d%%\n", progreso * 10);
                progresoAnterior = progreso;
            }
        }
    }

    printf("\t\t");

    for(i = 0; i < altoDeImagen; i++)
    {
        for(j = 0; j < anchoDeImagen; j++)
        {
            int rojo, verde, azul;
            t_color color1, color2, colorFinal;
            obtenerPixel(&imgAux, &color1, j, i);
            obtenerPixel(&imgFinal, &color2, j, i);

            rojo = (int)color2.r - (int)color1.r;
            azul = (int)color2.b - (int)color1.b;
            verde = (int)color2.g - (int)color1.g;

            if(rojo < 0) rojo = 0;
            if(azul < 0) azul = 0;
            if(verde < 0) verde = 0;

            if(abs(rojo) > 0 || abs(verde) > 0 || abs(azul) > 0)
            {
                colorFinal.r = 255;
                colorFinal.b = 255;
                colorFinal.g = 255;
            }
            else{
                colorFinal.r = 0;
                colorFinal.b = 0;
                colorFinal.g = 0;
            }
            colorearPixel(&imgFinal, &colorFinal, j, i);
        }
    }

    declararNombre(nombreNuevaImagen, "comodin");

    guardarImagen(&imgFinal, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgAux);
    eliminarImagen(&imgFinal);

    return true;
}

bool concatenar(char imagenes[][LARGO_PALABRA], int cantImagenes)
{
    int i, j;
    t_imagen img1, img2, imgResultante;
    t_color color;
    unsigned int maxAncho, altoTotal;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Concatenar \t");

    if(cantImagenes < 2)
    {
        printf("\tNo se puede concatenar, falta una imagen ");
        return false;
    }

    if(cargarImagen(&img1, imagenes[0]) == SIN_MEM)
        return false;
    if(cargarImagen(&img2, imagenes[1]) == SIN_MEM)
        return false;

    if(imagenAncho(&img1) > imagenAncho(&img2))
        maxAncho = imagenAncho(&img1);
    else
        maxAncho = imagenAncho(&img2);

    altoTotal = imagenAlto(&img1) + imagenAlto(&img2);

    if(!crearImagen(&imgResultante, maxAncho, altoTotal, 24))
        return false;

    for(i = 0; i < maxAncho; i++)
    {
        for(j = 0; j < altoTotal; j++)
        {
            if(j < imagenAlto(&img1))
            {
                if(obtenerPixel(&img1, &color, i, j))
                    colorearPixel(&imgResultante, &color, i, j);
                else
                {
                    color.r = 200;
                    color.g = 150;
                    color.b = 100;
                    colorearPixel(&imgResultante, &color, i, j);
                }
            }
            else
            {
                if(obtenerPixel(&img2, &color, i, j - imagenAlto(&img1)))
                    colorearPixel(&imgResultante, &color, i, j);
                else
                {
                    color.r = 200;
                    color.g = 150;
                    color.b = 100;
                    colorearPixel(&imgResultante, &color, i, j);
                }
            }
        }
    }

    declararNombre(nombreNuevaImagen, "concatenar");

    guardarImagen(&imgResultante, nombreNuevaImagen);

    eliminarImagen(&img1);
    eliminarImagen(&img2);
    eliminarImagen(&imgResultante);

    return true;
}

bool achicar(char imagen[])
{
    int i, j, xNuevaIMG = 0, yNuevaIMG = 0, offsetX, offsetY, anchoDeImagen, altoDeImagen;
    t_imagen img, imgAchicada;
    char nombreNuevaImagen[LARGO_PALABRA] = {};

    printf("- Achicar \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;
    if(!crearImagen(&imgAchicada, imagenAncho(&img)/2, imagenAlto(&img)/2, 24))
        return false;

    if(!esPar(imagenAncho(&img)))
        anchoDeImagen = imagenAncho(&img)-1;
    else
        anchoDeImagen = imagenAncho(&img);

    if(!esPar(imagenAlto(&img)))
        altoDeImagen = imagenAlto(&img)-1;
    else
        altoDeImagen = imagenAlto(&img);

    offsetX = imagenAncho(&img) / imagenAncho(&imgAchicada);
    offsetY = imagenAlto(&img) / imagenAlto(&imgAchicada);

    for(i = 0; i < anchoDeImagen; i+=offsetX)
    {
       for(j = 0; j < altoDeImagen; j+=offsetY)
       {
            t_color color;
            obtenerPixel(&img, &color, i, j);
            colorearPixel(&imgAchicada, &color, xNuevaIMG, yNuevaIMG);
            yNuevaIMG++;
       }
       xNuevaIMG++;
       yNuevaIMG = 0;
    }

    declararNombre(nombreNuevaImagen, "achicar");

    guardarImagen(&imgAchicada, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&imgAchicada);

    return true;
}

bool monocromo(char imagen[])
{
    int i, j, suma,  anchoDeImagen, altoDeImagen;
    t_imagen img, img2;
    char nombreNuevaImagen[LARGO_PALABRA] = {};
    t_color color;

    printf("- Monocromo \t");

    if(cargarImagen(&img, imagen) == SIN_MEM)
        return false;
    if(!crearImagen(&img2, imagenAncho(&img), imagenAlto(&img), 1))
        return false;

    anchoDeImagen = imagenAncho(&img);
    altoDeImagen = imagenAlto(&img);

    for(i = 0; i < altoDeImagen; i++)
    {
        for(j = 0; j < anchoDeImagen; j++)
        {
            obtenerPixel(&img, &color, j, i);
            suma = color.r + color.g + color.b;
            colorearBitDeImagen(&img2, (bool)(suma / 3. > 127), j, i);
        }
    }

    declararNombre(nombreNuevaImagen, "monocromo");

    guardarImagen(&img2, nombreNuevaImagen);

    eliminarImagen(&img);
    eliminarImagen(&img2);

    return true;
}

//////////////////////////////////////////////////////////////////////
//FUNCIONES DE UTILIDAD PARA EL COMODIN
void generarMatrizKernel(double mat[][MATRIZ_DESENFOQUE], double desviacionEstandard)
{
    // Este es el calculo de la matriz con distribucion normal que vamos a usar en el comodin.
    // Formula basada en este articulo: https://en.wikipedia.org/wiki/Gaussian_blur
    int i, j;
    int i2, j2; // i y j elevados al cuadrado. Son float para convertir
    int radioMatriz = MATRIZ_DESENFOQUE / 2;
    double exponente;
    double sumaTotal = 0;

    desviacionEstandard *= desviacionEstandard;
    for(i = 0; i < MATRIZ_DESENFOQUE; i++)
    {
        for (j = 0; j < MATRIZ_DESENFOQUE; j++)
        {
            i2 = pow((i - radioMatriz), 2);
            j2 = pow((j - radioMatriz), 2);
            exponente = - (i2 + j2) / (2.0 * desviacionEstandard);
            mat[i][j] = exp(exponente) * (1.0 / (2.0 * M_PI * desviacionEstandard));
            sumaTotal += mat[i][j];
        }
    }

    // Normalizamos la matriz, lo cual aumenta su brillo y nos garantiza que no oscurezca la imagen
    for(i = 0; i < MATRIZ_DESENFOQUE; i++)
    {
        for (j = 0; j < MATRIZ_DESENFOQUE; j++)
        {
            mat[i][j] /= sumaTotal;
            sumaTotal += mat[i][j];
        }
    }
}

t_color convolucionarMatrizKernel(t_imagen* const img, double const mat[][MATRIZ_DESENFOQUE], unsigned int coordX, unsigned int coordY)
{
    // Esta funcion va a tomar retornar un color formado por los pixeles que rodeen la coordenada, basandose en la matriz.
    // De paso, a los pixeles que no existan (al rededor de los bordes) los vamos a tomar como del mismo color que el pixel original
    t_color origen;
    t_color colorAux;
    t_color colorFinal;
    int i, j;
    int radioMatriz = MATRIZ_DESENFOQUE / 2;
    double auxSumaR = 0;
    double auxSumaB = 0;
    double auxSumaG = 0;

    obtenerPixel(img, &origen, coordX, coordY);
    for(i = 0; i < MATRIZ_DESENFOQUE; i++)
    {
        for(j = 0; j < MATRIZ_DESENFOQUE; j++)
        {
            if(!obtenerPixel(img, &colorAux, coordX + i - radioMatriz, coordY + j - radioMatriz))
                colorAux = origen;
            auxSumaR += colorAux.r * mat[i][j];
            auxSumaG += colorAux.g * mat[i][j];
            auxSumaB += colorAux.b * mat[i][j];
        }
    }
    if(auxSumaR > 255) auxSumaR = 255;
    if(auxSumaB > 255) auxSumaB = 255;
    if(auxSumaG > 255) auxSumaG = 255;
    if(auxSumaR < 0) auxSumaR = 0;
    if(auxSumaB < 0) auxSumaB = 0;
    if(auxSumaG < 0) auxSumaG = 0;
    colorFinal.r = auxSumaR;
    colorFinal.g = auxSumaG;
    colorFinal.b = auxSumaB;

    return colorFinal;
}

//////////////////////////////////////////////////////////////////////
//FUNCIONES PARA EL MANEJO DE IMAGENES
int cargarImagen(t_imagen* img, char ruta[])
{
    FILE* f;
    f = fopen(ruta, "rb");
    if(!f)
        exit(ARCHIVO_NO_ENCONTRADO);

    // Tenemos que cargar todos los campos manualmente porque el short deja un padding de 2 bytes, lo que hace que se cargue mal todos los campos que siguen
    fread(&img->encabezado.tipoDeFichero, sizeof(short), 1, f);
    fread(&img->encabezado.tamArchivo, sizeof(int), 1, f);
    fread(&img->encabezado.__reservado, sizeof(int), 1, f);
    fread(&img->encabezado.inicioImagen, sizeof(int), 1, f);
    fread(&img->encabezado.tamCabecera, sizeof(int), 1, f);
    fread(&img->encabezado.ancho, sizeof(int), 1, f);
    fread(&img->encabezado.alto, sizeof(int), 1, f);
    fread(&img->encabezado.numPlanos, sizeof(short), 1, f);
    fread(&img->encabezado.tamPunto, sizeof(short), 1, f);
    fread(&img->encabezado.compresion, sizeof(int), 1, f);
    fread(&img->encabezado.tamImagen, sizeof(int), 1, f);
    fread(&img->encabezado.resHorizontal, sizeof(int), 1, f);
    fread(&img->encabezado.resVertical, sizeof(int), 1, f);
    fread(&img->encabezado.tamTablaDeColor, sizeof(int), 1, f);
    fread(&img->encabezado.contColoresImportantes, sizeof(int), 1, f);

    if(img->encabezado.tamPunto != 24)
    {
        printf("\nError: Solo se soportan archivos de 24 bits por pixel y el archivo seleccionado tiene %hu bits por pixel\n", img->encabezado.tamPunto);
        fclose(f);
        exit(ARCHIVO_INVALIDO);
    }

    fseek(f, img->encabezado.inicioImagen, SEEK_SET);
    img->pixeles = malloc(img->encabezado.tamImagen);

    if(!img->pixeles)
        return SIN_MEM;

    fread(img->pixeles, sizeof(char), img->encabezado.tamImagen, f);

    fclose(f);

    return TODO_OK;
}

unsigned long anchoDeFilaPixelABytes(unsigned long anchoEnPixeles)
{
    // En formato BMP, el ancho de cada fila en bytes se redondea hacia arriba al proximo multiplo de 4
    // Esta operacion divide la cantidad de bytes entre 4, toma el techo, y lo multiplica por 4.
    // Esto deberia redondear al multiplo de 4 mas cercano.
    return ceil((float)(anchoEnPixeles * 3.0) / 4.0) * 4;
}

unsigned long anchoDeFilaPixelABits(unsigned long anchoEnPixeles)
{
    // En formato BMP, el ancho de cada fila en bits se redondea hacia arriba al proximo multiplo de 32
    // Esta operacion divide la cantidad de bytes entre 32, toma el techo, y lo multiplica por 32.
    // Esto deberia redondear al multiplo de 32 mas cercano.
    return ceil((float)(anchoEnPixeles) / 32.0) * 32;
}

int guardarImagen(t_imagen* const img, char ruta[])
{
    FILE* f;
    f = fopen(ruta, "wb");
    if(!f)
        exit(NO_SE_PUEDE_CREAR_ARCHIVO);

    // Tenemos que guardar todos los campos manualmente porque el short deja un padding de 2 bytes, lo que hace que se guarden mal todos los campos que siguen
    fwrite(&img->encabezado.tipoDeFichero, sizeof(short), 1, f);
    fwrite(&img->encabezado.tamArchivo, sizeof(int), 1, f);
    fwrite(&img->encabezado.__reservado, sizeof(int), 1, f);
    fwrite(&img->encabezado.inicioImagen, sizeof(int), 1, f);
    fwrite(&img->encabezado.tamCabecera, sizeof(int), 1, f);
    fwrite(&img->encabezado.ancho, sizeof(int), 1, f);
    fwrite(&img->encabezado.alto, sizeof(int), 1, f);
    fwrite(&img->encabezado.numPlanos, sizeof(short), 1, f);
    fwrite(&img->encabezado.tamPunto, sizeof(short), 1, f);
    fwrite(&img->encabezado.compresion, sizeof(int), 1, f);
    fwrite(&img->encabezado.tamImagen, sizeof(int), 1, f);
    fwrite(&img->encabezado.resHorizontal, sizeof(int), 1, f);
    fwrite(&img->encabezado.resVertical, sizeof(int), 1, f);
    fwrite(&img->encabezado.tamTablaDeColor, sizeof(int), 1, f);
    fwrite(&img->encabezado.contColoresImportantes, sizeof(int), 1, f);

    if(img->encabezado.tamPunto == 1)
    {
        // Color 0 (Marron 60, 30, 0)
        unsigned char r = (unsigned char)0;
        unsigned char g = (unsigned char)30;
        unsigned char b = (unsigned char)60;
        unsigned char a = (unsigned char)0;
        fwrite(&r, 1, 1, f);
        fwrite(&g, 1, 1, f);
        fwrite(&b, 1, 1, f);
        fwrite(&a, 1, 1, f);
        // Color 1 (Amarillo 255, 255, 170)
        r = (unsigned char)170;
        g = (unsigned char)255;
        b = (unsigned char)255;
        fwrite(&r, 1, 1, f);
        fwrite(&g, 1, 1, f);
        fwrite(&b, 1, 1, f);
        fwrite(&a, 1, 1, f);
    }

    fseek(f, img->encabezado.inicioImagen, SEEK_SET);
    fwrite(img->pixeles, sizeof(char), img->encabezado.tamImagen, f);

    fclose(f);

    printf("\t(%s generada con exito)\n", ruta);

    return TODO_OK;
}

void eliminarImagen(t_imagen* img)
{
    if(img->pixeles)
    {
        free(img->pixeles);
        img->pixeles = NULL;
    }
}

bool obtenerPixel(t_imagen* const img, t_color* color, unsigned long coordX, unsigned long coordY)
{
    unsigned long filaAnchoBytes, offset;

    if(img->encabezado.tamPunto != 24)
        return false;
    if(coordX > img->encabezado.ancho || coordY > img->encabezado.alto)
        return false;

    filaAnchoBytes = anchoDeFilaPixelABytes(img->encabezado.ancho);
    offset = 0;
    offset += coordY * filaAnchoBytes;
    offset += coordX * 3;

    if(offset > img->encabezado.tamImagen)
        return false;

    // Las imagenes se guardan como BGR en lugar de RGB
    color->b = img->pixeles[offset];
    color->g = img->pixeles[offset+1];
    color->r = img->pixeles[offset+2];

    return true;
}

bool colorearPixel(t_imagen* img, t_color* const color, unsigned long coordX, unsigned long coordY)
{
    unsigned long filaAnchoBytes, offset;

    if(img->encabezado.tamPunto != 24)
        return false;
    if(coordX > img->encabezado.ancho || coordY > img->encabezado.alto)
        return false;

    filaAnchoBytes = anchoDeFilaPixelABytes(img->encabezado.ancho);
    offset = 0;
    offset += coordY * filaAnchoBytes;
    offset += coordX * 3;

    // Las imagenes se guardan como BGR en lugar de RGB
    img->pixeles[offset] = color->b;
    img->pixeles[offset+1] = color->g;
    img->pixeles[offset+2] = color->r;
    return true;
}

bool colorearBitDeImagen(t_imagen* img, bool valor, unsigned long coordX, unsigned long coordY)
{
    unsigned long filaAnchoBytes, offset;

    if(img->encabezado.tamPunto != 1)
        return 0;
    if(coordX > img->encabezado.ancho || coordY > img->encabezado.alto)
        return 0;

    filaAnchoBytes = anchoDeFilaPixelABits(img->encabezado.ancho);
    offset = 0; // El offset esta en bytes
    offset += coordY * filaAnchoBytes;
    offset += coordX;
    offset /= 8;

    marcarBitDeByte(&img->pixeles[offset], coordX % 8, valor);

    return true;
}

bool crearImagen(t_imagen* img, unsigned long ancho, unsigned long alto, unsigned int profundidad)
{
    int i;
    unsigned long filaAnchoBytes, tamCabecera, offsetPixeles, tamImagen, tamArchivo;
    short tamTablaDeColor;

    if(profundidad != 24 && profundidad != 1)
        return false;

    filaAnchoBytes = anchoDeFilaPixelABytes(ancho);
    tamCabecera = 40; // Esta cabecera es el DIB, sin incluir la primer parte de header
    offsetPixeles = tamCabecera + 14; // 14 bytes del primer header
    tamTablaDeColor = 0;

    if(profundidad == 1)
    {
        filaAnchoBytes = anchoDeFilaPixelABits(ancho) / 8;
        tamTablaDeColor = 2;
        offsetPixeles += tamTablaDeColor * 4; // Cada color ocupa 4 bytes
    }

    tamImagen = filaAnchoBytes * alto;
    tamArchivo = tamCabecera + tamImagen + 14 + (tamTablaDeColor * 4); // La cabecera DIB, la otra cabecera (14 bytes), la tabla de color, y la imagen.

    img->encabezado.tipoDeFichero = 19778; // "BM"
    img->encabezado.tamArchivo = tamArchivo;
    img->encabezado.__reservado = 0;
    img->encabezado.inicioImagen = offsetPixeles;
    // Comienzo del DIB
    img->encabezado.tamCabecera = tamCabecera;
    img->encabezado.ancho = ancho;
    img->encabezado.alto = alto;
    img->encabezado.numPlanos = 1;
    img->encabezado.tamPunto = profundidad;
    img->encabezado.compresion = 0;
    img->encabezado.tamImagen = tamImagen;
    // Ambas resoluciones las dejamos en un valor por defecto. Para los fines de este TP no afecta, ya que esto es para el tamaño de impresion, lo cual no nos interesa
    // En https://stackoverflow.com/questions/17550545/bmp-image-header-bixpelspermeter se menciona que en Windows lo tradicional son 92 DPI (Dots Per Inch), que equivale a aproximadamente 3779 DPM (Dots Per Meter)
    img->encabezado.resHorizontal = 3779;
    img->encabezado.resVertical = 3779;
    img->encabezado.tamTablaDeColor = tamTablaDeColor;
    img->encabezado.contColoresImportantes = 0;

    img->pixeles = malloc(tamImagen);

    if(!img->pixeles)
        return false;

    for(i = 0; i < tamImagen; i++)
        img->pixeles[i] = 0;

    return true;
}

unsigned int imagenAlto(t_imagen* const img)
{
    if(!img)
        return 0;
    return img->encabezado.alto;
}

unsigned int imagenAncho(t_imagen* const img)
{
    if(!img)
        return 0;
    return img->encabezado.ancho;
}

bool esPar(unsigned int numero)
{
    if(!numero)
        return true;
    if(!(numero % 2))
        return true;
    return false;
}

void marcarBitDeByte(unsigned char* byte, int pos, bool valor)
{
    unsigned char mascara;

    pos %= 8;
    mascara = 128 >> pos;

    if(valor)
        *byte = *byte | mascara;
    else
        *byte = *byte & ~mascara;
}

//////////////////////////////////////////////////////////////////////
//FUNCIONES ACTUALMENTE EN DESUSO PERO QUE EN UN FUTURO NOS PODRIAN SERVIR PARA LEER IMAGENES DE 1 BIT DE PROFUNDIDAD
bool obtenerBitDeImagen(t_imagen* const img, bool* valor, unsigned long coordX, unsigned long coordY)
{
    unsigned long filaAnchoBytes, offset;

    if(img->encabezado.tamPunto != 1)
        return false;
    if(coordX > img->encabezado.ancho || coordY > img->encabezado.alto)
        return false;

    filaAnchoBytes = anchoDeFilaPixelABits(img->encabezado.ancho);
    offset = 0; // El offset esta en bytes
    offset += coordY * filaAnchoBytes;
    offset += coordX;
    offset /= 8;

    *valor = obtenerBitDeByte(img->pixeles[offset], coordX % 8);

    return true;
}

bool obtenerBitDeByte(unsigned char byte, int pos)
{
    unsigned char mascara;

    pos %= 8;
    mascara = 128 >> pos;

    return (bool) byte & mascara;
}

//////////////////////////////////////////////////////////////////////
//FUNCIONES DE UTILIDAD PARA TRABAJAR CON CARACTERES Y CADENAS
void obtenerPalabra(int comienzoCadena, int finCadena, char cadenaOrigen[], char cadenaDestino[])
{
    int i, index = 0;

    for(i = comienzoCadena; i < finCadena; i++)
    {
        cadenaDestino[index] = cadenaOrigen[i];
        index++;
    }

    cadenaDestino[index] = '\0';
}

// Las funciones de string.h para esta tarea no permiten seleccionar desde dónde buscar
int encontrarCaracter(char argv[], int comienzoCadena, char caracter)
{
    int i;

    for(i = comienzoCadena; i < strlen(argv); i++)
    {
        if(argv[i] == caracter)
            return i;
    }
    return -1;
}

void declararNombre(char nombreNuevaImagen[], char mod[])
{
    strcat(nombreNuevaImagen, "estudiante");
    strcat(nombreNuevaImagen, "_");
    strcat(nombreNuevaImagen, mod);
    strcat(nombreNuevaImagen, ".bmp");
}
