# 🛠️ Simulador de Crafteo

Este proyecto implementa un sistema de crafteo inspirado en mecánicas de videojuegos. Permite gestionar recetas, descomponer ingredientes, verificar inventario, realizar crafteos y registrar historial de acciones.

> Trabajo Práctico N°2 - Paradigmas de Programación Orientada a Objetos  
> Universidad Nacional de La Matanza (UNLaM)

---

## 🚀 Tecnologías

- Java 21
- Maven
- Jackson (manejo de JSON)
- JUnit 5 (tests automatizados)

---

## 📁 Estructura

```

simulador\_crafteo/
├── src/                → Código fuente Java
├── data/               → Archivos JSON con recetas e inventario
├── pom.xml             → Archivo de configuración Maven
├── README.md           → Este archivo
└── .gitignore          → Exclusiones para Git

````

---

## 📦 Archivos de entrada

### `data/recetas.json`

Define las recetas de crafteo. Ejemplo:

```json
{
  "producto": "espada",
  "tiempo": 10,
  "cantidad": 1,
  "ingredientes": [
    { "nombre": "hierro", "cantidad": 3 },
    { "nombre": "baston", "cantidad": 1 }
  ]
}
````

### `data/inventario.json`

Define el inventario inicial del jugador:

```json
{
  "madera": 10,
  "carbon": 5,
  "hierro": 3,
  "baston": 1
}
```

---

## ✅ Funcionalidades

* Mostrar qué se necesita para craftear un objeto
* Descomponer ingredientes hasta elementos básicos
* Verificar qué falta según inventario
* Ejecutar crafteo y actualizar inventario
* Calcular tiempos totales
* Registrar historial de crafteos
* Exportar inventario final (`inventario-out.json`)
* Mostrar árbol de crafteo (bonus)

---

## ▶️ Cómo correr

1. Asegurate de tener Maven instalado.
2. Abrí consola en la raíz del proyecto.
3. Ejecutá:

```bash
mvn clean compile exec:java -Dexec.mainClass="crafteo.main.Main"
```

> Si usás Eclipse, simplemente corré la clase `Main.java`.

---

## 🧪 Tests

Los tests se encuentran en `src/test/java/`. Para ejecutarlos:

```bash
mvn test
```

---

## 👨‍💻 Integrantes

* Pedro Melissari
* \[Agregá acá los nombres de tus compañeros]

---

## 📘 Licencia

Uso académico. Proyecto educativo sin fines de lucro.

```
