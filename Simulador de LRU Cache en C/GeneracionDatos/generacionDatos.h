#ifndef GENERACIONDATOS_H_INCLUDED
#define GENERACIONDATOS_H_INCLUDED

void generarPosteos(const char* nombreArchivo);
void generarFeedsAltaDispersion(const char* nombreArchivo);
void generarFeedsBajaDispersion(const char* nombreArchivo, int numPosteosPopulares);
void generarTextoAleatorio(char* texto, int longitud);
void mostrarContenidoArchivo(const char* rutaArchivo, const char* tipoEstructura);

#endif // GENERACIONDATOS_H_INCLUDED
