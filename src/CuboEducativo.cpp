/*
 * Implementación de la clase CuboEducativo
 */

#include "CuboEducativo.h"
#include <iostream>

using namespace std;

CuboEducativo::CuboEducativo() {
    x = 0.0f;
    y = 0.0f;
    ancho = 20;
    alto = 20;
    informacion = "";
    activo = true;
    rectanguloColision = {0, 0, ancho, alto};
}

CuboEducativo::CuboEducativo(float posX, float posY, const string& info) {
    inicializar(posX, posY, info);
}

CuboEducativo::~CuboEducativo() {
    // Destructor vacío - no hay recursos dinámicos que liberar
}

void CuboEducativo::inicializar(float posX, float posY, const string& info) {
    x = posX;
    y = posY;
    ancho = 20;
    alto = 20;
    informacion = info;
    activo = true;
    
    actualizarRectanguloColision();
    
    cout << "Cubo educativo creado en (" << x << ", " << y << ") con información: " 
         << informacion.substr(0, 30) << "..." << endl;
}

void CuboEducativo::renderizar(SDL_Renderer* renderizador) {
    if (!activo) return;
    
    // Dibujar cubo como rectángulo amarillo
    SDL_SetRenderDrawColor(renderizador, 255, 255, 0, 255); // Amarillo
    SDL_RenderFillRect(renderizador, &rectanguloColision);
    
    // Dibujar borde más oscuro para mejor definición
    SDL_SetRenderDrawColor(renderizador, 218, 165, 32, 255); // Amarillo dorado
    SDL_RenderDrawRect(renderizador, &rectanguloColision);
    
    // Agregar un pequeño símbolo "?" en el centro para indicar información
    SDL_Rect simbolo = {
        rectanguloColision.x + 8,
        rectanguloColision.y + 6,
        4, 8
    };
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); // Negro
    SDL_RenderFillRect(renderizador, &simbolo);
    
    // Punto del signo de interrogación
    SDL_Rect punto = {
        rectanguloColision.x + 9,
        rectanguloColision.y + 15,
        2, 2
    };
    SDL_RenderFillRect(renderizador, &punto);
}

bool CuboEducativo::verificarColision(SDL_Rect rectanguloJugador) {
    if (!activo) return false;
    
    // Verificar si hay intersección entre los rectángulos
    return SDL_HasIntersection(&rectanguloJugador, &rectanguloColision);
}

void CuboEducativo::actualizarRectanguloColision() {
    rectanguloColision.x = (int)x;
    rectanguloColision.y = (int)y;
    rectanguloColision.w = ancho;
    rectanguloColision.h = alto;
}

void CuboEducativo::establecerPosicion(float nuevaX, float nuevaY) {
    x = nuevaX;
    y = nuevaY;
    actualizarRectanguloColision();
}

void CuboEducativo::establecerInformacion(const string& nuevaInfo) {
    informacion = nuevaInfo;
}
