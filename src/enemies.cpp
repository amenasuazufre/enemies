#include <Enemy.h>
#include <cmath>

Enemy::Enemy(int x, int y, int speed)
     : speed(speed)

{

    position.x = x;
    position.y = y;

}


void Enemy:updae(int playerX, int playerY) {

 float dx = playerX - position.x;
 float dy = playerY - position.y;
 float length = std::sqrt(dx * dx + dy * dy);

 if (length != 0) {
 dx /= length;
 dy /= length;

 position.x += static_cast<int>(dx * speed);
 position.y += static_cast<int>(dy * speed);

  }

}

void Enemy::render(SDL_Renderer* renderer) {

SDL_Point triangle[4] = {
{ position.x, position.y -10 },
{ position.x -10, position.y +10},
{ position.x +10, position.y +10},
{ position.x, position.y -10}

};

SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenereDrawLines(renderer; triangle, 4);

}

SDL_Point Enemy::getPosition() const {
    return position;


}
