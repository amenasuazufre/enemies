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
    
    // Título principal
    TextoSimple::establecerColor(renderizador, 255, 255, 255);
    TextoSimple::renderizarTextoCentrado(renderizador, "JUEGO EDUCATIVO", 400, 80, 42);
    TextoSimple::renderizarTextoCentrado(renderizador, "DE PLATAFORMAS", 400, 130, 42);
    
    // Subtítulo
    TextoSimple::establecerColor(renderizador, 200, 200, 255);
    TextoSimple::renderizarTextoCentrado(renderizador, "Aprende mientras juegas", 400, 190, 24);
    
    // Información de niveles
    TextoSimple::establecerColor(renderizador, 255, 215, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "NIVEL 1: EL VALLE DEL TERROR ABSOLUTO", 400, 250, 20);
    TextoSimple::establecerColor(renderizador, 150, 255, 150);
    TextoSimple::renderizarTextoCentrado(renderizador, "Tema: Matematicas - Valor Absoluto", 400, 280, 18);
    
    // Controles del juego
    TextoSimple::establecerColor(renderizador, 255, 255, 255);
    TextoSimple::renderizarTextoCentrado(renderizador, "CONTROLES:", 400, 330, 24);
    
    TextoSimple::establecerColor(renderizador, 200, 200, 200);
    TextoSimple::renderizarTexto(renderizador, "Flechas", 200, 360, 18);
    TextoSimple::renderizarTexto(renderizador, "Movimiento horizontal", 350, 360, 18);
    
    TextoSimple::renderizarTexto(renderizador, "Flecha arriba o ESPACIO", 200, 385, 18);
    TextoSimple::renderizarTexto(renderizador, "Saltar", 500, 385, 18);
    
    TextoSimple::renderizarTexto(renderizador, "R", 200, 410, 18);
    TextoSimple::renderizarTexto(renderizador, "Reiniciar nivel", 350, 410, 18);
    
    // Objetivo
    TextoSimple::establecerColor(renderizador, 255, 215, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "OBJETIVO: Llega a la plataforma dorada", 400, 450, 20);
    
    // Instrucción para comenzar
    TextoSimple::establecerColor(renderizador, 255, 100, 100);
    TextoSimple::renderizarTextoCentrado(renderizador, "PRESIONA ESPACIO PARA COMENZAR", 400, 520, 28);
    
    // Créditos
    TextoSimple::establecerColor(renderizador, 100, 100, 150);
    TextoSimple::renderizarTextoCentrado(renderizador, "Desarrollado en C++ con SDL2", 400, 570, 14);
}

void Juego::renderizarPantallaFinal() {
    // Fondo dorado
    SDL_SetRenderDrawColor(renderizador, 255, 215, 0, 255);
    SDL_RenderClear(renderizador);
    
    // Título de felicitaciones
    TextoSimple::establecerColor(renderizador, 0, 0, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "FELICITACIONES", 400, 100, 48);
    
    // Mensaje de completado
    TextoSimple::establecerColor(renderizador, 50, 50, 50);
    TextoSimple::renderizarTextoCentrado(renderizador, "Has completado el Nivel 1", 400, 170, 28);
    TextoSimple::renderizarTextoCentrado(renderizador, "EL VALLE DEL TERROR ABSOLUTO", 400, 210, 24);
    
    // Información educativa
    TextoSimple::establecerColor(renderizador, 100, 50, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "Aprendiste sobre:", 400, 270, 22);
    TextoSimple::renderizarTextoCentrado(renderizador, "Matematicas - Valor Absoluto", 400, 300, 20);
    
    // Estadísticas del juego
    TextoSimple::establecerColor(renderizador, 0, 100, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "Habilidades desarrolladas:", 400, 350, 18);
    TextoSimple::renderizarTextoCentrado(renderizador, "- Coordinacion y reflejos", 400, 375, 16);
    TextoSimple::renderizarTextoCentrado(renderizador, "- Resolucion de problemas", 400, 395, 16);
    TextoSimple::renderizarTextoCentrado(renderizador, "- Perseverancia", 400, 415, 16);
    
    // Próximos pasos
    TextoSimple::establecerColor(renderizador, 150, 0, 150);
    TextoSimple::renderizarTextoCentrado(renderizador, "Proximamente: Nivel 2", 400, 460, 20);
    TextoSimple::renderizarTextoCentrado(renderizador, "Las Ruinas de la Sabiduria Antigua", 400, 485, 18);
    
    // Instrucción para salir
    TextoSimple::establecerColor(renderizador, 200, 0, 0);
    TextoSimple::renderizarTextoCentrado(renderizador, "Presiona ESC para salir", 400, 530, 22);
    
    // Créditos
    TextoSimple::establecerColor(renderizador, 100, 100, 100);
    TextoSimple::renderizarTextoCentrado(renderizador, "Gracias por jugar", 400, 570, 16);
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
