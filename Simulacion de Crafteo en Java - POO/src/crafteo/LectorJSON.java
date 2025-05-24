package crafteo;

import com.fasterxml.jackson.databind.*;
import com.fasterxml.jackson.core.type.TypeReference;

import java.io.File;
import java.util.*;

public class LectorJSON {
    private ObjectMapper mapper;

    public LectorJSON() {
        mapper = new ObjectMapper();
    }

    public List<Receta> cargarRecetas(String rutaArchivo) throws Exception {
        List<Map<String, Object>> datos = mapper.readValue(
            new File(rutaArchivo),
            new TypeReference<List<Map<String, Object>>>() {}
        );

        List<Receta> recetas = new ArrayList<>();

        for (Map<String, Object> recetaRaw : datos) {
            String nombreProducto = (String) recetaRaw.get("producto");
            int tiempo = (Integer) recetaRaw.get("tiempo");
            int cantidad = (Integer) recetaRaw.get("cantidad");

            Elemento producto = new ElementoComplejo(nombreProducto, tiempo, "crafteado");
            
            @SuppressWarnings("unchecked")
            List<Map<String, Object>> ingredientesRaw = (List<Map<String, Object>>) recetaRaw.get("ingredientes");
            List<IngredienteDeReceta> ingredientes = new ArrayList<>();

            for (Map<String, Object> ingr : ingredientesRaw) {
                String nombreIng = (String) ingr.get("nombre");
                int cant = (Integer) ingr.get("cantidad");

                Elemento e = new ElementoSimple(nombreIng, 1, "recolectado");
                ingredientes.add(new IngredienteDeReceta(e, cant));
            }

            recetas.add(new Receta(producto, ingredientes, cantidad));
        }

        return recetas;
    }

    public Inventario cargarInventario(String rutaArchivo) throws Exception {
        Map<String, Integer> datos = mapper.readValue(
            new File(rutaArchivo),
            new TypeReference<Map<String, Integer>>() {}
        );

        Inventario inv = new Inventario();
        datos.forEach(inv::agregarElemento);
        return inv;
    }
}
