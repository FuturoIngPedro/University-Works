package crafteo;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.databind.*;

public class Inventario {
    private Map<String, Integer> elementos;

    public Inventario() {
        elementos = new HashMap<>();
    }

    public void agregarElemento(String nombre, int cantidad) {
        elementos.put(nombre, elementos.getOrDefault(nombre, 0) + cantidad);
    }

    public boolean tieneElemento(String nombre, int cantidadRequerida) {
        return elementos.getOrDefault(nombre, 0) >= cantidadRequerida;
    }

    public int obtenerCantidad(String nombre) {
        return elementos.getOrDefault(nombre, 0);
    }

    public Map<String, Integer> getElementos() {
        return elementos;
    }

    public void consumirElemento(String nombre, int cantidad) {
        if (!tieneElemento(nombre, cantidad)) return;
        elementos.put(nombre, elementos.get(nombre) - cantidad);
    }

    public void mostrarInventario() {
        System.out.println("Inventario actual:");
        elementos.forEach((k, v) -> System.out.println(k + ": " + v));
    }
    
    public void guardarInventarioComoJSON(String rutaArchivo) {
        ObjectMapper mapper = new ObjectMapper();
        try {
            mapper.writerWithDefaultPrettyPrinter().writeValue(new File(rutaArchivo), elementos);
            System.out.println("Inventario final guardado en " + rutaArchivo);
        } catch (IOException e) {
            System.err.println("Error al guardar inventario final: " + e.getMessage());
        }
    }
}
