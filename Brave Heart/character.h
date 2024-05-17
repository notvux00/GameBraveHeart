#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_SIZE 35

#include<cmath>
#include<SDL.h>
#include"bullet.h"

using namespace std;

struct Character {
    float x, y;

    void move() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    x = mouseX;
    y = mouseY;
    }
};

const int NUM_COLLISION_BOXES = 8;
SDL_Rect collisionBoxes[NUM_COLLISION_BOXES] = {
    {100, 200, 50, 50},
    {250, 450, 50, 50},
    {1000, 150, 50, 50},
    {1100, 400, 50, 50},

    {0, 0, 1200, 110},//top
    {0, 590, 1200, 110},//bot
    {0, 0, 110, 700},//left
    {1090, 0, 110, 700}//right
};

bool checkCollision(float characterX, float characterY, int characterSize, float bulletX, float bulletY, int bulletSize) {
    float dx = characterX - bulletX;
    float dy = characterY - bulletY;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < (characterSize / 2 + bulletSize / 2);
}

bool checkCollisionBox(float characterX, float characterY, int characterSize, SDL_Rect box) {

    float characterCenterX = characterX + characterSize / 2;
    float characterCenterY = characterY + characterSize / 2;


    float boxCenterX = box.x + box.w / 2;
    float boxCenterY = box.y + box.h / 2;


    float dx = characterCenterX - boxCenterX;
    float dy = characterCenterY - boxCenterY;
    float combinedHalfWidths = (characterSize / 2) + (box.w / 2);
    float combinedHalfHeights = (characterSize / 2) + (box.h / 2);


    if (abs(dx) < combinedHalfWidths && abs(dy) < combinedHalfHeights) {
        return true;
    }

    return false;
}
#endif // CHARACTER_H
