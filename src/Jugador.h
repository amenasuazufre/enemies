/*
 * Clase Jugador
 * Maneja el movimiento, salto y colisiones del personaje principal
 */

#ifndef JUGADOR_H
#define JUGADOR_H

#include <SDL2/SDL.h>

class Jugador {
private:
    // Posición y dimensiones
    float x, y;
    float velocidadX, velocidadY;
    int ancho, alto;
    
    // Física
    float gravedad;
    float fuerzaSalto;
    float velocidadMovimiento;
    bool enSuelo;
    bool saltando;
    
    // Renderizado
    SDL_Rect rectanguloColision;
    
    // Métodos privados
    void aplicarGravedad();
    void actualizarRectanguloColision();

public:
    Jugador();
    ~Jugador();
    
    // Métodos principales
    void inicializar(float posX, float posY);
    void actualizar();
    void renderizar(SDL_Renderer* renderizador);
    
    // Movimiento
    void moverIzquierda();
    void moverDerecha();
    void saltar();
    void detenerMovimientoHorizontal();
    
    // Colisiones
    void establecerEnSuelo(bool estado);
    void establecerPosicionY(float nuevaY);
    
    // Getters
    float obtenerX() const { return x; }
    float obtenerY() const { return y; }
    int obtenerAncho() const { return ancho; }
    int obtenerAlto() const { return alto; }
    SDL_Rect obtenerRectanguloColision() const { return rectanguloColision; }
    bool estaEnSuelo() const { return enSuelo; }
    
    // Setters
    void establecerPosicion(float nuevaX, float nuevaY);
    void reiniciarPosicion();
};

#endif
