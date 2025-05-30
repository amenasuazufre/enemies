#include "Nivel2.h"
#include <iostream>

Nivel2::Nivel2() {
    jugador = nullptr;
    nivelCompletado = false;
    jugadorMuerto = false;
    posicionInicialX = 50.0f;
    posicionInicialY = 550.0f;
}
Nivel2::Nivel2() {
    limpiar();
}

void Nivel2::inicializar(Jugador* jugadorRef, TTF_Font* fuenteRef) {
    jugador = jugadorRef;
    nivelCompletado = false;
    jugadorMuerto = false;
    
    if(jugador) {
       jugador->inicializar(posicionInicialX, posicionInicialY);
    }

    crearPlataformas();

    crearCubosEducativos();

    panelLateral.inicializar(fuenteRef);
    
    cout << "Nivel 2 inicializado: Las Ruinas de la Sabiduria Antigua" << endl;
}

    void Nivel2::crearPlataformas() {


    plataformas.push_back(Plataforma(50, 400, 100, 20));
    plataformas.push_back(Plataforma(200, 350, 100, 20));
    plataformas.push_back(Plataforma(350, 300, 100, 20));
    plataformas.push_back(Plataforma(500, 250, 100, 20));

    cout << "Creadas " << plataformas.size() << " plataformas para el Nivel 1" << endl;

}


void Nivel2::actualizar() {
    if (!jugador || nivelCompletado || jugadorMuerto) {
        return;
    }

    jugador->actualizar();

    verificarColisionesPlataformas();

    verificarColisionesCubos();

    panelLateral.actualizar();

    verificarLimitesNivel();

    if (plataformas.size() > 0) {
        Plataforma& plataformaMeta = plataformas.back();
        if (plataformaMeta.jugadorEncima(jugador->obtenerRectanguloColision())) {
            nivelCompletado = true;
            cout << "¡Nivel 2 completado! Llegaste a la meta." << endl;
        }
    }
}


void Nivel2::verificarColisionesPlataformas() {
    if (!jugador) return;
    
    SDL_Rect rectanguloJugador = jugador->obtenerRectanguloColision();
    bool jugadorEnAlgunaPlataforma = false;
    
    for (auto& plataforma : plataformas) {
        if (plataforma.jugadorEncima(rectanguloJugador)) {
            
            float nuevaY = plataforma.obtenerY() - jugador->obtenerAlto();
            jugador->establecerPosicionY(nuevaY);
            jugador->establecerEnSuelo(true);
            jugadorEnAlgunaPlataforma = true;
            break;
        }
    }
    

    if (!jugadorEnAlgunaPlataforma) {
        jugador->establecerEnSuelo(false);
    }
}

void Nivel2::verificarColisionesCubos() {
    if (!jugador) return;
    
    SDL_Rect rectanguloJugador = jugador->obtenerRectanguloColision();
    
    for (auto& cubo : cubosEducativos) {
        if (cubo.verificarColision(rectanguloJugador)) {
            
            panelLateral.mostrar(cubo.obtenerInformacion());
            cout << "Jugador colisionó con cubo educativo" << endl;
            break; 
        }
    }
}

void Nivel2::verificarLimitesNivel() {
    if (!jugador) return;
    
    
    if (jugador->obtenerY() > 600) {
        jugadorMuerto = true;
        cout << "El jugador cayó fuera del nivel. Reiniciando..." << endl;
    }
}

void Nivel2::renderizar(SDL_Renderer* renderizador) {
    
    SDL_SetRenderDrawColor(renderizador, 25, 25, 112, 255); 
    SDL_RenderClear(renderizador);
    
    
    for (auto& plataforma : plataformas) {
        plataforma.renderizar(renderizador);
    }
    
    
    for (auto& cubo : cubosEducativos) {
        cubo.renderizar(renderizador);
    }
    
    
    if (jugador) {
        jugador->renderizar(renderizador);
    }
    
    
    if (plataformas.size() > 0) {
        Plataforma& plataformaMeta = plataformas.back();
        SDL_Rect metaRect = {
            (int)plataformaMeta.obtenerX() + 25,
            (int)plataformaMeta.obtenerY() - 40,
            50, 40
        };
        
        
        SDL_SetRenderDrawColor(renderizador, 255, 215, 0, 255); 
        SDL_RenderFillRect(renderizador, &metaRect);
        SDL_SetRenderDrawColor(renderizador, 184, 134, 11, 255); 
        SDL_RenderDrawRect(renderizador, &metaRect);
    }
    
   
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
    SDL_Rect tituloRect = {10, 10, 300, 30};
    SDL_RenderDrawRect(renderizador, &tituloRect);
    
    
    panelLateral.renderizar(renderizador);
}

void Nivel2::manejarEventos(SDL_Event& evento) {
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



void Nivel2::reiniciarNivel() {
    jugadorMuerto = false;
    nivelCompletado = false;
    
    if (jugador) {
        jugador->reiniciarPosicion();
        jugador->establecerPosicion(posicionInicialX, posicionInicialY);
    }
    
    cout << "Nivel 2 reiniciado" << endl;


}

void Nivel2::crearCubosEducativos() {
    cubosEducativos.clear();

cubosEducativos.push_back(CuboEducativo(
        275, 355, 
        "El valor absoluto de un numero es su distancia al cero en la recta numerica, sin importar la direccion. Ejemplo: abs(5)=5 y abs(-5)=5."
    ));
    
    
    cubosEducativos.push_back(CuboEducativo(
        560, 375, 
        "PROPIEDADES: 1) |x| >= 0 siempre. 2) |x| = |-x|. 3) |x * y| = |x| * |y|. 4) |x + y| <= |x| + |y| (desigualdad triangular). 5) |x| = 0 si y solo si x = 0."
    ));
    
    
    cubosEducativos.push_back(CuboEducativo(
        270, 295, 
        "APLICACIONES: El valor absoluto se usa para medir distancias, errores de medicion, diferencias de temperatura, y en ecuaciones como |x - 3| = 5. Tambien en funciones que siempre devuelven valores positivos."
    ));
    
    
    cubosEducativos.push_back(CuboEducativo(
        615, 215, 
        "HISTORIA: El concepto de valor absoluto fue desarrollado por matematicos como Karl Weierstrass en el siglo XIX. Inicialmente se usaba para estudiar funciones complejas y mas tarde se aplico en algebra y geometria."
    ));
    
    
    cubosEducativos.push_back(CuboEducativo(
        230, 135, 
        "EJERCICIOS: Resuelve: |x - 2| = 4. Respuesta: x = 6 o x = -2. Otro: |2x + 1| = 7. Respuesta: x = 3 o x = -4. El valor absoluto crea dos soluciones porque la distancia puede ser en ambas direcciones."
    ));
    
    cout << "Creados " << cubosEducativos.size() << " cubos educativos para el Nivel 2" << endl;
}

void Nivel2::limpiar() {
    plataformas.clear();
    cubosEducativos.clear();
    jugador = nullptr; // No eliminamos el jugador, solo la referencia
    cout << "Nivel 2 limpiado" << endl;
}


    
    cubos.push_back(CuboEducativo(220, 320, "¡Bienvenido al Nivel 2!", AZUL));

    
    cubos.push_back(CuboEducativo(520, 220, "¡Nivel completado!", AMARILLO));

    jugador.setPosicion(50, 370);
}

void Nivel2::actualizar() {
    jugador.actualizar();

    for (auto& plataforma : plataformas) {
        jugador.verificarColision(plataforma);
    }

    for (auto& cubo : cubos) {
        cubo.verificarInteraccion(jugador);
    }
}

void Nivel2::renderizar() {
    for (auto& plataforma : plataformas) {
        plataforma.dibujar(renderer);
    }

    for (auto& cubo : cubos) {
        cubo.dibujar(renderer);
    }

    jugador.dibujar(renderer);
}

bool Nivel2::jugadorTocaCuboEspecial() {
    for (auto& cubo : cubos) {
        if (cubo.esEspecial() && cubo.colisionaCon(jugador)) {
            return true;
        }
    }
    return false;
}
