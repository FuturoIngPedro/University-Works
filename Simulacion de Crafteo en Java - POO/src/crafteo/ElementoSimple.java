package crafteo;

import java.util.Collections;
import java.util.Map;

public class ElementoSimple extends Elemento {
    private String accion;

    public ElementoSimple(String nombre, int tiempo, String accion) {
        super(nombre, tiempo);
        this.accion = accion;
    }

    @Override
    public Map<String, Elemento[]> subelementos() {
        return Collections.emptyMap();
    }

    @Override
    public void agregarAccion(Map<String, Elemento[]> acciones) {
        // No aplica a simples
    }

    public String getAccion() {
        return accion;
    }
}

