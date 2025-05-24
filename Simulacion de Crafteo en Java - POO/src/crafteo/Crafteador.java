package crafteo;

import java.util.*;

public class Crafteador {
    private List<Receta> recetasDisponibles;
    private List<RegistroCrafteo> historial;

    public Crafteador(List<Receta> recetasDisponibles) {
        this.recetasDisponibles = recetasDisponibles;
        this.historial = new ArrayList<>();
    }

    public List<RegistroCrafteo> getHistorial() {
        return historial;
    }

    public Optional<Receta> obtenerRecetaDe(String nombreProducto) {
        return recetasDisponibles.stream()
                .filter(r -> r.getProducto().getNombre().equals(nombreProducto))
                .findFirst();
    }

    public boolean puedeCraftear(String nombreProducto, Inventario inventario) {
        Optional<Receta> receta = obtenerRecetaDe(nombreProducto);
        if (receta.isEmpty()) return false;

        for (IngredienteDeReceta ing : receta.get().getIngredientes()) {
            if (!inventario.tieneElemento(ing.getElemento().getNombre(), ing.getCantidad())) {
                return false;
            }
        }
        return true;
    }

    public int calcularTiempoTotal(String nombreProducto) {
        Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);
        if (recetaOpt.isEmpty()) return 0;

        int tiempoTotal = recetaOpt.get().getProducto().getTiempo();
        for (IngredienteDeReceta ing : recetaOpt.get().getIngredientes()) {
            tiempoTotal += ing.getElemento().getTiempo() * ing.getCantidad();
        }

        return tiempoTotal;
    }

    public boolean realizarCrafteo(String nombreProducto, Inventario inventario) {
        Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);
        if (recetaOpt.isEmpty()) return false;

        Receta receta = recetaOpt.get();

        if (!puedeCraftear(nombreProducto, inventario)) return false;

        // Consumir del inventario
        for (IngredienteDeReceta ing : receta.getIngredientes()) {
            inventario.consumirElemento(ing.getElemento().getNombre(), ing.getCantidad());
        }

        // Agregar resultado
        inventario.agregarElemento(receta.getProducto().getNombre(), receta.getCantidadResultado());

        // Registrar crafteo
        int tiempo = calcularTiempoTotal(nombreProducto);
        RegistroCrafteo registro = new RegistroCrafteo(receta.getProducto(), receta.getIngredientes(), receta.getCantidadResultado(), tiempo);
        historial.add(registro);

        return true;
    }

    public void mostrarHistorial() {
        if (historial.isEmpty()) {
            System.out.println("No se ha realizado ningún crafteo aún.");
        } else {
            System.out.println("Historial de crafteos:");
            historial.forEach(System.out::println);
        }
    }
    
    public void mostrarArbol(String nombreProducto, int nivel) {
        Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);
        if (recetaOpt.isEmpty()) {
            System.out.println("  ".repeat(nivel) + "🔹 " + nombreProducto + " (elemento básico)");
            return;
        }

        Receta receta = recetaOpt.get();
        System.out.println("  ".repeat(nivel) + "🔧 " + nombreProducto + " (" + receta.getCantidadResultado() + " unidad/es, " + receta.getProducto().getTiempo() + " min)");

        for (IngredienteDeReceta ing : receta.getIngredientes()) {
            mostrarArbol(ing.getElemento().getNombre(), nivel + 1);
        }
    }
   
    
    public Map<String, Integer> calcularIngredientesDesdeCero(String nombreProducto, Inventario inventarioOriginal) {
        Map<String, Integer> ingredientesBasicos = new HashMap<>();

        // Copiamos el inventario original para simular consumo
        Inventario copiaInventario = new Inventario();
        inventarioOriginal.getElementos().forEach(copiaInventario::agregarElemento);

        calcularRecursivo(nombreProducto, ingredientesBasicos, 1, copiaInventario);
        return ingredientesBasicos;
    }


    private void calcularRecursivo(String nombreProducto, Map<String, Integer> acumulador, int multiplicador, Inventario inventario) {
    	Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);

    	if (recetaOpt.isEmpty()) {
    	    acumulador.put(nombreProducto, acumulador.getOrDefault(nombreProducto, 0) + multiplicador);
    	    return;
    	}

    	// Simular consumo desde inventario
    	int disponibles = inventario.obtenerCantidad(nombreProducto);
    	int aConsumir = Math.min(disponibles, multiplicador);
    	if (aConsumir > 0) {
    	    inventario.consumirElemento(nombreProducto, aConsumir);
    	}

    	int faltan = multiplicador - aConsumir;
    	if (faltan == 0) return; // ya cubierto con inventario

    	// Descomponer lo que falta
    	Receta receta = recetaOpt.get();
    	for (IngredienteDeReceta ing : receta.getIngredientes()) {
    	    calcularRecursivo(
    	        ing.getElemento().getNombre(),
    	        acumulador,
    	        ing.getCantidad() * faltan,
    	        inventario
    	    );
    	}
    }

    public Map<String, Integer> ingredientesFaltantes(String nombreProducto, Inventario inventario) {
        Map<String, Integer> faltantes = new HashMap<>();

        Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);
        if (recetaOpt.isEmpty()) return faltantes;

        for (IngredienteDeReceta ing : recetaOpt.get().getIngredientes()) {
            String nombre = ing.getElemento().getNombre();
            int cantidadNecesaria = ing.getCantidad();
            int cantidadInventario = inventario.obtenerCantidad(nombre);

            if (cantidadInventario < cantidadNecesaria) {
                faltantes.put(nombre, cantidadNecesaria - cantidadInventario);
            }
        }

        return faltantes;
    }
    
    public Map<String, Integer> ingredientesFaltantesDesdeCero(String nombreProducto, Inventario inventario) {
        // Ahora le pasamos el inventario al nuevo método
        Map<String, Integer> necesarios = calcularIngredientesDesdeCero(nombreProducto, inventario);
        Map<String, Integer> faltantes = new HashMap<>();

        for (Map.Entry<String, Integer> entrada : necesarios.entrySet()) {
            String nombre = entrada.getKey();
            int requerido = entrada.getValue();
            int disponible = inventario.obtenerCantidad(nombre);

            int falta = requerido - disponible;
            if (falta > 0) {
                faltantes.put(nombre, falta);
            }
        }

        return faltantes;
    }
    
    public int cantidadMaximaCrafteable(String nombreProducto, Inventario inventarioOriginal) {
        Optional<Receta> recetaOpt = obtenerRecetaDe(nombreProducto);
        if (recetaOpt.isEmpty()) return 0;

        Receta receta = recetaOpt.get();
        int max = Integer.MAX_VALUE;

        // Clonamos el inventario para no modificar el original
        Inventario copia = new Inventario();
        inventarioOriginal.getElementos().forEach(copia::agregarElemento);

        // Ingredientes básicos necesarios para UNA ejecución de la receta
        Map<String, Integer> necesarios = calcularIngredientesDesdeCero(nombreProducto, new Inventario());

        for (Map.Entry<String, Integer> entrada : necesarios.entrySet()) {
            String nombre = entrada.getKey();
            int requerido = entrada.getValue();
            int disponible = copia.obtenerCantidad(nombre);

            if (requerido == 0) continue;

            int posible = disponible / requerido;
            max = Math.min(max, posible);
        }

        // Multiplicamos por el resultado real de la receta
        return max * receta.getCantidadResultado();
    }


}
