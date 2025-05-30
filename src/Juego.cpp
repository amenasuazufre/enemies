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
    int anchoNivel1Titulo, altoNivel1Titulo;
    TTF_SizeText(fuente, "NIVEL 1: EL VALLE DEL TERROR ABSOLUTO", &anchoNivel1Titulo, &altoNivel1Titulo);
    renderizarTextoSDLTTF("NIVEL 1: EL VALLE DEL TERROR ABSOLUTO", (ANCHO_VENTANA - anchoNivel1Titulo) / 2, 250, colorDorado);

    // Nivel 1
    int anchoNivel1Tema, altoNivel1Tema;
    TTF_SizeText(fuente, "Tema: Matematicas - Valor Absoluto", &anchoNivel1Tema, &altoNivel1Tema);
    renderizarTextoSDLTTF("Tema: Matematicas - Valor Absoluto", (ANCHO_VENTANA - anchoNivel1Tema) / 2, 280, colorVerdeClaro);

    // Controles
    int anchoControles, altoControles;
    TTF_SizeText(fuente, "CONTROLES:", &anchoControles, &altoControles);
    renderizarTextoSDLTTF("CONTROLES:", (ANCHO_VENTANA - anchoControles) / 2, 330, colorBlanco);

    renderizarTextoSDLTTF("Flechas ---> ", 200, 360, colorGrisClaro);
    renderizarTextoSDLTTF("Movimiento horizontal", 350, 360, colorGrisClaro);

    renderizarTextoSDLTTF("Flecha arriba o ESPACIO ---> ", 200, 385, colorGrisClaro);
    renderizarTextoSDLTTF("  Saltar", 500, 385, colorGrisClaro);

    renderizarTextoSDLTTF("R ---> ", 200, 410, colorGrisClaro);
    renderizarTextoSDLTTF("Reiniciar nivel", 350, 410, colorGrisClaro);

    // Objetivo
    int anchoObjetivo, altoObjetivo;
    TTF_SizeText(fuente, "OBJETIVO: Llega a la plataforma dorada", &anchoObjetivo, &altoObjetivo);
    renderizarTextoSDLTTF("OBJETIVO: Llega a la plataforma dorada", (ANCHO_VENTANA - anchoObjetivo) / 2, 450, colorDorado);

    // Instrucción para comenzar
    int anchoComenzar, altoComenzar;
    TTF_SizeText(fuente, "PRESIONA ESPACIO PARA COMENZAR", &anchoComenzar, &altoComenzar);
    renderizarTextoSDLTTF("PRESIONA ESPACIO PARA COMENZAR", (ANCHO_VENTANA - anchoComenzar) / 2, 520, colorRojoClaro);

    // Créditos
    int anchoCreditos, altoCreditos;
    TTF_SizeText(fuente, "Desarrollado en C++ con SDL2", &anchoCreditos, &altoCreditos);
    renderizarTextoSDLTTF("Desarrollado en C++ con SDL2", (ANCHO_VENTANA - anchoCreditos) / 2, 570, colorGrisAzul);
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
    int anchoFelicitaciones, altoFelicitaciones;
    TTF_SizeText(fuente, "FELICITACIONES", &anchoFelicitaciones, &altoFelicitaciones);
    renderizarTextoSDLTTF("FELICITACIONES", (ANCHO_VENTANA - anchoFelicitaciones) / 2, 100, colorNegro);
    
    // Mensaje de completado
    int anchoCompletado1, altoCompletado1;
    TTF_SizeText(fuente, "Has completado el Nivel 1", &anchoCompletado1, &altoCompletado1);
    renderizarTextoSDLTTF("Has completado el Nivel 1", (ANCHO_VENTANA - anchoCompletado1) / 2, 170, colorGrisOscuro);

    int anchoCompletado2, altoCompletado2;
    TTF_SizeText(fuente, "EL VALLE DEL TERROR ABSOLUTO", &anchoCompletado2, &altoCompletado2);
    renderizarTextoSDLTTF("EL VALLE DEL TERROR ABSOLUTO", (ANCHO_VENTANA - anchoCompletado2) / 2, 210, colorGrisOscuro);
    
    // Información educativa
    int anchoInfoEducativa1, altoInfoEducativa1;
    TTF_SizeText(fuente, "Aprendiste sobre:", &anchoInfoEducativa1, &altoInfoEducativa1);
    renderizarTextoSDLTTF("Aprendiste sobre:", (ANCHO_VENTANA - anchoInfoEducativa1) / 2, 270, colorMarron);

    int anchoInfoEducativa2, altoInfoEducativa2;
    TTF_SizeText(fuente, "Matematicas - Valor Absoluto", &anchoInfoEducativa2, &altoInfoEducativa2);
    renderizarTextoSDLTTF("Matematicas - Valor Absoluto", (ANCHO_VENTANA - anchoInfoEducativa2) / 2, 300, colorMarron);
    
    // Estadísticas del juego
    int anchoHabilidadesTitulo, altoHabilidadesTitulo;
    TTF_SizeText(fuente, "Habilidades desarrolladas:", &anchoHabilidadesTitulo, &altoHabilidadesTitulo);
    renderizarTextoSDLTTF("Habilidades desarrolladas:", (ANCHO_VENTANA - anchoHabilidadesTitulo) / 2, 350, colorVerdeOscuro);

    int anchoHabilidad1, altoHabilidad1;
    TTF_SizeText(fuente, "- Coordinacion y reflejos", &anchoHabilidad1, &altoHabilidad1);
    renderizarTextoSDLTTF("- Coordinacion y reflejos", (ANCHO_VENTANA - anchoHabilidad1) / 2, 375, colorVerdeOscuro);

    int anchoHabilidad2, altoHabilidad2;
    TTF_SizeText(fuente, "- Resolucion de problemas", &anchoHabilidad2, &altoHabilidad2);
    renderizarTextoSDLTTF("- Resolucion de problemas", (ANCHO_VENTANA - anchoHabilidad2) / 2, 395, colorVerdeOscuro);

    int anchoHabilidad3, altoHabilidad3;
    TTF_SizeText(fuente, "- Perseverancia", &anchoHabilidad3, &altoHabilidad3);
    renderizarTextoSDLTTF("- Perseverancia", (ANCHO_VENTANA - anchoHabilidad3) / 2, 415, colorVerdeOscuro);
    
    // Próximos pasos
    int anchoProximosPasos1, altoProximosPasos1;
    TTF_SizeText(fuente, "Proximamente: Nivel 2", &anchoProximosPasos1, &altoProximosPasos1);
    renderizarTextoSDLTTF("Proximamente: Nivel 2", (ANCHO_VENTANA - anchoProximosPasos1) / 2, 460, colorMorado);

    int anchoProximosPasos2, altoProximosPasos2;
    TTF_SizeText(fuente, "Las Ruinas de la Sabiduria Antigua", &anchoProximosPasos2, &altoProximosPasos2);
    renderizarTextoSDLTTF("Las Ruinas de la Sabiduria Antigua", (ANCHO_VENTANA - anchoProximosPasos2) / 2, 485, colorMorado);
    
    // Instrucción para salir
    int anchoSalir, altoSalir;
    TTF_SizeText(fuente, "Presiona ESC para salir", &anchoSalir, &altoSalir);
    renderizarTextoSDLTTF("Presiona ESC para salir", (ANCHO_VENTANA - anchoSalir) / 2, 530, colorRojoOscuro);
    
    // Créditos
    int anchoGracias, altoGracias;
    TTF_SizeText(fuente, "Gracias por jugar", &anchoGracias, &altoGracias);
    renderizarTextoSDLTTF("Gracias por jugar", (ANCHO_VENTANA - anchoGracias) / 2, 570, colorGris);
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
