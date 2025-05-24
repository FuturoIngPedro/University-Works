package crafteo;

import java.util.List;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        try {
            // 1. Cargar datos desde JSON
            LectorJSON lector = new LectorJSON();
            List<Receta> recetas = lector.cargarRecetas("data/recetas.json");
            Inventario inventario = lector.cargarInventario("data/inventario.json");

            // 2. Mostrar inventario inicial
            System.out.println("📦 Inventario inicial:");
            inventario.mostrarInventario();

            // 3. Crear el crafteador
            Crafteador crafteador = new Crafteador(recetas);

            // 4. Intentar craftear "antorcha"
            String objeto = "antorcha";
            if (crafteador.puedeCraftear(objeto, inventario)) {
                System.out.println("\n✅ Se puede craftear " + objeto + ", crafteando...");
                crafteador.realizarCrafteo(objeto, inventario);
            } else {
                System.out.println("\n❌ No se puede craftear " + objeto + ".");
            }
            
            if (crafteador.puedeCraftear(objeto, inventario)) {
                System.out.println("\n✅ Se puede craftear " + objeto + ", crafteando...");
                crafteador.realizarCrafteo(objeto, inventario);
            } else {
                System.out.println("\n❌ No se puede craftear " + objeto + ".");
            }

            // 5. Mostrar inventario actualizado
            System.out.println("\n📦 Inventario después del crafteo:");
            inventario.mostrarInventario();

            // 6. Mostrar historial
            System.out.println("\n🕘 Historial:");
            for (RegistroCrafteo reg : crafteador.getHistorial()) {
                System.out.println(reg);
            }

            // 7. Arbol de crafteo de espada
            
            System.out.println("\n🌳 Árbol de crafteo para 'espada':");
            crafteador.mostrarArbol("espada", 0);
            
            // 8. Ingredientes basicos espada
            System.out.println("\n📋 Ingredientes básicos para craftear 'espada' desde cero:");
            Map<String, Integer> ingredientes = crafteador.calcularIngredientesDesdeCero("espada", inventario);
            ingredientes.forEach((nombre, cantidad) -> 
                System.out.println("- " + cantidad + "x " + nombre));
            
            // 9. ¿Que me falta para craftear (nivel 1)?
            System.out.println("\n🧮 Ingredientes faltantes para craftear 'espada':");
            Map<String, Integer> faltantes = crafteador.ingredientesFaltantes("espada", inventario);

            if (faltantes.isEmpty()) {
                System.out.println("✔️ Tenés todo lo necesario.");
            } else {
                faltantes.forEach((nombre, cantidad) ->
                    System.out.println("- Faltan " + cantidad + "x " + nombre));
            }

            // 10. ¿Que me falta para craftear (desde 0)?
            System.out.println("\n🧮 Ingredientes faltantes para craftear 'espada' desde cero:");
            Map<String, Integer> faltantesTotales = crafteador.ingredientesFaltantesDesdeCero("espada", inventario);

            if (faltantesTotales.isEmpty()) {
                System.out.println("✔️ Tenés todo lo necesario (desde cero).");
            } else {
                faltantesTotales.forEach((nombre, cantidad) ->
                    System.out.println("- Faltan " + cantidad + "x " + nombre));
            }
            
            // 11. ¿Cuántas unidades puedo craftear?
            int cantidad = crafteador.cantidadMaximaCrafteable("antorcha", inventario);
            System.out.println("\n🔢 Con lo que tengo, puedo craftear " + cantidad + " antorcha/s.");

            // 12. Guardar inventario final como inventario-out.json
            inventario.guardarInventarioComoJSON("data/inventario-out.json");


        } catch (Exception e) {
            System.err.println("❌ Error al ejecutar el programa: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
