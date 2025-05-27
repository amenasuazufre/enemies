/*
 * Implementación de la clase Plataforma
 */

#include "Plataforma.h"
#include <iostream>

using namespace std;

Plataforma::Plataforma() {
    x = 0.0f;
    y = 0.0f;
    ancho = 100;
    alto = 20;
    rectanguloColision = {0, 0, ancho, alto};
}

Plataforma::Plataforma(float posX, float posY, int anchura, int altura) {
    inicializar(posX, posY, anchura, altura);
}

Plataforma::~Plataforma() {
    // Destructor vacío - no hay recursos dinámicos que liberar
}

void Plataforma::inicializar(float posX, float posY, int anchura, int altura) {
    x = posX;
    y = posY;
    ancho = anchura;
    alto = altura;
    
    actualizarRectanguloColision();
    
    cout << "Plataforma creada en (" << x << ", " << y << ") con dimensiones " 
         << ancho << "x" << alto << endl;
}

void Plataforma::renderizar(SDL_Renderer* renderizador) {
    // Dibujar plataforma como rectángulo verde
    SDL_SetRenderDrawColor(renderizador, 34, 139, 34, 255); // Verde bosque
    SDL_RenderFillRect(renderizador, &rectanguloColision);
    
    // Dibujar borde más oscuro para mejor definición
    SDL_SetRenderDrawColor(renderizador, 0, 100, 0, 255); // Verde oscuro
    SDL_RenderDrawRect(renderizador, &rectanguloColision);
    
    // Agregar líneas decorativas en la parte superior
    SDL_SetRenderDrawColor(renderizador, 50, 205, 50, 255); // Verde lima
    for (int i = 0; i < ancho; i += 10) {
        SDL_RenderDrawPoint(renderizador, rectanguloColision.x + i, rectanguloColision.y + 2);
    }
}

bool Plataforma::verificarColision(SDL_Rect rectanguloJugador) {
    // Verificar si hay intersección entre los rectángulos
    return SDL_HasIntersection(&rectanguloJugador, &rectanguloColision);
}

bool Plataforma::jugadorEncima(SDL_Rect rectanguloJugador) {
    // Verificar si el jugador está encima de la plataforma
    // El jugador debe estar cayendo (velocidad Y positiva) y su parte inferior
    // debe estar cerca de la parte superior de la plataforma
    
    int jugadorInferior = rectanguloJugador.y + rectanguloJugador.h;
    int plataformaSuperior = rectanguloColision.y;
    
    // Verificar si hay superposición horizontal
    bool superpuestoHorizontalmente = 
        (rectanguloJugador.x < rectanguloColision.x + rectanguloColision.w) &&
        (rectanguloJugador.x + rectanguloJugador.w > rectanguloColision.x);
    
    // Verificar si el jugador está justo encima de la plataforma
    bool encimaVerticalmente = 
        (jugadorInferior >= plataformaSuperior) &&
        (jugadorInferior <= plataformaSuperior + 10); // Tolerancia de 10 píxeles
    
    return superpuestoHorizontalmente && encimaVerticalmente;
}

void Plataforma::actualizarRectanguloColision() {
    rectanguloColision.x = (int)x;
    rectanguloColision.y = (int)y;
    rectanguloColision.w = ancho;
    rectanguloColision.h = alto;
}

void Plataforma::establecerPosicion(float nuevaX, float nuevaY) {
    x = nuevaX;
    y = nuevaY;
    actualizarRectanguloColision();
}

void Plataforma::establecerDimensiones(int nuevoAncho, int nuevoAlto) {
    ancho = nuevoAncho;
    alto = nuevoAlto;
    actualizarRectanguloColision();
}
