/*
 * Juego Educativo de Plataformas
 * Desarrolladores: [Tu nombre aquí]
 * Tecnología: C++ con SDL2
 * 
 * Archivo principal del juego
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Juego.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error al inicializar SDL: " << SDL_GetError() << endl;
        return -1;
    }

    // Crear instancia del juego
    Juego juego;
    
    // Inicializar el juego
    if (!juego.inicializar()) {
        cout << "Error al inicializar el juego" << endl;
        SDL_Quit();
        return -1;
    }

    // Loop principal del juego
    juego.ejecutar();

    // Limpiar recursos
    juego.limpiar();
    SDL_Quit();

    return 0;
}
