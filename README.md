# 🎮 Juego Educativo de Plataformas

## 📋 Descripción
Juego de plataformas educativo desarrollado en C++ con SDL2. El juego incluye dos niveles temáticos: matemáticas (valor absoluto) e historia (Antigua Grecia).

## 🚀 Estado Actual del Desarrollo

### ✅ Completado
- **Configuración base del proyecto**
  - Estructura de archivos organizada
  - Makefile funcional
  - Inicialización de SDL2

- **Sistema de juego principal**
  - Clase Juego con gestión de estados
  - Loop principal del juego
  - Manejo de eventos básico
  - Menú principal
  - Pantalla final

- **Mecánicas básicas implementadas**
  - Clase Jugador con física completa
    - Movimiento horizontal (flechas izquierda/derecha)
    - Salto (flecha arriba o espacio)
    - Gravedad y colisiones
    - Sistema de fricción
  - Clase Plataforma con detección de colisiones
  - Clase Nivel1 completamente funcional
    - 7 plataformas distribuidas verticalmente
    - Sistema de colisiones jugador-plataforma
    - Detección de meta (objetivo del nivel)
    - Reinicio automático al morir
    - Reinicio manual con tecla 'R'

### 🎮 Controles Actuales
- **Menú Principal:** ESPACIO para comenzar
- **En el juego:**
  - ⬅️➡️ Flechas: Movimiento horizontal
  - ⬆️ Flecha o ESPACIO: Salto
  - R: Reiniciar nivel
- **Pantalla Final:** ESC para salir

### 🎯 Nivel 1: "El Valle del Terror Absoluto"
- **Tema:** Matemáticas - Valor Absoluto
- **Objetivo:** Llegar a la plataforma dorada en la parte superior
- **Mecánicas:** Saltar entre plataformas evitando caer
- **Diseño:** 7 plataformas en disposición vertical ascendente

## 🛠️ Compilación y Ejecución

### Requisitos
- g++ con soporte C++11
- SDL2 development libraries

### Instalación de dependencias (Ubuntu/Debian)
```bash
make install-deps
```

### Compilar
```bash
make
```

### Ejecutar
```bash
make run
# o directamente:
./juego_educativo
```

### Limpiar archivos compilados
```bash
make clean
```

## 📁 Estructura del Proyecto
```
game-project/
├── src/
│   ├── main.cpp           # Punto de entrada del programa
│   ├── Juego.h/.cpp       # Clase principal del juego
│   ├── Jugador.h/.cpp     # Mecánicas del personaje
│   ├── Plataforma.h/.cpp  # Plataformas del nivel
│   ├── Nivel1.h/.cpp      # Lógica específica del Nivel 1
│   └── [más clases...]
├── Makefile               # Sistema de compilación
├── README.md              # Este archivo
└── requerimientos.md      # Plan detallado del proyecto
```

## 🔄 Próximos Pasos
1. **Elementos adicionales del juego:**
   - Clase Enemigo (rectángulos rojos que se mueven)
   - Clase CuboEducativo (información al colisionar)
   - Sistema de paneles educativos

2. **Sistema educativo:**
   - Panel lateral con contenido de matemáticas
   - Sistema de preguntas al completar nivel
   - Archivos de contenido educativo

3. **Nivel 2:**
   - Implementación del segundo nivel (Historia - Antigua Grecia)
   - Nuevas mecánicas y diseño de plataformas

4. **Mejoras visuales:**
   - Efectos visuales adicionales
   - Mejor feedback visual
   - Animaciones simples

## 🎨 Estilo Visual
- **Estilo:** Pixel Art Retro Simplificado
- **Colores:** Paleta limitada de 12-16 colores
- **Elementos:** Formas geométricas (rectángulos) con bordes definidos
- **Jugador:** Rectángulo azul (32x32 px)
- **Plataformas:** Rectángulos verdes con decoración
- **Meta:** Rectángulo dorado

## 👨‍💻 Desarrollo
- **Lenguaje:** C++11
- **Biblioteca gráfica:** SDL2
- **Arquitectura:** Orientada a objetos con separación clara de responsabilidades
- **Comentarios:** En español para mejor legibilidad del código

---
*Desarrollado como proyecto educativo de programación en C++ con SDL2*
