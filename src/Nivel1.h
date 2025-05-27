/*
 * Clase Nivel1 - "El Valle del Terror Absoluto"
 * Maneja la lógica específica del primer nivel (Matemáticas - Valor Absoluto)
 */

#ifndef NIVEL1_H
#define NIVEL1_H

#include <SDL2/SDL.h>
#include <vector>
#include "Jugador.h"
#include "Plataforma.h"

class Nivel1 {
private:
    // Elementos del nivel
    Jugador* jugador;
    std::vector<Plataforma> plataformas;
    
    // Estado del nivel
    bool nivelCompletado;
    bool jugadorMuerto;
    
    // Posición inicial del jugador
    float posicionInicialX;
    float posicionInicialY;
    
    // Métodos privados
    void crearPlataformas();
    void verificarColisionesPlataformas();
    void verificarLimitesNivel();

public:
    Nivel1();
    ~Nivel1();
    
    // Métodos principales
    void inicializar(Jugador* jugadorRef);
    void actualizar();
    void renderizar(SDL_Renderer* renderizador);
    void manejarEventos(SDL_Event& evento);
    
    // Control del nivel
    void reiniciarNivel();
    void limpiar();
    
    // Getters
    bool estaCompletado() const { return nivelCompletado; }
    bool jugadorHaMuerto() const { return jugadorMuerto; }
    
    // Setters
    void establecerCompletado(bool estado) { nivelCompletado = estado; }
};

#endif
