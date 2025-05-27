/*
 * Implementación de la clase Juego
 */

#include "Juego.h"
#include <iostream>

using namespace std;

Juego::Juego() {
    ventana = nullptr;
    renderizador = nullptr;
    ejecutando = false;
    estadoActual = MENU_PRINCIPAL;
}

Juego::~Juego() {
    limpiar();
}

bool Juego::inicializar() {
    // Crear ventana
    ventana = SDL_CreateWindow(
        TITULO_VENTANA.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        ANCHO_VENTANA,
        ALTO_VENTANA,
        SDL_WINDOW_SHOWN
    );
    
    if (!ventana) {
        cout << "Error al crear ventana: " << SDL_GetError() << endl;
        return false;
    }
    
    // Crear renderizador
    renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderizador) {
        cout << "Error al crear renderizador: " << SDL_GetError() << endl;
        return false;
    }
    
    ejecutando = true;
    cout << "Juego inicializado correctamente" << endl;
    return true;
}

void Juego::ejecutar() {
    while (ejecutando) {
        manejarEventos();
        actualizar();
        renderizar();
        
        // Controlar FPS (aproximadamente 60 FPS)
        SDL_Delay(16);
    }
}

void Juego::manejarEventos() {
    SDL_Event evento;
    
    while (SDL_PollEvent(&evento)) {
        switch (evento.type) {
            case SDL_QUIT:
                ejecutando = false;
                break;
                
            case SDL_KEYDOWN:
                switch (estadoActual) {
                    case MENU_PRINCIPAL:
                        if (evento.key.keysym.sym == SDLK_SPACE) {
                            estadoActual = NIVEL_1;
                            nivel1.inicializar(&jugador);
                            cout << "Iniciando Nivel 1: El Valle del Terror Absoluto" << endl;
                        }
                        break;
                        
                    case NIVEL_1:
                        // Manejar reinicio del nivel con R
                        if (evento.key.keysym.sym == SDLK_r) {
                            nivel1.reiniciarNivel();
                        }
                        break;
                        
                    case PANTALLA_FINAL:
                        if (evento.key.keysym.sym == SDLK_ESCAPE) {
                            ejecutando = false;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
        }
        
        // Pasar eventos al nivel actual
        if (estadoActual == NIVEL_1) {
            nivel1.manejarEventos(evento);
        }
    }
}

void Juego::actualizar() {
    // Lógica de actualización según el estado actual
    switch (estadoActual) {
        case NIVEL_1:
            nivel1.actualizar();
            
            // Verificar si el jugador murió
            if (nivel1.jugadorHaMuerto()) {
                nivel1.reiniciarNivel();
            }
            
            // Verificar si el nivel se completó
            if (nivel1.estaCompletado()) {
                estadoActual = PANTALLA_FINAL;
                cout << "¡Felicitaciones! Has completado el Nivel 1" << endl;
            }
            break;
            
        case NIVEL_2:
            // TODO: Actualizar lógica del nivel 2
            break;
            
        default:
            break;
    }
}

void Juego::renderizar() {
    // Limpiar pantalla con color negro
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);
    
    // Renderizar según el estado actual
    switch (estadoActual) {
        case MENU_PRINCIPAL:
            renderizarMenuPrincipal();
            break;
            
        case NIVEL_1:
            nivel1.renderizar(renderizador);
            break;
            
        case NIVEL_2:
            // TODO: Renderizar nivel 2
            // Por ahora, solo un fondo marrón
            SDL_SetRenderDrawColor(renderizador, 139, 69, 19, 255);
            SDL_RenderClear(renderizador);
            break;
            
        case PANTALLA_FINAL:
            renderizarPantallaFinal();
            break;
            
        default:
            break;
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderizador);
}

void Juego::renderizarMenuPrincipal() {
    // Fondo degradado azul
    SDL_SetRenderDrawColor(renderizador, 30, 30, 80, 255);
    SDL_RenderClear(renderizador);
    
    // Título del juego (simulado con rectángulos)
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
    
    // Rectángulo para simular el título
    SDL_Rect tituloRect = {200, 150, 400, 80};
    SDL_RenderDrawRect(renderizador, &tituloRect);
    
    // Instrucciones (simulado con rectángulos)
    SDL_Rect instruccionRect = {250, 300, 300, 40};
    SDL_RenderDrawRect(renderizador, &instruccionRect);
    
    // Texto simulado "PRESIONA ESPACIO PARA COMENZAR"
    SDL_Rect textoRect = {200, 400, 400, 30};
    SDL_RenderDrawRect(renderizador, &textoRect);
}

void Juego::renderizarPantallaFinal() {
    // Fondo dorado
    SDL_SetRenderDrawColor(renderizador, 255, 215, 0, 255);
    SDL_RenderClear(renderizador);
    
    // Rectángulo para felicitaciones
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_Rect felicitacionesRect = {150, 200, 500, 100};
    SDL_RenderDrawRect(renderizador, &felicitacionesRect);
    
    // Rectángulo para créditos
    SDL_Rect creditosRect = {200, 350, 400, 150};
    SDL_RenderDrawRect(renderizador, &creditosRect);
}

void Juego::limpiar() {
    if (renderizador) {
        SDL_DestroyRenderer(renderizador);
        renderizador = nullptr;
    }
    
    if (ventana) {
        SDL_DestroyWindow(ventana);
        ventana = nullptr;
    }
    
    cout << "Recursos del juego liberados" << endl;
}
