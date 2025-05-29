/*
 * Clase principal del juego
 * Maneja la ventana, renderizado y estados del juego
 */

#ifndef JUEGO_H
#define JUEGO_H

#include <SDL2/SDL.h>
#include <string>
#include "Jugador.h"
#include "Nivel1.h"
#include <SDL2/SDL_ttf.h>

// Constantes del juego
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;
const std::string TITULO_VENTANA = "LEVEL UP!";

// Estados del juego
enum EstadoJuego {
    MENU_PRINCIPAL,
    NIVEL_1,
    NIVEL_2,
    PANTALLA_FINAL,
    SALIR
};

class Juego {
private:
    SDL_Window* ventana;
    SDL_Renderer* renderizador;
    bool ejecutando;
    EstadoJuego estadoActual;
    
    // Puntero SDL_ttf
    TTF_Font* fuente;
    
    // Elementos del juego
    Jugador jugador;
    Nivel1 nivel1;
    
    // Métodos privados
    void manejarEventos();
    void actualizar();
    void renderizar();
    void renderizarMenuPrincipal();
    void renderizarPantallaFinal();
    
    // Helper para renderizar texto con SDL_ttf
    void renderizarTextoSDLTTF(const std::string& texto, int x, int y, SDL_Color color);

public:
    Juego();
    ~Juego();
    
    bool inicializar();
    void ejecutar();
    void limpiar();
    
    // Getters
    SDL_Renderer* obtenerRenderizador() { return renderizador; }
    EstadoJuego obtenerEstado() { return estadoActual; }
    
    // Setters
    void cambiarEstado(EstadoJuego nuevoEstado) { estadoActual = nuevoEstado; }
};

#endif
