# 🎮 Juego Educativo de Plataformas

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![SDL2](https://img.shields.io/badge/SDL2-2.0-green.svg)
![License](https://img.shields.io/badge/License-Educational-yellow.svg)
![Status](https://img.shields.io/badge/Status-En%20Desarrollo-orange.svg)

*Un juego de plataformas educativo que combina diversión y aprendizaje*

</div>

---

## 📑 Tabla de Contenidos

- [📋 Descripción](#-descripción)
- [🚀 Inicio Rápido](#-inicio-rápido)
  - [📋 Requisitos Previos](#-requisitos-previos)
  - [⬇️ Instalación](#️-instalación)
  - [🔧 Configuración](#-configuración)
  - [▶️ Ejecución](#️-ejecución)
- [🎮 Cómo Jugar](#-cómo-jugar)
  - [🎯 Controles](#-controles)
  - [🏆 Objetivos](#-objetivos)
- [📊 Estado del Desarrollo](#-estado-del-desarrollo)
- [🎯 Niveles Disponibles](#-niveles-disponibles)
- [📁 Estructura del Proyecto](#-estructura-del-proyecto)
- [🛠️ Comandos de Desarrollo](#️-comandos-de-desarrollo)
- [🎨 Diseño y Estilo](#-diseño-y-estilo)
- [🔄 Roadmap](#-roadmap)
- [🤝 Contribución](#-contribución)
- [📄 Licencia](#-licencia)

---

## 📋 Descripción

**Juego Educativo de Plataformas** es un proyecto desarrollado en C++ utilizando la biblioteca SDL2. Combina mecánicas clásicas de juegos de plataformas con contenido educativo, ofreciendo una experiencia de aprendizaje interactiva y divertida.

### ✨ Características Principales

- 🎓 **Contenido Educativo**: Niveles temáticos con matemáticas e historia
- 🎮 **Mecánicas Clásicas**: Física realista, saltos precisos y colisiones
- 🎨 **Estilo Retro**: Gráficos pixel art simplificados
- 🔧 **Código Limpio**: Arquitectura orientada a objetos bien estructurada
- 📚 **Documentación Completa**: Código comentado en español

---

## 🚀 Inicio Rápido

### 📋 Requisitos Previos

Antes de comenzar, asegúrate de tener instalado:

- **Sistema Operativo**: Linux (Ubuntu/Debian recomendado)
- **Compilador**: g++ con soporte para C++11 o superior
- **Herramientas de Build**: make
- **Bibliotecas**: SDL2 development libraries

### ⬇️ Instalación

#### 1. Clonar el Repositorio

```bash
# Clona el proyecto desde el repositorio
git clone https://github.com/codinSamueldev/game-project.git
cd game-project
```

#### 2. Instalar Dependencias

**Para Ubuntu/Debian:**
```bash
# Instalar dependencias automáticamente
make install-deps

# O manualmente:
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-2.0-0 build-essential
```

**Para otras distribuciones:**
```bash
# Fedora/CentOS/RHEL
sudo dnf install SDL2-devel gcc-c++ make

# Arch Linux
sudo pacman -S sdl2 gcc make
```

#### 3. Verificar Instalación

```bash
# Verificar que SDL2 esté correctamente instalado
make check-sdl
```

### 🔧 Configuración

El proyecto viene preconfigurado y listo para usar. No se requiere configuración adicional.

### ▶️ Ejecución

#### Método 1: Compilación y Ejecución Automática
```bash
# Compila y ejecuta el juego en un solo comando
make run
```

#### Método 2: Compilación Manual
```bash
# 1. Limpiar compilaciones anteriores (opcional)
make clean

# 2. Compilar el proyecto
make

# 3. Ejecutar el juego
./juego_educativo
```

#### Método 3: Ejecución Directa (si ya está compilado)
```bash
# Ejecutar directamente el binario
./juego_educativo
```

---

## 🎮 Cómo Jugar

### 🎯 Controles

| Acción | Tecla(s) | Descripción |
|--------|----------|-------------|
| **Menú Principal** | `ESPACIO` | Comenzar el juego |
| **Movimiento** | `←` `→` | Mover el personaje horizontalmente |
| **Saltar** | `↑` o `ESPACIO` | Realizar salto |
| **Reiniciar Nivel** | `R` | Reiniciar el nivel actual |
| **Salir** | `ESC` | Salir del juego (desde pantalla final) |

### 🏆 Objetivos

1. **Objetivo Principal**: Llegar a la plataforma dorada en la parte superior de cada nivel
2. **Evitar Obstáculos**: No caer fuera de las plataformas
3. **Aprender**: Absorber el contenido educativo de cada nivel

### 🎯 Consejos de Juego

- 💡 **Planifica tus saltos**: Observa la disposición de las plataformas antes de saltar
- 🔄 **Usa el reinicio**: Presiona `R` si te quedas atascado
- 🎯 **Precisión**: Los saltos requieren timing preciso
- 📚 **Aprende**: Cada nivel tiene contenido educativo específico

---

## 📊 Estado del Desarrollo

### ✅ Funcionalidades Completadas

#### 🏗️ **Sistema Base**
- [x] Configuración de SDL2
- [x] Loop principal del juego
- [x] Sistema de estados (Menú → Juego → Final)
- [x] Manejo de eventos y entrada del usuario

#### 🎮 **Mecánicas de Juego**
- [x] Física del jugador (gravedad, fricción, colisiones)
- [x] Sistema de plataformas
- [x] Detección de colisiones precisa
- [x] Sistema de reinicio de nivel

#### 🎨 **Interfaz y Visuales**
- [x] Menú principal informativo
- [x] Sistema de texto pixel art
- [x] Pantalla de finalización
- [x] Estilo visual retro consistente

#### 📚 **Contenido Educativo**
- [x] Nivel 1: "El Valle del Terror Absoluto" (Matemáticas - Valor Absoluto)

### 🔄 En Desarrollo

- [ ] Sistema de enemigos
- [ ] Cubos educativos interactivos
- [ ] Panel lateral de información
- [ ] Sistema de preguntas
- [ ] Nivel 2: "Las Ruinas de la Sabiduría Antigua" (Historia - Antigua Grecia)

---

## 🎯 Niveles Disponibles

### 🔢 Nivel 1: "El Valle del Terror Absoluto"
- **📚 Tema**: Matemáticas - Valor Absoluto
- **🎯 Objetivo**: Llegar a la plataforma dorada superior
- **🏗️ Diseño**: 7 plataformas en disposición vertical ascendente
- **⚡ Mecánicas**: Saltos precisos entre plataformas
- **📊 Dificultad**: Principiante

### 🏛️ Nivel 2: "Las Ruinas de la Sabiduría Antigua" *(Próximamente)*
- **📚 Tema**: Historia - Antigua Grecia
- **🎯 Objetivo**: Por definir
- **🏗️ Diseño**: En desarrollo
- **⚡ Mecánicas**: Nuevas mecánicas por implementar
- **📊 Dificultad**: Intermedio

---

## 📁 Estructura del Proyecto

```
game-project/
├── 📂 src/                     # Código fuente
│   ├── 🎮 main.cpp             # Punto de entrada del programa
│   ├── 🎯 Juego.h/.cpp         # Clase principal del juego
│   ├── 👤 Jugador.h/.cpp       # Mecánicas del personaje
│   ├── 🟩 Plataforma.h/.cpp    # Sistema de plataformas
│   ├── 🎲 Nivel1.h/.cpp        # Lógica del primer nivel
│   └── 📝 TextoSimple.h/.cpp   # Sistema de renderizado de texto
├── 📂 build/                   # Archivos compilados (generado)
│   └── *.o                     # Archivos objeto
├── 🔧 Makefile                 # Sistema de compilación
├── 📖 README.md                # Documentación principal
├── 📋 requerimientos.md        # Plan detallado del proyecto
└── 🎮 juego_educativo          # Ejecutable (generado)
```

### 📝 Descripción de Archivos Clave

| Archivo | Propósito |
|---------|-----------|
| `main.cpp` | Inicialización y punto de entrada |
| `Juego.h/.cpp` | Gestión de estados y loop principal |
| `Jugador.h/.cpp` | Física y mecánicas del personaje |
| `Plataforma.h/.cpp` | Sistema de colisiones de plataformas |
| `Nivel1.h/.cpp` | Lógica específica del primer nivel |
| `TextoSimple.h/.cpp` | Renderizado de texto pixel art |

---

## 🛠️ Comandos de Desarrollo

### 📦 Compilación

```bash
# Compilación completa
make

# Compilación con limpieza previa
make clean && make

# Compilación y ejecución
make run
```

### 🧹 Limpieza

```bash
# Limpiar archivos compilados
make clean

# Limpiar y verificar
make clean && ls -la
```

### 🔍 Verificación

```bash
# Verificar dependencias
make check-sdl

# Mostrar ayuda de comandos
make help
```

### 🐛 Debugging

```bash
# Compilar con información de debug
g++ -std=c++11 -Wall -Wextra -g -O0 src/*.cpp -o juego_educativo_debug -lSDL2

# Ejecutar con gdb
gdb ./juego_educativo_debug
```

---

## 🎨 Diseño y Estilo

### 🎨 **Estilo Visual**
- **Tema**: Pixel Art Retro Simplificado
- **Paleta**: 12-16 colores cuidadosamente seleccionados
- **Formas**: Geometría simple con rectángulos y bordes definidos

### 🎭 **Elementos Visuales**

| Elemento | Color | Dimensiones | Descripción |
|----------|-------|-------------|-------------|
| **Jugador** | Azul (`#0064FF`) | 32x32 px | Rectángulo con borde negro |
| **Plataformas** | Verde (`#228B22`) | Variable x 20 px | Con decoración superior |
| **Meta** | Dorado (`#FFD700`) | 50x40 px | Objetivo del nivel |
| **Fondo Nivel 1** | Azul Oscuro (`#191970`) | 800x600 px | Tema "Valle del Terror" |

### 🎯 **Principios de Diseño**
- **Simplicidad**: Formas geométricas básicas
- **Legibilidad**: Alto contraste entre elementos
- **Consistencia**: Paleta de colores uniforme
- **Accesibilidad**: Colores distinguibles

---

## 🔄 Roadmap

### 🎯 **Fase Actual: Mecánicas Básicas** *(Completada)*
- [x] Sistema de juego fundamental
- [x] Nivel 1 funcional
- [x] Interfaz de usuario básica

### 🎮 **Próxima Fase: Elementos Interactivos**
- [ ] **Enemigos**: Rectángulos rojos con movimiento horizontal
- [ ] **Cubos Educativos**: Elementos que muestran información al colisionar
- [ ] **Panel Lateral**: Sistema de información educativa

### 📚 **Fase Educativa: Sistema de Aprendizaje**
- [ ] **Contenido Matemático**: Archivos con información de valor absoluto
- [ ] **Sistema de Preguntas**: Evaluación al final de cada nivel
- [ ] **Progreso del Jugador**: Seguimiento de aprendizaje

### 🏛️ **Fase de Expansión: Nivel 2**
- [ ] **Nuevo Nivel**: "Las Ruinas de la Sabiduría Antigua"
- [ ] **Contenido Histórico**: Información sobre Antigua Grecia
- [ ] **Nuevas Mecánicas**: Elementos específicos del nivel

### ✨ **Fase de Pulimiento: Mejoras Finales**
- [ ] **Efectos Visuales**: Animaciones y transiciones
- [ ] **Audio**: Efectos de sonido y música
- [ ] **Optimización**: Mejoras de rendimiento
- [ ] **Testing**: Pruebas exhaustivas

---

## 🤝 Contribución

### 🔧 **Cómo Contribuir**

1. **Fork** el repositorio
2. **Crea** una rama para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. **Commit** tus cambios (`git commit -am 'Añadir nueva funcionalidad'`)
4. **Push** a la rama (`git push origin feature/nueva-funcionalidad`)
5. **Abre** un Pull Request

### 📋 **Estándares de Código**

- **Lenguaje**: C++11 o superior
- **Estilo**: Comentarios en español
- **Nomenclatura**: CamelCase para clases, camelCase para métodos
- **Documentación**: Comentarios descriptivos en todas las funciones

### 🐛 **Reportar Bugs**

Usa el sistema de issues del repositorio incluyendo:
- Descripción detallada del problema
- Pasos para reproducir
- Sistema operativo y versión
- Logs de error si están disponibles

---

## 📄 Licencia

Este proyecto es desarrollado con fines **educativos**. 

### 📚 **Uso Educativo**
- ✅ Permitido para aprendizaje y enseñanza
- ✅ Modificación y distribución con fines educativos
- ✅ Uso en instituciones educativas

### 🛠️ **Tecnologías Utilizadas**
- **C++11**: Lenguaje de programación principal
- **SDL2**: Biblioteca gráfica y de entrada
- **Make**: Sistema de compilación

---

<div align="center">

### 🎓 Desarrollado como Proyecto Educativo

*Este juego fue creado para demostrar conceptos de programación en C++, desarrollo de juegos y diseño de software educativo.*

**¿Tienes preguntas?** Abre un issue en el repositorio  
**¿Quieres contribuir?** ¡Las contribuciones son bienvenidas!

---

⭐ **¡Dale una estrella al proyecto si te ha sido útil!** ⭐

</div>
