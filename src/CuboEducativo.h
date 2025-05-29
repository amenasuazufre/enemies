/*
 * Clase CuboEducativo
 * Representa cubos que muestran información educativa al colisionar con el jugador
 */

#ifndef CUBO_EDUCATIVO_H
#define CUBO_EDUCATIVO_H

#include <SDL2/SDL.h>
#include <string>

class CuboEducativo {
private:
    float x, y;
    int ancho, alto;
    SDL_Rect rectanguloColision;
    std::string informacion;
    bool activo;
    
    // Métodos privados
    void actualizarRectanguloColision();

public:
    CuboEducativo();
    CuboEducativo(float posX, float posY, const std::string& info);
    ~CuboEducativo();
    
    // Métodos principales
    void inicializar(float posX, float posY, const std::string& info);
    void renderizar(SDL_Renderer* renderizador);
    
    // Detección de colisiones
    bool verificarColision(SDL_Rect rectanguloJugador);
    
    // Getters
    float obtenerX() const { return x; }
    float obtenerY() const { return y; }
    int obtenerAncho() const { return ancho; }
    int obtenerAlto() const { return alto; }
    SDL_Rect obtenerRectanguloColision() const { return rectanguloColision; }
    std::string obtenerInformacion() const { return informacion; }
    bool estaActivo() const { return activo; }
    
    // Setters
    void establecerPosicion(float nuevaX, float nuevaY);
    void establecerInformacion(const std::string& nuevaInfo);
    void establecerActivo(bool estado) { activo = estado; }
};

#endif
