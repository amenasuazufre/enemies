/*
 * Implementación de la clase Jugador
 */

#include "Jugador.h"
#include <iostream>

using namespace std;

Jugador::Jugador() {
    x = 0.0f;
    y = 0.0f;
    velocidadX = 0.0f;
    velocidadY = 0.0f;
    ancho = 32;
    alto = 32;
    
    // Constantes de física
    gravedad = 0.8f;
    fuerzaSalto = -16.0f;
    velocidadMovimiento = 10.0f;
    
    enSuelo = false;
    saltando = false;
    
    rectanguloColision = {0, 0, ancho, alto};
}

Jugador::~Jugador() {
    // Destructor vacío - no hay recursos dinámicos que liberar
}

void Jugador::inicializar(float posX, float posY) {
    x = posX;
    y = posY;
    velocidadX = 0.0f;
    velocidadY = 0.0f;
    enSuelo = false;
    saltando = false;
    
    actualizarRectanguloColision();
    
    cout << "Jugador inicializado en posición (" << x << ", " << y << ")" << endl;
}

void Jugador::actualizar() {
    // Aplicar gravedad
    aplicarGravedad();
    
    // Actualizar posición horizontal
    x += velocidadX;
    
    // Actualizar posición vertical
    y += velocidadY;
    
    // Limitar movimiento horizontal a los bordes de la pantalla
    if (x < 0) {
        x = 0;
    } else if (x + ancho > 800) { // ANCHO_VENTANA
        x = 800 - ancho;
    }
    
    // Limitar caída por debajo de la pantalla
    if (y > 600) { // ALTO_VENTANA
        y = 600 - alto;
        velocidadY = 0;
        enSuelo = true;
    }
    
    // Actualizar rectángulo de colisión
    actualizarRectanguloColision();
    
    // Reducir velocidad horizontal gradualmente (fricción)
    velocidadX *= 0.85f;
    if (abs(velocidadX) < 0.1f) {
        velocidadX = 0.0f;
    }
}

void Jugador::renderizar(SDL_Renderer* renderizador) {
    // Dibujar jugador como rectángulo azul
    SDL_SetRenderDrawColor(renderizador, 0, 100, 255, 255); // Azul
    SDL_RenderFillRect(renderizador, &rectanguloColision);
    
    // Dibujar borde negro para mejor visibilidad
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderizador, &rectanguloColision);
}

void Jugador::moverIzquierda() {
    velocidadX = -velocidadMovimiento;
}

void Jugador::moverDerecha() {
    velocidadX = velocidadMovimiento;
}

void Jugador::saltar() {
    if (enSuelo && !saltando) {
        velocidadY = fuerzaSalto;
        enSuelo = false;
        saltando = true;
        cout << "Jugador saltando" << endl;
    }
}

void Jugador::detenerMovimientoHorizontal() {
    velocidadX = 0.0f;
}

void Jugador::aplicarGravedad() {
    if (!enSuelo) {
        velocidadY += gravedad;
        
        // Limitar velocidad de caída máxima
        if (velocidadY > 20.0f) {
            velocidadY = 20.0f;
        }
    }
    
    // Resetear estado de salto cuando la velocidad vertical es positiva (cayendo)
    if (velocidadY > 0) {
        saltando = false;
    }
}

void Jugador::actualizarRectanguloColision() {
    rectanguloColision.x = (int)x;
    rectanguloColision.y = (int)y;
    rectanguloColision.w = ancho;
    rectanguloColision.h = alto;
}

void Jugador::establecerEnSuelo(bool estado) {
    enSuelo = estado;
    if (estado) {
        velocidadY = 0.0f;
        saltando = false;
    }
}

void Jugador::establecerPosicionY(float nuevaY) {
    y = nuevaY;
    actualizarRectanguloColision();
}

void Jugador::establecerPosicion(float nuevaX, float nuevaY) {
    x = nuevaX;
    y = nuevaY;
    actualizarRectanguloColision();
}

void Jugador::reiniciarPosicion() {
    // Posición inicial del jugador (esquina inferior izquierda)
    x = 50.0f;
    y = 550.0f;
    velocidadX = 0.0f;
    velocidadY = 0.0f;
    enSuelo = true;
    saltando = false;
    
    actualizarRectanguloColision();
    cout << "Posición del jugador reiniciada" << endl;
}
