#ifndef NIVEL2_H
#define NIVEL2_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Jugador.h"
#include "Plataforma.h"
#include "CuboEducativo.h"
#include "PanelLateral.h"

class Nivel2  {
private:
   Jugador* jugador;
    std::vector<Plataforma> plataformas;
    std::vector<CuboEducativo> cubosEducativos;
    PanelLateral panelLateral;

    bool nivelCompletado;
    bool jugadorMuerto;


    float posicionInicialX;
    float posicionInicialY;

    void crearPlataformas();
    void crearCubosEducativos();
    void verificarColisionesPlataformas();
    void verificarColisionesCubos();
    void verificarLimitesNivel();


    public:
    Nivel2();
    ~Nivel2();

    void inicializar(Jugador* jugadorRef, TTF_Font* fuenteRef);
    void actualizar();
    void renderizar(SDL_Renderer* renderizador);
    void manejarEventos(SDL_Event& evento);


    void reiniciarNivel();
    void limpiar();


    bool estaCompletado() const { return nivelCompletado; }
    bool jugadorHaMuerto() const { return jugadorMuerto; }


    void establecerCompletado(bool estado) { nivelCompletado = estado; }
};

#endif

