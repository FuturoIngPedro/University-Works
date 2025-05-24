package crafteo;

import java.util.Map;

public abstract class Elemento {
    protected String nombre;
    protected int tiempo; // en minutos

    public Elemento(String nombre, int tiempo) {
        this.nombre = nombre;
        this.tiempo = tiempo;
    }

    public String getNombre() {
        return nombre;
    }

    public int getTiempo() {
        return tiempo;
    }

    public abstract Map<String, Elemento[]> subelementos();
    public abstract void agregarAccion(Map<String, Elemento[]> acciones);
}
