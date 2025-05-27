/*
 * Clase TextoSimple
 * Renderiza texto básico usando rectángulos para simular letras
 */

#ifndef TEXTO_SIMPLE_H
#define TEXTO_SIMPLE_H

#include <SDL2/SDL.h>
#include <string>

class TextoSimple {
private:
    static void renderizarLetra(SDL_Renderer* renderizador, char letra, int x, int y, int tamaño);
    static int obtenerAnchoLetra(char letra, int tamaño);

public:
    // Renderizar texto en una posición específica
    static void renderizarTexto(SDL_Renderer* renderizador, const std::string& texto, 
                               int x, int y, int tamaño = 20);
    
    // Obtener el ancho total de un texto
    static int obtenerAnchoTexto(const std::string& texto, int tamaño = 20);
    
    // Renderizar texto centrado
    static void renderizarTextoCentrado(SDL_Renderer* renderizador, const std::string& texto, 
                                       int centroX, int y, int tamaño = 20);
    
    // Establecer color del texto
    static void establecerColor(SDL_Renderer* renderizador, int r, int g, int b);
};

#endif
