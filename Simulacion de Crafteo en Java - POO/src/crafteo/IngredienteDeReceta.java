package crafteo;

public class IngredienteDeReceta {
    private Elemento elemento;
    private int cantidad;

    public IngredienteDeReceta(Elemento elemento, int cantidad) {
        this.elemento = elemento;
        this.cantidad = cantidad;
    }

    public Elemento getElemento() {
        return elemento;
    }

    public int getCantidad() {
        return cantidad;
    }
}
