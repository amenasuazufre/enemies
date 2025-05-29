/*
 * Implementación de la clase PanelLateral
 */

#include "PanelLateral.h"
#include "TextoSimple.h"
#include <iostream>
#include <sstream>

using namespace std;

PanelLateral::PanelLateral() {
    x = 500; // Lado derecho de la pantalla (800 - 250)
    y = 420; // Centrado verticalmente
    ancho = 280;
    alto = 180;
    visible = false;
    tiempoInicio = 0;
    duracionMostrar = 3000; // 3 segundos en milisegundos
    informacion = "";
}

PanelLateral::~PanelLateral() {
    // Destructor vacío - no hay recursos dinámicos que liberar
}

void PanelLateral::inicializar() {
    visible = false;
    tiempoInicio = 0;
    informacion = "";
    lineasTexto.clear();
    
    cout << "Panel lateral inicializado en posición (" << x << ", " << y << ")" << endl;
}

void PanelLateral::mostrar(const string& info) {
    informacion = info;
    visible = true;
    tiempoInicio = SDL_GetTicks();
    
    // Dividir el texto en líneas para mejor visualización
    dividirTextoEnLineas();
    
    cout << "Panel lateral mostrado con información: " << info.substr(0, 50) << "..." << endl;
}

void PanelLateral::actualizar() {
    if (visible) {
        Uint32 tiempoActual = SDL_GetTicks();
        if (tiempoActual - tiempoInicio >= duracionMostrar) {
            ocultar();
        }
    }
}

void PanelLateral::renderizar(SDL_Renderer* renderizador) {
    if (!visible) return;
    
    // Renderizar fondo del panel
    renderizarFondo(renderizador);
    
    // Renderizar texto
    renderizarTexto(renderizador);
}

void PanelLateral::renderizarFondo(SDL_Renderer* renderizador) {
    // Fondo semi-transparente (simulado con color gris claro)
    SDL_SetRenderDrawColor(renderizador, 240, 240, 240, 255); // Gris muy claro
    SDL_Rect fondoPanel = {x, y, ancho, alto};
    SDL_RenderFillRect(renderizador, &fondoPanel);
    
    // Borde del panel
    SDL_SetRenderDrawColor(renderizador, 100, 100, 100, 255); // Gris oscuro
    SDL_RenderDrawRect(renderizador, &fondoPanel);
    
    // Borde interno para mejor definición
    SDL_Rect bordeInterno = {x + 2, y + 2, ancho - 4, alto - 4};
    SDL_SetRenderDrawColor(renderizador, 150, 150, 150, 255); // Gris medio
    SDL_RenderDrawRect(renderizador, &bordeInterno);
    
    // Título del panel
    SDL_SetRenderDrawColor(renderizador, 0, 100, 200, 255); // Azul
    SDL_Rect tituloRect = {x + 5, y + 5, ancho - 10, 25};
    SDL_RenderFillRect(renderizador, &tituloRect);
}

void PanelLateral::renderizarTexto(SDL_Renderer* renderizador) {
    // Título
    TextoSimple::establecerColor(renderizador, 255, 255, 255); // Blanco
    TextoSimple::renderizarTextoCentrado(renderizador, "INFORMACION", x + ancho/2, y + 10, 16);
    
    // Contenido del texto
    TextoSimple::establecerColor(renderizador, 0, 0, 0); // Negro
    int posY = y + 40;
    int espaciadoLinea = 18;
    
    for (size_t i = 0; i < lineasTexto.size() && posY < y + alto - 20; i++) {
        TextoSimple::renderizarTexto(renderizador, lineasTexto[i], x + 10, posY, 12);
        posY += espaciadoLinea;
    }
    
    // Indicador de tiempo restante (barra de progreso simple)
    Uint32 tiempoActual = SDL_GetTicks();
    Uint32 tiempoTranscurrido = tiempoActual - tiempoInicio;
    float progreso = (float)tiempoTranscurrido / duracionMostrar;
    
    if (progreso <= 1.0f) {
        int anchoBarra = (int)((ancho - 20) * (1.0f - progreso));
        SDL_SetRenderDrawColor(renderizador, 0, 200, 0, 255); // Verde
        SDL_Rect barraProgreso = {x + 10, y + alto - 15, anchoBarra, 8};
        SDL_RenderFillRect(renderizador, &barraProgreso);
        
        // Fondo de la barra
        SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); // Gris claro
        SDL_Rect fondoBarra = {x + 10 + anchoBarra, y + alto - 15, (ancho - 20) - anchoBarra, 8};
        SDL_RenderFillRect(renderizador, &fondoBarra);
    }
}

void PanelLateral::dividirTextoEnLineas() {
    lineasTexto.clear();
    
    if (informacion.empty()) return;
    
    istringstream stream(informacion);
    string palabra;
    string lineaActual = "";
    const int maxCaracteresPorLinea = 28; // Aproximadamente para el ancho del panel
    
    while (stream >> palabra) {
        if (lineaActual.length() + palabra.length() + 1 <= maxCaracteresPorLinea) {
            if (!lineaActual.empty()) {
                lineaActual += " ";
            }
            lineaActual += palabra;
        } else {
            if (!lineaActual.empty()) {
                lineasTexto.push_back(lineaActual);
            }
            lineaActual = palabra;
        }
    }
    
    if (!lineaActual.empty()) {
        lineasTexto.push_back(lineaActual);
    }
    
    cout << "Texto dividido en " << lineasTexto.size() << " líneas" << endl;
}

void PanelLateral::ocultar() {
    visible = false;
    tiempoInicio = 0;
    cout << "Panel lateral ocultado" << endl;
}

void PanelLateral::establecerPosicion(int nuevaX, int nuevaY) {
    x = nuevaX;
    y = nuevaY;
}

void PanelLateral::establecerDimensiones(int nuevoAncho, int nuevoAlto) {
    ancho = nuevoAncho;
    alto = nuevoAlto;
}
