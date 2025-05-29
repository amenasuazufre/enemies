/*
 * Clase PanelLateral
 * Muestra información educativa en un panel lateral cuando el jugador colisiona con cubos educativos
 */

#ifndef PANEL_LATERAL_H
#define PANEL_LATERAL_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class PanelLateral {
private:
    int x, y;
    int ancho, alto;
    bool visible;
    Uint32 tiempoInicio;
    Uint32 duracionMostrar; // en milisegundos
    std::string informacion;
    std::vector<std::string> lineasTexto;
    
    // Métodos privados
    void dividirTextoEnLineas();
    void renderizarFondo(SDL_Renderer* renderizador);
    void renderizarTexto(SDL_Renderer* renderizador);

public:
    PanelLateral();
    ~PanelLateral();
    
    // Métodos principales
    void inicializar();
    void mostrar(const std::string& info);
    void actualizar();
    void renderizar(SDL_Renderer* renderizador);
    void ocultar();
    
    // Getters
    bool estaVisible() const { return visible; }
    
    // Setters
    void establecerPosicion(int nuevaX, int nuevaY);
    void establecerDimensiones(int nuevoAncho, int nuevoAlto);
    void establecerDuracion(Uint32 nuevaDuracion) { duracionMostrar = nuevaDuracion; }
};

#endif
