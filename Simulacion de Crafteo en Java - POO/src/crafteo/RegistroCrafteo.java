package crafteo;

import java.time.LocalDateTime;
import java.util.List;

public class RegistroCrafteo {
    private Elemento elementoCrafteado;
    private List<IngredienteDeReceta> ingredientesUsados;
    private int cantidad;
    private int tiempoTotal;
    private LocalDateTime fecha;

    public RegistroCrafteo(Elemento elementoCrafteado, List<IngredienteDeReceta> ingredientesUsados, int cantidad, int tiempoTotal) {
        this.elementoCrafteado = elementoCrafteado;
        this.ingredientesUsados = ingredientesUsados;
        this.cantidad = cantidad;
        this.tiempoTotal = tiempoTotal;
        this.fecha = LocalDateTime.now();
    }

    public Elemento getElementoCrafteado() {
        return elementoCrafteado;
    }

    public List<IngredienteDeReceta> getIngredientesUsados() {
        return ingredientesUsados;
    }

    public int getCantidad() {
        return cantidad;
    }

    public int getTiempoTotal() {
        return tiempoTotal;
    }

    public LocalDateTime getFecha() {
        return fecha;
    }

    @Override
    public String toString() {
        return "Crafteo de " + cantidad + "x " + elementoCrafteado.getNombre() +
               " en " + tiempoTotal + " minutos, el " + fecha;
    }
}
