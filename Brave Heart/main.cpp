#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "defs.h"
#include "graphics.h"
#include "character.h"
#include "bullet.h"
#include "highscore.h"

using namespace std;

int main(int argc, char* args[]) {
    Graphics graphics;
    graphics.init();

    TTF_Font* font = graphics.loadFont("assets/font/PressStart2P-Regular.ttf", 20);
    TTF_Font* fontScore = graphics.loadFont("assets/font/Antonio-Bold.ttf", 40);
    SDL_Color colorWhite = {255, 255, 255, 255};
    SDL_Color colorBlack = {0, 0, 0, 255};

    Mix_Music* backgroundMusic = graphics.loadMusic("assets/music/megalovania.mp3");
    Mix_Music* menuMusic = graphics.loadMusic("assets/music/menumusic.mp3");
    Mix_Music* gameoverMusic = graphics.loadMusic("assets/music/gameovermusic.mp3");

    SDL_Texture* background = graphics.loadTexture("assets/img/map.png");
    SDL_Texture* menuBG = graphics.loadTexture("assets/img/menu.png");
    SDL_Texture* scoreBG = graphics.loadTexture("assets/img/scoremenu.png");
    SDL_Texture* gameoverBG = graphics.loadTexture("assets/img/gameover.png");
    SDL_Texture* character = graphics.loadTexture("assets/img/player.png");
    SDL_Texture* bullett = graphics.loadTexture("assets/img/bullet.png");
    SDL_Texture* trapTexture = graphics.loadTexture(TRAP_SPRITE_FILE);
    SDL_Texture* wallTop = graphics.loadTexture("assets/img/wallTop.png");
    SDL_Texture* wallBottom = graphics.loadTexture("assets/img/wallBottom.png");
    SDL_Texture* wallLeft = graphics.loadTexture("assets/img/wallLeft.png");
    SDL_Texture* wallRight = graphics.loadTexture("assets/img/wallRight.png");

    Character player;
    player.x = 600;
    player.y = 500;

    Sprite trap;
    trap.init(trapTexture, TRAP_FRAMES, TRAP_CLIPS);

    srand(time(nullptr));

    vector<Bullet> bullets;
    int bulletSpeed = 8;

    vector<Highscore> highscores = readHighscoresFromFile("assets/highscore.txt");

    GameStatus gameStatus = MENU;

    int score = 0;
    int lastSecond = SDL_GetTicks() / 500;


    bool quit = false;
    SDL_Event event;
    while (!quit) {

        switch (gameStatus) {
            case MENU:
                {
                    while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (mouseX >= START_BUTTON_X && mouseX <= START_BUTTON_X + START_BUTTON_WIDTH &&
                            mouseY >= START_BUTTON_Y && mouseY <= START_BUTTON_Y + START_BUTTON_HEIGHT) {
                            Mix_HaltMusic();
                            graphics.play(backgroundMusic);
                            gameStatus = GAME_LOOP;
                        }
                        else if (mouseX >= SCORE_BUTTON_X && mouseX <= SCORE_BUTTON_X + SCORE_BUTTON_WIDTH &&
                                 mouseY >= SCORE_BUTTON_Y && mouseY <= SCORE_BUTTON_Y + SCORE_BUTTON_HEIGHT) {
                            gameStatus = MENU_SCORE;
                        }
                        else if (mouseX >= EXIT_BUTTON_X && mouseX <= EXIT_BUTTON_X + EXIT_BUTTON_WIDTH &&
                                 mouseY >= EXIT_BUTTON_Y && mouseY <= EXIT_BUTTON_Y + EXIT_BUTTON_HEIGHT) {
                            quit = true;
                        }
                    }
                }

                graphics.play(menuMusic);
                graphics.prepareScene(menuBG);

                bullets.clear();

                graphics.presentScene();

                break;
                }

            case MENU_SCORE:
                {
                    while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            gameStatus = MENU;
                            }
                        }
                    }

                    string highScore1= to_string(highscores[0].score);
                    string highScore2 = to_string(highscores[1].score);
                    string highScore3 = to_string(highscores[2].score);

                    SDL_Texture* realHighScore1 = graphics.renderText(highScore1.c_str(), fontScore, colorBlack);
                    SDL_Texture* realHighScore2 = graphics.renderText(highScore2.c_str(), fontScore, colorBlack);
                    SDL_Texture* realHighScore3 = graphics.renderText(highScore3.c_str(), fontScore, colorBlack);

                    graphics.prepareScene(scoreBG);
                    graphics.renderTexture(realHighScore1, 710, 325);
                    graphics.renderTexture(realHighScore2, 710, 395);
                    graphics.renderTexture(realHighScore3, 710, 465);

                    SDL_DestroyTexture(realHighScore1);
                    SDL_DestroyTexture(realHighScore2);
                    SDL_DestroyTexture(realHighScore3);

                graphics.presentScene();

                break;
                }

            case GAME_LOOP:
                {
                    while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                int currentSecond = SDL_GetTicks() / 500;
                if (currentSecond > lastSecond) {
                    score++;
                    lastSecond = currentSecond;
                }

                string stringScore = "SCORE: " + to_string(score);

                SDL_Texture* Score = graphics.renderText(stringScore.c_str(), font, colorWhite);

                if (score >= 30) {
                    bulletSpeed = 10;
                }

                if (score >= 60) {
                    bulletSpeed = 12;
                }

                graphics.prepareScene(background);
                if (score >= 30 && score <=45) {
                    graphics.renderTexture(wallTop, 0,0);
                    graphics.renderTexture(wallBottom, 0,534);
                    graphics.renderTexture(wallLeft, 0,0);
                    graphics.renderTexture(wallRight, 1034,0);

                    for (int i = 4; i < NUM_COLLISION_BOXES; ++i) {
                    if (checkCollisionBox(player.x, player.y, CHARACTER_SIZE, collisionBoxes[i])) {
                        Mix_HaltMusic();
                        gameStatus = GAME_OVER;
                        break;
                        }
                    }
                }

                if (score >= 60 && score <=75) {
                    graphics.renderTexture(wallTop, 0,0);
                    graphics.renderTexture(wallBottom, 0,534);
                    graphics.renderTexture(wallLeft, 0,0);
                    graphics.renderTexture(wallRight, 1034,0);

                    for (int i = 4; i < NUM_COLLISION_BOXES; ++i) {
                    if (checkCollisionBox(player.x, player.y, CHARACTER_SIZE, collisionBoxes[i])) {
                        Mix_HaltMusic();
                        gameStatus = GAME_OVER;
                        break;
                        }
                    }
                }

                if (score >= 100) {
                    graphics.renderTexture(wallTop, 0,0);
                    graphics.renderTexture(wallBottom, 0,534);
                    graphics.renderTexture(wallLeft, 0,0);
                    graphics.renderTexture(wallRight, 1034,0);

                    for (int i = 4; i < NUM_COLLISION_BOXES; ++i) {
                    if (checkCollisionBox(player.x, player.y, CHARACTER_SIZE, collisionBoxes[i])) {
                        Mix_HaltMusic();
                        gameStatus = GAME_OVER;
                        break;
                        }
                    }
                }
                graphics.renderTexture(Score, 10, 10);
                SDL_DestroyTexture(Score);


                if (rand() % 20 == 0) {
                    Bullet bullet;
                    int side = std::rand() % 4;
                    switch (side) {
                        case 0:
                            bullet.x = std::rand() % SCREEN_WIDTH;
                            bullet.y = 0;
                            break;
                        case 1:
                            bullet.x = std::rand() % SCREEN_WIDTH;
                            bullet.y = SCREEN_HEIGHT;
                            break;
                        case 2:
                            bullet.x = 0;
                            bullet.y = std::rand() % SCREEN_HEIGHT;
                            break;
                        case 3:
                            bullet.x = SCREEN_WIDTH;
                            bullet.y = std::rand() % SCREEN_HEIGHT;
                            break;
                    }

                    bullet.fire(player.x, player.y, bulletSpeed);
                    bullets.push_back(bullet);
                }

                player.move();

                for (int i = 0; i < (int)bullets.size(); ++i) {
                    bullets[i].update();
                    if (bullets[i].isOffScreen()) {
                        bullets.erase(bullets.begin() + i);
                        --i;
                    }
                }

                for (size_t i = 0; i < bullets.size(); ++i) {
                    if (checkCollision(player.x, player.y, CHARACTER_SIZE, bullets[i].x, bullets[i].y, BULLETT_SIZE)) {
                        Mix_HaltMusic();
                        gameStatus = GAME_OVER;
                        break;
                    }
                }

                for (int i = 0; i < 4; ++i) {
                    if (checkCollisionBox(player.x, player.y, CHARACTER_SIZE, collisionBoxes[i])) {
                        Mix_HaltMusic();
                        gameStatus = GAME_OVER;
                        break;
                    }
                }

                graphics.renderTexture(character, player.x-10, player.y-10);
                trap.tick();
                graphics.render(100, 200, trap);
                graphics.render(250, 450, trap);
                graphics.render(1000, 150, trap);
                graphics.render(1100, 400, trap);

                for (int i = 0; i < (int)bullets.size(); ++i) {
                    graphics.renderTexture(bullett, bullets[i].x, bullets[i].y);
                }

                graphics.presentScene();

                break;
                }

            case GAME_OVER:
                {
                Highscore newScore;
                newScore.score = score;
                highscores.push_back(newScore);
                std::sort(highscores.begin(), highscores.end(), compareScore);
                if (highscores.size() > 10) {
                    highscores.resize(10);
                }
                writeHighscoresToFile("assets/highscore.txt", highscores);

                bullets.clear();
                score = 0;
                bulletSpeed = 8;

                graphics.play(gameoverMusic);
                graphics.prepareScene(gameoverBG);
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (mouseX >= PLAYAGAIN_BUTTON_X && mouseX <= PLAYAGAIN_BUTTON_X + PLAYAGAIN_BUTTON_WIDTH &&
                            mouseY >= PLAYAGAIN_BUTTON_Y && mouseY <= PLAYAGAIN_BUTTON_Y + PLAYAGAIN_BUTTON_HEIGHT) {
                            bullets.clear();

                            Mix_HaltMusic();

                            graphics.play(backgroundMusic);

                            gameStatus = GAME_LOOP;
                        }
                        else if (mouseX >= MENU_BUTTON_X && mouseX <= MENU_BUTTON_X + MENU_BUTTON_WIDTH &&
                                 mouseY >= MENU_BUTTON_Y && mouseY <= MENU_BUTTON_Y + MENU_BUTTON_HEIGHT) {
                            Mix_HaltMusic();

                            graphics.play(menuMusic);

                            gameStatus = MENU;
                        }
                    }
                }

                graphics.presentScene();

                break;
                }
        }
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(menuBG);
    SDL_DestroyTexture(scoreBG);
    SDL_DestroyTexture(gameoverBG);
    SDL_DestroyTexture(character);
    SDL_DestroyTexture(bullett);
    SDL_DestroyTexture(trapTexture);
    SDL_DestroyTexture(wallTop);
    SDL_DestroyTexture(wallBottom);
    SDL_DestroyTexture(wallLeft);
    SDL_DestroyTexture(wallRight);

    TTF_CloseFont(font);

    Mix_FreeMusic(backgroundMusic);
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(gameoverMusic);

    bullets.clear();

    graphics.quit();
    return 0;
}
