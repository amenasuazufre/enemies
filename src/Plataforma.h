/*
 * Clase Plataforma
 * Representa las plataformas sobre las que el jugador puede pararse
 */

#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <SDL2/SDL.h>

class Plataforma {
private:
    float x, y;
    int ancho, alto;
    SDL_Rect rectanguloColision;
    
    // Métodos privados
    void actualizarRectanguloColision();

public:
    Plataforma();
    Plataforma(float posX, float posY, int anchura, int altura);
    ~Plataforma();
    
    // Métodos principales
    void inicializar(float posX, float posY, int anchura, int altura);
    void renderizar(SDL_Renderer* renderizador);
    
    // Detección de colisiones
    bool verificarColision(SDL_Rect rectanguloJugador);
    bool jugadorEncima(SDL_Rect rectanguloJugador);
    
    // Getters
    float obtenerX() const { return x; }
    float obtenerY() const { return y; }
    int obtenerAncho() const { return ancho; }
    int obtenerAlto() const { return alto; }
    SDL_Rect obtenerRectanguloColision() const { return rectanguloColision; }
    
    // Setters
    void establecerPosicion(float nuevaX, float nuevaY);
    void establecerDimensiones(int nuevoAncho, int nuevoAlto);
};

#endif
