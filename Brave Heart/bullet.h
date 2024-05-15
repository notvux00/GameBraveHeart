#ifndef BULLET_H
#define BULLET_H

#define BULLETT_SIZE 20

#include<SDL.h>
#include"defs.h"

using namespace std;

struct Bullet {
    float x, y;
    float dx, dy;

    void fire(float characterX, float characterY, float speed) {

        float directionX = characterX - x;
        float directionY = characterY - y;

        float distance = sqrt(directionX * directionX + directionY * directionY);

        directionX /= distance;
        directionY /= distance;

        dx = directionX * speed;
        dy = directionY * speed;
    }

        void update() {
        x += dx;
        y += dy;
    }
        bool isOffScreen(){
            if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return true;
            return false;
        }
};
#endif // BULLET_H

