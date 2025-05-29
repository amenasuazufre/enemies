/*
 * Implementación de la clase PanelLateral
 */

#include "PanelLateral.h"
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

void PanelLateral::inicializar(TTF_Font* fuenteRef) {
    if (fuenteRef) {
        fuente = fuenteRef;
    } else {
        cout << "Error: Fuente de titulo invalida pasada a PanelLateral::inicializar" << endl;
        cout << SDL_GetError();
    }

    // Cargar fuente para el cuerpo del texto
    fuenteCuerpo = TTF_OpenFont("src/data/fonts/Recoleta-Regular.ttf", 18);
    if (!fuenteCuerpo) {
        cout << "Error al cargar fuente de cuerpo para PanelLateral: " << TTF_GetError() << endl;
        cout << SDL_GetError();
    }

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
    if (!fuente || !fuenteCuerpo || !renderizador) return; // Asegurar que las fuentes sean cargadas.
    
    // Título
    SDL_Color colorBlanco = {255, 255, 255, 255};
    SDL_Color colorNegro = {0, 0, 0, 255};
    
    // Renderizar título
    SDL_Surface* superficieTitulo = TTF_RenderText_Solid(fuente, "INFORMACION", colorBlanco);
    if (superficieTitulo) {
        SDL_Texture* texturaTitulo = SDL_CreateTextureFromSurface(renderizador, superficieTitulo);
        if (texturaTitulo) {
            SDL_Rect tituloRect;
            // Centrar el titulo horizontalmente
            TTF_SizeText(fuente, "INFORMACION", &tituloRect.w, &tituloRect.h);
            tituloRect.x = x + (ancho - tituloRect.w) / 2;
            tituloRect.y = y + 10;
            SDL_RenderCopy(renderizador, texturaTitulo, nullptr, &tituloRect);
            SDL_DestroyTexture(texturaTitulo);
        }
        SDL_FreeSurface(superficieTitulo);
    }
    
    // Contenido del texto
    int posY = y + 40;
    int espaciadoLinea = 18;
    
    for (const string& linea : lineasTexto) {
        if (posY > y + alto - 20) break; // Previene renderización fuera del panel
        
        SDL_Surface* superficieLinea = TTF_RenderText_Solid(fuenteCuerpo, linea.c_str(), colorNegro);
        if (superficieLinea) {
            SDL_Texture* texturaLinea = SDL_CreateTextureFromSurface(renderizador, superficieLinea);
            if (texturaLinea) {
                SDL_Rect lineaRect = {x + 10, posY, superficieLinea->w, superficieLinea->h};
                SDL_RenderCopy(renderizador, texturaLinea, nullptr, &lineaRect);
                SDL_DestroyTexture(texturaLinea);
            }
            SDL_FreeSurface(superficieLinea);
        }
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
    
    if (informacion.empty() || !fuenteCuerpo) return;
    
    istringstream stream(informacion);
    string palabra;
    string lineaActual = "";
    const int anchoContenidoPanel = ancho - 20;
    
    while (stream >> palabra) {
        string testLine = lineaActual.empty() ? palabra : lineaActual + " " + palabra;
        int testWidth;
        TTF_SizeText(fuenteCuerpo, testLine.c_str(), &testWidth, nullptr);
        
        if (testWidth <= anchoContenidoPanel) {
            lineaActual = testLine;
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
