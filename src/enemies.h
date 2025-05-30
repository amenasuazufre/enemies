#ifndef ENEMIES_H
#define ENEMIES_H

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class enemy {
public:
Enemy(int x, int y, int speed);
void update(int playerX, int playerY);
void render(SDL_Renderer* renderer);
SDL_Point getPosition() const;

private:

SDL_Point posisition;
int speed;


};
