/*
 * Implementación de la clase Nivel1
 */

#include "Nivel1.h"
#include <iostream>

using namespace std;

Nivel1::Nivel1() {
    jugador = nullptr;
    nivelCompletado = false;
    jugadorMuerto = false;
    posicionInicialX = 50.0f;
    posicionInicialY = 550.0f;
}

Nivel1::~Nivel1() {
    limpiar();
}

void Nivel1::inicializar(Jugador* jugadorRef) {
    jugador = jugadorRef;
    nivelCompletado = false;
    jugadorMuerto = false;
    
    // Inicializar jugador en posición inicial
    if (jugador) {
        jugador->inicializar(posicionInicialX, posicionInicialY);
    }
    
    // Crear las plataformas del nivel
    crearPlataformas();
    
    // Crear los cubos educativos del nivel
    crearCubosEducativos();
    
    // Inicializar panel lateral
    panelLateral.inicializar();
    
    cout << "Nivel 1 inicializado: El Valle del Terror Absoluto" << endl;
}

void Nivel1::crearPlataformas() {
    plataformas.clear();
    
    // Plataforma base (suelo)
    plataformas.push_back(Plataforma(0, 580, 800, 20));
    
    // Plataformas del nivel (diseño vertical ascendente)
    // Plataforma 1 - Izquierda baja
    plataformas.push_back(Plataforma(100, 480, 250, 20));
    
    // Plataforma 2 - Derecha media
    plataformas.push_back(Plataforma(500, 400, 120, 20));
    
    // Plataforma 3 - Centro-izquierda
    plataformas.push_back(Plataforma(200, 320, 140, 20));
    
    // Plataforma 4 - Derecha alta
    plataformas.push_back(Plataforma(550, 240, 130, 20));
    
    // Plataforma 5 - Izquierda muy alta
    plataformas.push_back(Plataforma(150, 160, 160, 20));
    
    // Plataforma final - Centro superior (meta)
    plataformas.push_back(Plataforma(350, 80, 100, 20));
    
    cout << "Creadas " << plataformas.size() << " plataformas para el Nivel 1" << endl;
}

void Nivel1::actualizar() {
    if (!jugador || nivelCompletado || jugadorMuerto) {
        return;
    }
    
    // Actualizar jugador
    jugador->actualizar();
    
    // Verificar colisiones con plataformas
    verificarColisionesPlataformas();
    
    // Verificar colisiones con cubos educativos
    verificarColisionesCubos();
    
    // Actualizar panel lateral
    panelLateral.actualizar();
    
    // Verificar límites del nivel
    verificarLimitesNivel();
    
    // Verificar si llegó a la meta (plataforma superior)
    if (plataformas.size() > 0) {
        Plataforma& plataformaMeta = plataformas.back(); // Última plataforma
        if (plataformaMeta.jugadorEncima(jugador->obtenerRectanguloColision())) {
            nivelCompletado = true;
            cout << "¡Nivel 1 completado! Llegaste a la meta." << endl;
        }
    }
}

void Nivel1::verificarColisionesPlataformas() {
    if (!jugador) return;
    
    SDL_Rect rectanguloJugador = jugador->obtenerRectanguloColision();
    bool jugadorEnAlgunaPlataforma = false;
    
    for (auto& plataforma : plataformas) {
        if (plataforma.jugadorEncima(rectanguloJugador)) {
            // El jugador está encima de esta plataforma
            float nuevaY = plataforma.obtenerY() - jugador->obtenerAlto();
            jugador->establecerPosicionY(nuevaY);
            jugador->establecerEnSuelo(true);
            jugadorEnAlgunaPlataforma = true;
            break;
        }
    }
    
    // Si el jugador no está en ninguna plataforma, está en el aire
    if (!jugadorEnAlgunaPlataforma) {
        jugador->establecerEnSuelo(false);
    }
}

void Nivel1::verificarColisionesCubos() {
    if (!jugador) return;
    
    SDL_Rect rectanguloJugador = jugador->obtenerRectanguloColision();
    
    for (auto& cubo : cubosEducativos) {
        if (cubo.verificarColision(rectanguloJugador)) {
            // Mostrar información del cubo en el panel lateral
            panelLateral.mostrar(cubo.obtenerInformacion());
            cout << "Jugador colisionó con cubo educativo" << endl;
            break; // Solo procesar una colisión por frame
        }
    }
}

void Nivel1::verificarLimitesNivel() {
    if (!jugador) return;
    
    // Verificar si el jugador cayó fuera del nivel
    if (jugador->obtenerY() > 600) {
        jugadorMuerto = true;
        cout << "El jugador cayó fuera del nivel. Reiniciando..." << endl;
    }
}

void Nivel1::renderizar(SDL_Renderer* renderizador) {
    // Fondo del nivel (azul oscuro para el "Valle del Terror")
    SDL_SetRenderDrawColor(renderizador, 25, 25, 112, 255); // Azul medianoche
    SDL_RenderClear(renderizador);
    
    // Renderizar todas las plataformas
    for (auto& plataforma : plataformas) {
        plataforma.renderizar(renderizador);
    }
    
    // Renderizar todos los cubos educativos
    for (auto& cubo : cubosEducativos) {
        cubo.renderizar(renderizador);
    }
    
    // Renderizar jugador
    if (jugador) {
        jugador->renderizar(renderizador);
    }
    
    // Renderizar indicador de meta en la plataforma superior
    if (plataformas.size() > 0) {
        Plataforma& plataformaMeta = plataformas.back();
        SDL_Rect metaRect = {
            (int)plataformaMeta.obtenerX() + 25,
            (int)plataformaMeta.obtenerY() - 40,
            50, 40
        };
        
        // Dibujar meta como rectángulo dorado
        SDL_SetRenderDrawColor(renderizador, 255, 215, 0, 255); // Dorado
        SDL_RenderFillRect(renderizador, &metaRect);
        SDL_SetRenderDrawColor(renderizador, 184, 134, 11, 255); // Dorado oscuro
        SDL_RenderDrawRect(renderizador, &metaRect);
    }
    
    // Mostrar título del nivel en la esquina superior izquierda
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
    SDL_Rect tituloRect = {10, 10, 300, 30};
    SDL_RenderDrawRect(renderizador, &tituloRect);
    
    // Renderizar panel lateral (se renderiza al final para que aparezca encima)
    panelLateral.renderizar(renderizador);
}

void Nivel1::manejarEventos(SDL_Event& evento) {
    if (!jugador || nivelCompletado || jugadorMuerto) {
        return;
    }
    
    if (evento.type == SDL_KEYDOWN) {
        switch (evento.key.keysym.sym) {
            case SDLK_LEFT:
                jugador->moverIzquierda();
                break;
                
            case SDLK_RIGHT:
                jugador->moverDerecha();
                break;
                
            case SDLK_UP:
            case SDLK_SPACE:
                jugador->saltar();
                break;
        }
    }
    
    if (evento.type == SDL_KEYUP) {
        switch (evento.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                jugador->detenerMovimientoHorizontal();
                break;
        }
    }
}

void Nivel1::reiniciarNivel() {
    jugadorMuerto = false;
    nivelCompletado = false;
    
    if (jugador) {
        jugador->reiniciarPosicion();
        jugador->establecerPosicion(posicionInicialX, posicionInicialY);
    }
    
    cout << "Nivel 1 reiniciado" << endl;
}

void Nivel1::crearCubosEducativos() {
    cubosEducativos.clear();
    
    // Cubo 1 - Definición de Valor Absoluto (en plataforma 1)
    cubosEducativos.push_back(CuboEducativo(
        175, 455, // Posición en plataforma 1
        "VALOR ABSOLUTO: El valor absoluto de un numero es su distancia al cero en la recta numerica, sin importar la direccion. Se representa con barras verticales |x|. Ejemplo: |5| = 5 y |-5| = 5."
    ));
    
    // Cubo 2 - Propiedades del Valor Absoluto (en plataforma 2)
    cubosEducativos.push_back(CuboEducativo(
        560, 375, // Posición en plataforma 2
        "PROPIEDADES: 1) |x| >= 0 siempre. 2) |x| = |-x|. 3) |x * y| = |x| * |y|. 4) |x + y| <= |x| + |y| (desigualdad triangular). 5) |x| = 0 si y solo si x = 0."
    ));
    
    // Cubo 3 - Aplicaciones del Valor Absoluto (en plataforma 3)
    cubosEducativos.push_back(CuboEducativo(
        270, 295, // Posición en plataforma 3
        "APLICACIONES: El valor absoluto se usa para medir distancias, errores de medicion, diferencias de temperatura, y en ecuaciones como |x - 3| = 5. Tambien en funciones que siempre devuelven valores positivos."
    ));
    
    // Cubo 4 - Historia del Valor Absoluto (en plataforma 4)
    cubosEducativos.push_back(CuboEducativo(
        615, 215, // Posición en plataforma 4
        "HISTORIA: El concepto de valor absoluto fue desarrollado por matematicos como Karl Weierstrass en el siglo XIX. Inicialmente se usaba para estudiar funciones complejas y mas tarde se aplico en algebra y geometria."
    ));
    
    // Cubo 5 - Ejercicios de Valor Absoluto (en plataforma 5)
    cubosEducativos.push_back(CuboEducativo(
        230, 135, // Posición en plataforma 5
        "EJERCICIOS: Resuelve: |x - 2| = 4. Respuesta: x = 6 o x = -2. Otro: |2x + 1| = 7. Respuesta: x = 3 o x = -4. El valor absoluto crea dos soluciones porque la distancia puede ser en ambas direcciones."
    ));
    
    cout << "Creados " << cubosEducativos.size() << " cubos educativos para el Nivel 1" << endl;
}

void Nivel1::limpiar() {
    plataformas.clear();
    cubosEducativos.clear();
    jugador = nullptr; // No eliminamos el jugador, solo la referencia
    cout << "Nivel 1 limpiado" << endl;
}
