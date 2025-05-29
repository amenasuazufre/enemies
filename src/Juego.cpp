/*
 * Implementación de la clase Juego
 */

#include "Juego.h"
#include <iostream>

using namespace std;

Juego::Juego() {
    ventana = nullptr;
    renderizador = nullptr;
    ejecutando = false;
    estadoActual = MENU_PRINCIPAL;
}

Juego::~Juego() {
    limpiar();
}

bool Juego::inicializar() {
    // Crear ventana
    ventana = SDL_CreateWindow(
        TITULO_VENTANA.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        ANCHO_VENTANA,
        ALTO_VENTANA,
        SDL_WINDOW_SHOWN
    );
    
    if (!ventana) {
        cout << "Error al crear ventana: " << SDL_GetError() << endl;
        return false;
    }
    
    // Crear renderizador
    renderizador = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderizador) {
        cout << "Error al crear renderizador: " << SDL_GetError() << endl;
        return false;
    }
    
    // Inicializar SDL_ttf
    if (TTF_Init() < 0) {
        cout << "Error al inicializar SDL_ttf: " << TTF_GetError() << endl;
        limpiar(); // Limpiar recursos de SDL ya previamente inicializados.
        return false;
    }
    
    ejecutando = true;
    
    // Cargar fuente SDL_ttf
    fuente = TTF_OpenFont("src/data/fonts/Recoleta-Regular.ttf", 24);
    if (!fuente) {
        cout << "Error al cargar fuente SDL_ttf: " << TTF_GetError() << endl;
        limpiar(); // Limpiar recursos
        return false;
    }
    
    cout << "Juego inicializado correctamente" << endl;
    return true;
}

void Juego::ejecutar() {
    while (ejecutando) {
        manejarEventos();
        actualizar();
        renderizar();
        
        // Controlar FPS (aproximadamente 60 FPS)
        SDL_Delay(16);
    }
}

void Juego::manejarEventos() {
    SDL_Event evento;
    
    while (SDL_PollEvent(&evento)) {
        switch (evento.type) {
            case SDL_QUIT:
                ejecutando = false;
                break;
                
            case SDL_KEYDOWN:
                switch (estadoActual) {
                    case MENU_PRINCIPAL:
                        if (evento.key.keysym.sym == SDLK_SPACE) {
                            estadoActual = NIVEL_1;
                            nivel1.inicializar(&jugador, fuente);
                            cout << "Iniciando Nivel 1: El Valle del Terror Absoluto" << endl;
                        }
                        break;
                        
                    case NIVEL_1:
                        // Manejar reinicio del nivel con R
                        if (evento.key.keysym.sym == SDLK_r) {
                            nivel1.reiniciarNivel();
                        }
                        break;
                        
                    case PANTALLA_FINAL:
                        if (evento.key.keysym.sym == SDLK_ESCAPE) {
                            ejecutando = false;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
        }
        
        // Pasar eventos al nivel actual
        if (estadoActual == NIVEL_1) {
            nivel1.manejarEventos(evento);
        }
    }
}

void Juego::actualizar() {
    // Lógica de actualización según el estado actual
    switch (estadoActual) {
        case NIVEL_1:
            nivel1.actualizar();
            
            // Verificar si el jugador murió
            if (nivel1.jugadorHaMuerto()) {
                nivel1.reiniciarNivel();
            }
            
            // Verificar si el nivel se completó
            if (nivel1.estaCompletado()) {
                estadoActual = PANTALLA_FINAL;
                cout << "¡Felicitaciones! Has completado el Nivel 1" << endl;
            }
            break;
            
        case NIVEL_2:
            // TODO: Actualizar lógica del nivel 2
            break;
            
        default:
            break;
    }
}

void Juego::renderizar() {
    // Limpiar pantalla con color negro
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);
    
    // Renderizar según el estado actual
    switch (estadoActual) {
        case MENU_PRINCIPAL:
            renderizarMenuPrincipal();
            break;
            
        case NIVEL_1:
            nivel1.renderizar(renderizador);
            break;
            
        case NIVEL_2:
            // TODO: Renderizar nivel 2
            // Por ahora, solo un fondo marrón
            SDL_SetRenderDrawColor(renderizador, 139, 69, 19, 255);
            SDL_RenderClear(renderizador);
            break;
            
        case PANTALLA_FINAL:
            renderizarPantallaFinal();
            break;
            
        default:
            break;
    }
    
    // Presentar el frame
    SDL_RenderPresent(renderizador);
}

// Helper para renderizar texto con SDL_ttf
void Juego::renderizarTextoSDLTTF(const std::string& texto, int x, int y, SDL_Color color) {
    if (!fuente || !renderizador || texto.empty()) {
        return; // No renderizar si la fuente, renderizador o texto son inválidos
    }
    
    // Crear superficie de texto con SDL_ttf
    SDL_Surface* superficieTexto = TTF_RenderText_Solid(fuente, texto.c_str(), color);
    if (!superficieTexto) {
        cout << "Error al crear superficie de texto SDL_ttf: " << TTF_GetError() << endl;
        return;
    }
    
    // Crear textura a partir de la superficie
    SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderizador, superficieTexto);
    if (!texturaTexto) {
        cout << "Error al crear textura de texto SDL_ttf: " << SDL_GetError() << endl;
        SDL_FreeSurface(superficieTexto);
        return;
    }
    
    // Obtener dimensiones del texto para el rectángulo de destino
    SDL_Rect dstRect = {x, y, superficieTexto->w, superficieTexto->h};
    
    // Renderizar la textura de texto
    SDL_RenderCopy(renderizador, texturaTexto, nullptr, &dstRect);
    
    // Liberar recursos temporales
    SDL_DestroyTexture(texturaTexto);
    SDL_FreeSurface(superficieTexto);
}

void Juego::renderizarMenuPrincipal() {
    // Fondo degradado azul
    SDL_SetRenderDrawColor(renderizador, 30, 30, 80, 255);
    SDL_RenderClear(renderizador);
    
    // Título principal
    SDL_Color colorBlanco = {255, 255, 255, 255};
    SDL_Color colorAzulClaro = {200, 200, 255, 255};
    SDL_Color colorDorado = {255, 215, 0, 255};
    SDL_Color colorVerdeClaro = {150, 255, 150, 255};
    SDL_Color colorGrisClaro = {200, 200, 200, 255};
    SDL_Color colorRojoClaro = {255, 100, 100, 255};
    SDL_Color colorGrisAzul = {100, 100, 150, 255};

    int anchoTitulo1, altoTitulo1;
    TTF_SizeText(fuente, "LEVEL UP!", &anchoTitulo1, &altoTitulo1);
    renderizarTextoSDLTTF("LEVEL UP!", (ANCHO_VENTANA - anchoTitulo1) / 2, 80, colorBlanco);
    
    // Subtítulo
    int anchoTitulo2, altoTitulo2;
    TTF_SizeText(fuente, "JUEGO DE PLATAFORMAS", &anchoTitulo2, &altoTitulo2);
    renderizarTextoSDLTTF("JUEGO DE PLATAFORMAS", (ANCHO_VENTANA - anchoTitulo2) / 2, 130, colorBlanco);
    
    // Subtítulo 2
    int anchoSubtitulo, altoSubtitulo;
    TTF_SizeText(fuente, "Aprende mientras juegas", &anchoSubtitulo, &altoSubtitulo);
    renderizarTextoSDLTTF("Aprende mientras juegas", (ANCHO_VENTANA - anchoSubtitulo) / 2, 190, colorAzulClaro);
    
    // Información de niveles
    renderizarTextoSDLTTF("NIVEL 1: EL VALLE DEL TERROR ABSOLUTO", 400 - TextoSimple::obtenerAnchoTexto("NIVEL 1: EL VALLE DEL TERROR ABSOLUTO", 20) / 2, 250, colorDorado);
    renderizarTextoSDLTTF("Tema: Matematicas - Valor Absoluto", 400 - TextoSimple::obtenerAnchoTexto("Tema: Matematicas - Valor Absoluto", 18) / 2, 280, colorVerdeClaro);
    
    // Controles del juego
    renderizarTextoSDLTTF("CONTROLES:", 400 - TextoSimple::obtenerAnchoTexto("CONTROLES:", 24) / 2, 330, colorBlanco);
    
    renderizarTextoSDLTTF("Flechas", 200, 360, colorGrisClaro);
    renderizarTextoSDLTTF("Movimiento horizontal", 350, 360, colorGrisClaro);
    
    renderizarTextoSDLTTF("Flecha arriba o ESPACIO", 200, 385, colorGrisClaro);
    renderizarTextoSDLTTF("Saltar", 500, 385, colorGrisClaro);
    
    renderizarTextoSDLTTF("R", 200, 410, colorGrisClaro);
    renderizarTextoSDLTTF("Reiniciar nivel", 350, 410, colorGrisClaro);
    
    // Objetivo
    renderizarTextoSDLTTF("OBJETIVO: Llega a la plataforma dorada", 400 - TextoSimple::obtenerAnchoTexto("OBJETIVO: Llega a la plataforma dorada", 20) / 2, 450, colorDorado);
    
    // Instrucción para comenzar
    renderizarTextoSDLTTF("PRESIONA ESPACIO PARA COMENZAR", 400 - TextoSimple::obtenerAnchoTexto("PRESIONA ESPACIO PARA COMENZAR", 28) / 2, 520, colorRojoClaro);
    
    // Créditos
    renderizarTextoSDLTTF("Desarrollado en C++ con SDL2", 400 - TextoSimple::obtenerAnchoTexto("Desarrollado en C++ con SDL2", 14) / 2, 570, colorGrisAzul);
}

void Juego::renderizarPantallaFinal() {
    // Fondo dorado
    SDL_SetRenderDrawColor(renderizador, 255, 215, 0, 255);
    SDL_RenderClear(renderizador);
    
    SDL_Color colorNegro = {0, 0, 0, 255};
    SDL_Color colorGrisOscuro = {50, 50, 50, 255};
    SDL_Color colorMarron = {100, 50, 0, 255};
    SDL_Color colorVerdeOscuro = {0, 100, 0, 255};
    SDL_Color colorMorado = {150, 0, 150, 255};
    SDL_Color colorRojoOscuro = {200, 0, 0, 255};
    SDL_Color colorGris = {100, 100, 100, 255};

    // Título de felicitaciones
    renderizarTextoSDLTTF("FELICITACIONES", 400 - TextoSimple::obtenerAnchoTexto("FELICITACIONES", 48) / 2, 100, colorNegro);
    
    // Mensaje de completado
    renderizarTextoSDLTTF("Has completado el Nivel 1", 400 - TextoSimple::obtenerAnchoTexto("Has completado el Nivel 1", 28) / 2, 170, colorGrisOscuro);
    renderizarTextoSDLTTF("EL VALLE DEL TERROR ABSOLUTO", 400 - TextoSimple::obtenerAnchoTexto("EL VALLE DEL TERROR ABSOLUTO", 24) / 2, 210, colorGrisOscuro);
    
    // Información educativa
    renderizarTextoSDLTTF("Aprendiste sobre:", 400 - TextoSimple::obtenerAnchoTexto("Aprendiste sobre:", 22) / 2, 270, colorMarron);
    renderizarTextoSDLTTF("Matematicas - Valor Absoluto", 400 - TextoSimple::obtenerAnchoTexto("Matematicas - Valor Absoluto", 20) / 2, 300, colorMarron);
    
    // Estadísticas del juego
    renderizarTextoSDLTTF("Habilidades desarrolladas:", 400 - TextoSimple::obtenerAnchoTexto("Habilidades desarrolladas:", 18) / 2, 350, colorVerdeOscuro);
    renderizarTextoSDLTTF("- Coordinacion y reflejos", 400 - TextoSimple::obtenerAnchoTexto("- Coordinacion y reflejos", 16) / 2, 375, colorVerdeOscuro);
    renderizarTextoSDLTTF("- Resolucion de problemas", 400 - TextoSimple::obtenerAnchoTexto("- Resolucion de problemas", 16) / 2, 395, colorVerdeOscuro);
    renderizarTextoSDLTTF("- Perseverancia", 400 - TextoSimple::obtenerAnchoTexto("- Perseverancia", 16) / 2, 415, colorVerdeOscuro);
    
    // Próximos pasos
    renderizarTextoSDLTTF("Proximamente: Nivel 2", 400 - TextoSimple::obtenerAnchoTexto("Proximamente: Nivel 2", 20) / 2, 460, colorMorado);
    renderizarTextoSDLTTF("Las Ruinas de la Sabiduria Antigua", 400 - TextoSimple::obtenerAnchoTexto("Las Ruinas de la Sabiduria Antigua", 18) / 2, 485, colorMorado);
    
    // Instrucción para salir
    renderizarTextoSDLTTF("Presiona ESC para salir", 400 - TextoSimple::obtenerAnchoTexto("Presiona ESC para salir", 22) / 2, 530, colorRojoOscuro);
    
    // Créditos
    renderizarTextoSDLTTF("Gracias por jugar", 400 - TextoSimple::obtenerAnchoTexto("Gracias por jugar", 16) / 2, 570, colorGris);
}

void Juego::limpiar() {
    // Limpiar SDL_ttf
    if (fuente) {
        TTF_CloseFont(fuente);
        fuente = nullptr;
    }
    TTF_Quit();
    
    if (renderizador) {
        SDL_DestroyRenderer(renderizador);
        renderizador = nullptr;
    }
    
    if (ventana) {
        SDL_DestroyWindow(ventana);
        ventana = nullptr;
    }
    
    cout << "Recursos del juego liberados" << endl;
}
