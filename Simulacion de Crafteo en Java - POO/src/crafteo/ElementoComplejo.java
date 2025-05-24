package crafteo;

import java.util.HashMap;
import java.util.Map;

public class ElementoComplejo extends Elemento {
    private String accion;
    private Map<String, Elemento[]> subelementos;

    public ElementoComplejo(String nombre, int tiempo, String accion) {
        super(nombre, tiempo);
        this.accion = accion;
        this.subelementos = new HashMap<>();
    }

    @Override
    public Map<String, Elemento[]> subelementos() {
        return subelementos;
    }

    @Override
    public void agregarAccion(Map<String, Elemento[]> acciones) {
        subelementos.putAll(acciones);
    }

    public String getAccion() {
        return accion;
    }
}

