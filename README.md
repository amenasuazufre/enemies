# game-project
Juego interactivo hecho en C++ para aprender algo nuevo en cada nivel.

Este es un juego de plataformas inspirado en clásicos como Mario, con una mecánica única centrada en la educación. En lugar de los elementos tradicionales de los juegos de plataformas, encontrarás cubos interactivos a lo largo de los niveles.

Al interactuar con estos cubos, se revelará información educativa en diversas áreas del conocimiento, como matemáticas, literatura, filosofía y más. Por ejemplo, un cubo podría explicar de forma sencilla cómo calcular el valor absoluto de un número, o argumentar por qué el debate es fundamental para el desarrollo del pensamiento crítico.

El juego está desarrollado en C++ y utiliza principalmente la librería **lib-sdl** para los gráficos y la interactividad.

## Instalación en MacOS/Linux

Para instalar y ejecutar este juego en sistemas MacOS o Linux, sigue los siguientes pasos:

1.  **Clonar el repositorio:**

    Abre una terminal y clona el repositorio del juego:

    ```bash
    git clone git@github.com:codinSamueldev/game-project.git
    cd game-project
    ```


2.  **Instalar dependencias (lib-sdl):**

    Necesitas tener instalada la librería SDL2 y sus módulos de desarrollo. La forma de instalarla varía ligeramente dependiendo de tu sistema operativo y gestor de paquetes:

    *   **En MacOS (usando Homebrew):**

        Si no tienes Homebrew instalado, puedes seguir las instrucciones en [https://brew.sh/](https://brew.sh/). Una vez que tengas Homebrew, abre la terminal y ejecuta:

        ```bash
        brew install sdl2
        ```

    *   **En sistemas basados en Debian/Ubuntu:**

        Abre la terminal y ejecuta:

        ```bash
        sudo apt update
        sudo apt install libsdl2-dev
        ```

3.  **Compilar el juego:**

    Una vez que tengas las dependencias instaladas, navega a la carpeta del proyecto (`game-project`) en la terminal (si no lo hiciste ya en el paso 1) y compila el código fuente. Necesitarás un compilador de C++ (como g++). Puedes compilar usando `pkg-config` para encontrar las flags de compilación de SDL2:

    ```bash
    g++ main.cpp $(pkg-config --cflags --libs sdl2) -o game-project
    ```

## Ejecutar el juego

Una vez compilado, puedes ejecutar el juego desde la terminal:

```bash
./game-project
```
