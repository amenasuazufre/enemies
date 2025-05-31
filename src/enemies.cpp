#include "enemies.h"
#include <SDL2/SDL.h>
#include <algorithm>

// Constructor: inicializa el enemigo en la plataforma dada
Enemy::Enemy(Plataforma* plataforma, float posX, float posY, float velocidad)
    : plataforma(plataforma), x(posX), y(posY), velocidadX(velocidad)
{
    ancho = 20; // Tamaño base del triángulo
    alto = 20;
}

Enemy::~Enemy() {}

// Actualiza la posición del enemigo patrullando la plataforma
void Enemy::actualizar() {
    // Mover horizontalmente
    x += velocidadX;
    // Calcular límites de la plataforma
    float limiteIzq = plataforma->obtenerX();
    float limiteDer = plataforma->obtenerX() + plataforma->obtenerAncho() - ancho;
    // Si llega a un borde, invertir dirección
    if (x <= limiteIzq) {
        x = limiteIzq;
        velocidadX = -velocidadX;
    } else if (x >= limiteDer) {
        x = limiteDer;
        velocidadX = -velocidadX;
    }
    // Mantener al enemigo sobre la plataforma
    y = plataforma->obtenerY() - alto;
}

// Renderiza el enemigo como triángulo apuntando hacia arriba
void Enemy::renderizar(SDL_Renderer* renderizador) {
    // Puntos del triángulo
    SDL_Point puntos[4] = {
        {(int)(x + ancho / 2), (int)y}, // Vértice superior
        {(int)x, (int)(y + alto)},      // Esquina inferior izquierda
        {(int)(x + ancho), (int)(y + alto)}, // Esquina inferior derecha
        {(int)(x + ancho / 2), (int)y} // Volver al vértice superior
    };
    // Color rojo
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderDrawLines(renderizador, puntos, 4);
    // Opcional: rellenar el triángulo (no nativo en SDL2)
}

// Devuelve el rectángulo de colisión del enemigo
SDL_Rect Enemy::obtenerRectanguloColision() const {
    SDL_Rect rect = {(int)x, (int)y, ancho, alto};
    return rect;
}

// Detecta colisión con el jugador
bool Enemy::colisionaConJugador(const SDL_Rect& rectJugador) const {
    SDL_Rect rectEnemigo = obtenerRectanguloColision();
    return SDL_HasIntersection(&rectEnemigo, &rectJugador);
}
