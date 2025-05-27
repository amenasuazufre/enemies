/*
 * Implementación de la clase TextoSimple
 */

#include "TextoSimple.h"
#include <cctype>

void TextoSimple::establecerColor(SDL_Renderer* renderizador, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderizador, r, g, b, 255);
}

void TextoSimple::renderizarLetra(SDL_Renderer* renderizador, char letra, int x, int y, int tamaño) {
    letra = toupper(letra);
    
    // Definir patrones de letras usando una matriz 5x7
    // 1 = píxel encendido, 0 = píxel apagado
    int patrones[128][7][5] = {0}; // Inicializar todo en 0
    
    // Letra A
    patrones['A'][0][1] = patrones['A'][0][2] = patrones['A'][0][3] = 1;
    patrones['A'][1][0] = patrones['A'][1][4] = 1;
    patrones['A'][2][0] = patrones['A'][2][4] = 1;
    patrones['A'][3][0] = patrones['A'][3][1] = patrones['A'][3][2] = patrones['A'][3][3] = patrones['A'][3][4] = 1;
    patrones['A'][4][0] = patrones['A'][4][4] = 1;
    patrones['A'][5][0] = patrones['A'][5][4] = 1;
    patrones['A'][6][0] = patrones['A'][6][4] = 1;
    
    // Letra E
    patrones['E'][0][0] = patrones['E'][0][1] = patrones['E'][0][2] = patrones['E'][0][3] = patrones['E'][0][4] = 1;
    patrones['E'][1][0] = 1;
    patrones['E'][2][0] = 1;
    patrones['E'][3][0] = patrones['E'][3][1] = patrones['E'][3][2] = patrones['E'][3][3] = 1;
    patrones['E'][4][0] = 1;
    patrones['E'][5][0] = 1;
    patrones['E'][6][0] = patrones['E'][6][1] = patrones['E'][6][2] = patrones['E'][6][3] = patrones['E'][6][4] = 1;
    
    // Letra D
    patrones['D'][0][0] = patrones['D'][0][1] = patrones['D'][0][2] = patrones['D'][0][3] = 1;
    patrones['D'][1][0] = patrones['D'][1][4] = 1;
    patrones['D'][2][0] = patrones['D'][2][4] = 1;
    patrones['D'][3][0] = patrones['D'][3][4] = 1;
    patrones['D'][4][0] = patrones['D'][4][4] = 1;
    patrones['D'][5][0] = patrones['D'][5][4] = 1;
    patrones['D'][6][0] = patrones['D'][6][1] = patrones['D'][6][2] = patrones['D'][6][3] = 1;
    
    // Letra U
    patrones['U'][0][0] = patrones['U'][0][4] = 1;
    patrones['U'][1][0] = patrones['U'][1][4] = 1;
    patrones['U'][2][0] = patrones['U'][2][4] = 1;
    patrones['U'][3][0] = patrones['U'][3][4] = 1;
    patrones['U'][4][0] = patrones['U'][4][4] = 1;
    patrones['U'][5][0] = patrones['U'][5][4] = 1;
    patrones['U'][6][1] = patrones['U'][6][2] = patrones['U'][6][3] = 1;
    
    // Letra C
    patrones['C'][0][1] = patrones['C'][0][2] = patrones['C'][0][3] = 1;
    patrones['C'][1][0] = patrones['C'][1][4] = 1;
    patrones['C'][2][0] = 1;
    patrones['C'][3][0] = 1;
    patrones['C'][4][0] = 1;
    patrones['C'][5][0] = patrones['C'][5][4] = 1;
    patrones['C'][6][1] = patrones['C'][6][2] = patrones['C'][6][3] = 1;
    
    // Letra T
    patrones['T'][0][0] = patrones['T'][0][1] = patrones['T'][0][2] = patrones['T'][0][3] = patrones['T'][0][4] = 1;
    patrones['T'][1][2] = 1;
    patrones['T'][2][2] = 1;
    patrones['T'][3][2] = 1;
    patrones['T'][4][2] = 1;
    patrones['T'][5][2] = 1;
    patrones['T'][6][2] = 1;
    
    // Letra I
    patrones['I'][0][0] = patrones['I'][0][1] = patrones['I'][0][2] = patrones['I'][0][3] = patrones['I'][0][4] = 1;
    patrones['I'][1][2] = 1;
    patrones['I'][2][2] = 1;
    patrones['I'][3][2] = 1;
    patrones['I'][4][2] = 1;
    patrones['I'][5][2] = 1;
    patrones['I'][6][0] = patrones['I'][6][1] = patrones['I'][6][2] = patrones['I'][6][3] = patrones['I'][6][4] = 1;
    
    // Letra V
    patrones['V'][0][0] = patrones['V'][0][4] = 1;
    patrones['V'][1][0] = patrones['V'][1][4] = 1;
    patrones['V'][2][0] = patrones['V'][2][4] = 1;
    patrones['V'][3][0] = patrones['V'][3][4] = 1;
    patrones['V'][4][1] = patrones['V'][4][3] = 1;
    patrones['V'][5][1] = patrones['V'][5][3] = 1;
    patrones['V'][6][2] = 1;
    
    // Letra O
    patrones['O'][0][1] = patrones['O'][0][2] = patrones['O'][0][3] = 1;
    patrones['O'][1][0] = patrones['O'][1][4] = 1;
    patrones['O'][2][0] = patrones['O'][2][4] = 1;
    patrones['O'][3][0] = patrones['O'][3][4] = 1;
    patrones['O'][4][0] = patrones['O'][4][4] = 1;
    patrones['O'][5][0] = patrones['O'][5][4] = 1;
    patrones['O'][6][1] = patrones['O'][6][2] = patrones['O'][6][3] = 1;
    
    // Letra J
    patrones['J'][0][4] = 1;
    patrones['J'][1][4] = 1;
    patrones['J'][2][4] = 1;
    patrones['J'][3][4] = 1;
    patrones['J'][4][4] = 1;
    patrones['J'][5][0] = patrones['J'][5][4] = 1;
    patrones['J'][6][1] = patrones['J'][6][2] = patrones['J'][6][3] = 1;
    
    // Letra G
    patrones['G'][0][1] = patrones['G'][0][2] = patrones['G'][0][3] = 1;
    patrones['G'][1][0] = patrones['G'][1][4] = 1;
    patrones['G'][2][0] = 1;
    patrones['G'][3][0] = patrones['G'][3][2] = patrones['G'][3][3] = patrones['G'][3][4] = 1;
    patrones['G'][4][0] = patrones['G'][4][4] = 1;
    patrones['G'][5][0] = patrones['G'][5][4] = 1;
    patrones['G'][6][1] = patrones['G'][6][2] = patrones['G'][6][3] = 1;
    
    // Letra M
    patrones['M'][0][0] = patrones['M'][0][4] = 1;
    patrones['M'][1][0] = patrones['M'][1][1] = patrones['M'][1][3] = patrones['M'][1][4] = 1;
    patrones['M'][2][0] = patrones['M'][2][2] = patrones['M'][2][4] = 1;
    patrones['M'][3][0] = patrones['M'][3][4] = 1;
    patrones['M'][4][0] = patrones['M'][4][4] = 1;
    patrones['M'][5][0] = patrones['M'][5][4] = 1;
    patrones['M'][6][0] = patrones['M'][6][4] = 1;
    
    // Letra N
    patrones['N'][0][0] = patrones['N'][0][4] = 1;
    patrones['N'][1][0] = patrones['N'][1][1] = patrones['N'][1][4] = 1;
    patrones['N'][2][0] = patrones['N'][2][2] = patrones['N'][2][4] = 1;
    patrones['N'][3][0] = patrones['N'][3][2] = patrones['N'][3][4] = 1;
    patrones['N'][4][0] = patrones['N'][4][3] = patrones['N'][4][4] = 1;
    patrones['N'][5][0] = patrones['N'][5][3] = patrones['N'][5][4] = 1;
    patrones['N'][6][0] = patrones['N'][6][4] = 1;
    
    // Letra P
    patrones['P'][0][0] = patrones['P'][0][1] = patrones['P'][0][2] = patrones['P'][0][3] = 1;
    patrones['P'][1][0] = patrones['P'][1][4] = 1;
    patrones['P'][2][0] = patrones['P'][2][4] = 1;
    patrones['P'][3][0] = patrones['P'][3][1] = patrones['P'][3][2] = patrones['P'][3][3] = 1;
    patrones['P'][4][0] = 1;
    patrones['P'][5][0] = 1;
    patrones['P'][6][0] = 1;
    
    // Letra R
    patrones['R'][0][0] = patrones['R'][0][1] = patrones['R'][0][2] = patrones['R'][0][3] = 1;
    patrones['R'][1][0] = patrones['R'][1][4] = 1;
    patrones['R'][2][0] = patrones['R'][2][4] = 1;
    patrones['R'][3][0] = patrones['R'][3][1] = patrones['R'][3][2] = patrones['R'][3][3] = 1;
    patrones['R'][4][0] = patrones['R'][4][2] = 1;
    patrones['R'][5][0] = patrones['R'][5][3] = 1;
    patrones['R'][6][0] = patrones['R'][6][4] = 1;
    
    // Letra S
    patrones['S'][0][1] = patrones['S'][0][2] = patrones['S'][0][3] = patrones['S'][0][4] = 1;
    patrones['S'][1][0] = 1;
    patrones['S'][2][0] = 1;
    patrones['S'][3][1] = patrones['S'][3][2] = patrones['S'][3][3] = 1;
    patrones['S'][4][4] = 1;
    patrones['S'][5][4] = 1;
    patrones['S'][6][0] = patrones['S'][6][1] = patrones['S'][6][2] = patrones['S'][6][3] = 1;
    
    // Letra L
    patrones['L'][0][0] = 1;
    patrones['L'][1][0] = 1;
    patrones['L'][2][0] = 1;
    patrones['L'][3][0] = 1;
    patrones['L'][4][0] = 1;
    patrones['L'][5][0] = 1;
    patrones['L'][6][0] = patrones['L'][6][1] = patrones['L'][6][2] = patrones['L'][6][3] = patrones['L'][6][4] = 1;
    
    // Letra F
    patrones['F'][0][0] = patrones['F'][0][1] = patrones['F'][0][2] = patrones['F'][0][3] = patrones['F'][0][4] = 1;
    patrones['F'][1][0] = 1;
    patrones['F'][2][0] = 1;
    patrones['F'][3][0] = patrones['F'][3][1] = patrones['F'][3][2] = patrones['F'][3][3] = 1;
    patrones['F'][4][0] = 1;
    patrones['F'][5][0] = 1;
    patrones['F'][6][0] = 1;
    
    // Espacio
    // (ya está inicializado en 0)
    
    // Dos puntos (:)
    patrones[':'][2][2] = 1;
    patrones[':'][4][2] = 1;
    
    // Renderizar el patrón
    int pixelSize = tamaño / 7;
    if (pixelSize < 1) pixelSize = 1;
    
    for (int fila = 0; fila < 7; fila++) {
        for (int col = 0; col < 5; col++) {
            if (patrones[letra][fila][col]) {
                SDL_Rect pixel = {
                    x + col * pixelSize,
                    y + fila * pixelSize,
                    pixelSize,
                    pixelSize
                };
                SDL_RenderFillRect(renderizador, &pixel);
            }
        }
    }
}

int TextoSimple::obtenerAnchoLetra(char letra, int tamaño) {
    if (letra == ' ') {
        return tamaño / 2;
    }
    return (tamaño * 5) / 7 + 2; // 5 píxeles de ancho + espaciado
}

void TextoSimple::renderizarTexto(SDL_Renderer* renderizador, const std::string& texto, int x, int y, int tamaño) {
    int posX = x;
    for (char c : texto) {
        if (c != ' ') {
            renderizarLetra(renderizador, c, posX, y, tamaño);
        }
        posX += obtenerAnchoLetra(c, tamaño);
    }
}

int TextoSimple::obtenerAnchoTexto(const std::string& texto, int tamaño) {
    int ancho = 0;
    for (char c : texto) {
        ancho += obtenerAnchoLetra(c, tamaño);
    }
    return ancho;
}

void TextoSimple::renderizarTextoCentrado(SDL_Renderer* renderizador, const std::string& texto, int centroX, int y, int tamaño) {
    int anchoTexto = obtenerAnchoTexto(texto, tamaño);
    int x = centroX - anchoTexto / 2;
    renderizarTexto(renderizador, texto, x, y, tamaño);
}
