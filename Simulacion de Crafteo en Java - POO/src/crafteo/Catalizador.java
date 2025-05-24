package crafteo;

import java.util.HashMap;
import java.util.Map;

public class Catalizador extends Elemento {
    private String accion;
    private String tipo;
    private Map<String, Elemento[]> subelementos;

    public Catalizador(String nombre, int tiempo, String accion, String tipo) {
        super(nombre, tiempo);
        this.accion = accion;
        this.tipo = tipo;
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

    public String getTipo() {
        return tipo;
    }
}
