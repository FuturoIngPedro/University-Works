#ifndef FUNCIONES_ESTUDIANTE_H_INCLUDED
#define FUNCIONES_ESTUDIANTE_H_INCLUDED

#include<stdbool.h>

#define TODO_OK 0
#define ARCHIVO_NO_ENCONTRADO 10
#define NO_SE_PUEDE_CREAR_ARCHIVO 20
#define ARCHIVO_INVALIDO 30
#define SIN_MEM 40

#define MATRIZ_DESENFOQUE 9
#define LARGO_PALABRA 100
#define MAX_IMAGENES 2

#define COMANDO_NEGATIVO    1
#define COMANDO_ROJO        (1 << 1)
#define COMANDO_AZUL        (1 << 2)
#define COMANDO_VERDE       (1 << 3)
#define COMANDO_GRIS        (1 << 4)
#define COMANDO_A_CONTRASTE (1 << 5)
#define COMANDO_R_CONTRASTE (1 << 6)
#define COMANDO_ROTAR_D     (1 << 7)
#define COMANDO_ROTAR_I     (1 << 8)
#define COMANDO_ACHICAR     (1 << 9)
#define COMANDO_RECORTAR    (1 << 10)
#define COMANDO_MONOCROMO   (1 << 11)
#define COMANDO_COMODIN     (1 << 12)
#define COMANDO_CONCATENAR  (1 << 13)
#define COMANDO_PIXELAR     (1 << 14)
#define COMANDO_ROTAR_180   (1 << 15)

typedef struct {
    unsigned short int tipoDeFichero;
    unsigned int tamArchivo;
    unsigned int __reservado; // Este campo no va a ser utilizado, pero necesito dejar 4 bytes entre los otros campos
    unsigned int inicioImagen;
    // Lo de arriba es el header del archivo, lo ed abajo es el DIB: https://en.wikipedia.org/wiki/BMP_file_format
    unsigned int tamCabecera;
    unsigned int ancho;
    unsigned int alto;
    // Los siguientes tres campos no se usan directamente, pero es informaci�n que el formato necesita, y por lo tanto los tenemos que guardar
    unsigned short int numPlanos;
    unsigned short int tamPunto;
    unsigned int compresion;
    unsigned int tamImagen;
    unsigned int resHorizontal;
    unsigned int resVertical;
    unsigned int tamTablaDeColor;
    unsigned int contColoresImportantes;
}t_encabezado;

typedef struct {
    t_encabezado encabezado;
    unsigned char* pixeles;
}t_imagen;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}t_color;

//FUNCIONES PRINCIPALES
int solucion(int argc, char* argv[]);
void procesarArgumentos(int argc, char* argv[]);
int buscarImagenes(int argc, char* argv[], char imagenes[][LARGO_PALABRA]);
unsigned short int buscarComandos(int argc, char* argv[]);
void realizarModificaciones(unsigned short int comandos, char imagenes[][LARGO_PALABRA], int cantImagenes);

//FUNCIONES DE UTILIDAD PARA EL COMODIN
void generarMatrizKernel(double mat[][MATRIZ_DESENFOQUE], double desviacionEstandard);
t_color convolucionarMatrizKernel(t_imagen* const img, double const mat[][MATRIZ_DESENFOQUE], unsigned int coordX, unsigned int coordY);

//FUNCIONES DE UTILIDAD PARA TRABAJAR CON CARACTERES Y CADENAS
int encontrarCaracter(char argv[], int comienzoCadena,char caracter);
void obtenerPalabra(int comienzoCadena, int finCadena, char cadenaOrigen[], char cadenaDestino[]);
void declararNombre(char nombreNuevaImagen[], char mod[]);

//FUNCIONES PARA LAS MODIFICACIONES
bool negativo(char imagen[]);
bool rotarDerecha(char imagen[]);
bool rotarIzquierda(char imagen[]);
bool escalaGrises(char imagen[]);
bool aumentarContraste(char imagen[]);
bool reducirContraste(char imagen[]);
bool tonalidadAzul(char imagen[]);
bool tonalidadVerde(char imagen[]);
bool tonalidadRoja(char imagen[]);
bool recortar(char imagen[]);
bool comodin(char imagen[]);
bool concatenar(char imagenes[][LARGO_PALABRA], int cantImagenes);
bool achicar(char imagen[]);
bool monocromo(char imagen[]);

bool pixelar(char imagen[]);
bool rotar180(char imagen[]);

//FUNCIONES PARA EL MANEJO DE IMAGENES
int cargarImagen(t_imagen* img, char ruta[]);
int guardarImagen(t_imagen* img, char ruta[]);
bool crearImagen(t_imagen* img, unsigned long ancho, unsigned long alto, unsigned int profundidad);
unsigned long anchoDeFilaPixelABytes(unsigned long anchoEnPixeles);
unsigned long anchoDeFilaPixelABits(unsigned long anchoEnPixeles);
void eliminarImagen(t_imagen* img);
bool obtenerPixel(t_imagen* const img, t_color* color, unsigned long coordX, unsigned long coordY);
bool colorearPixel(t_imagen* img, t_color* const color, unsigned long coordX, unsigned long coordY);
bool colorearBitDeImagen(t_imagen* img, bool valor, unsigned long coordX, unsigned long coordY);
void marcarBitDeByte(unsigned char* byte, int pos, bool valor);
bool esPar(unsigned int numero);

bool obtenerBitDeImagen(t_imagen* const img, bool* valor, unsigned long coordX, unsigned long coordY);
bool obtenerBitDeByte(unsigned char byte, int pos);
//Creo estas funciones para encapsular y no tener que tocar las propiedades directamente.
unsigned int imagenAlto(t_imagen* const img);
unsigned int imagenAncho(t_imagen* const img);


#endif // FUNCIONES_ESTUDIANTE_H_INCLUDED
