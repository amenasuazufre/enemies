#ifndef ENEMIES_H
#define ENEMIES_H
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Plataforma.h"

// Clase Enemy: representa un enemigo que patrulla una plataforma
class Enemy {

	private:
		// Posición y dimensiones.
		float x, y;
		float velocidadX, velocidadY;
		int ancho, alto;

		// Física
    		float gravedad;
    		float fuerzaSalto;
    		float velocidadMovimiento;
    		bool enSuelo;

		SDL_Point posisition;
		int speed;

		Plataforma* plataforma; // Plataforma asignada

	public:
		// Constructor & Destructor.
		Enemy(Plataforma* plataforma, float posX, float posY, float velocidad = 2.0f);
		~Enemy();

		// Métodos iniciales.
		void inicializar(float posX, float posY);
		void actualizar();
		void renderizar(SDL_Renderer* renderizador);

		// Movimiento de los enemigos.
		void moverDerecha();
		void moverIzquierda();
		void detenerMovimientoHorizontal();

		// Colisiones.
		void establecerEnSuelo(bool estado);
		
		// Getters.
		float obtenerX() const { return x; }
		float obtenerY() const { return y; }
		int obtenerAlto() const { return alto; }
		int obtenerAncho() const { return ancho; }
		bool estaEnSuelo() const { return enSuelo; }

		// Devuelve el rectángulo de colisión del enemigo
		SDL_Rect obtenerRectanguloColision() const;

		// Detecta colisión con el jugador
		bool colisionaConJugador(const SDL_Rect& rectJugador) const;
};
#endif

