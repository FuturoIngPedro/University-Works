package crafteo;

import java.util.List;

public class Receta {
    private Elemento producto;
    private List<IngredienteDeReceta> ingredientes;
    private int cantidadResultado;

    public Receta(Elemento producto, List<IngredienteDeReceta> ingredientes, int cantidadResultado) {
        this.producto = producto;
        this.ingredientes = ingredientes;
        this.cantidadResultado = cantidadResultado;
    }

    public Elemento getProducto() {
        return producto;
    }

    public List<IngredienteDeReceta> getIngredientes() {
        return ingredientes;
    }

    public int getCantidadResultado() {
        return cantidadResultado;
    }
}
