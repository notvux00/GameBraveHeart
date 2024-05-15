#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const char* WINDOW_TITLE = "Brave Heart";

const char* TRAP_SPRITE_FILE = "assets/img/trap.png";
const int TRAP_CLIPS[][4] = {
    {  0, 0, 50, 50},
    { 50, 0, 50, 50},
    {100, 0, 50, 50},
    {150, 0, 50, 50}};
const int TRAP_FRAMES = sizeof(TRAP_CLIPS)/sizeof(int)/4;

enum GameStatus {
    MENU,
    GAME_LOOP,
    GAME_OVER,
    MENU_SCORE
};

#define START_BUTTON_X 485
#define START_BUTTON_Y 375
#define START_BUTTON_WIDTH 215
#define START_BUTTON_HEIGHT 82

#define SCORE_BUTTON_X 485
#define SCORE_BUTTON_Y 480
#define SCORE_BUTTON_WIDTH 215
#define SCORE_BUTTON_HEIGHT 82

#define EXIT_BUTTON_X 485
#define EXIT_BUTTON_Y 590
#define EXIT_BUTTON_WIDTH 215
#define EXIT_BUTTON_HEIGHT 82

#define PLAYAGAIN_BUTTON_X 490
#define PLAYAGAIN_BUTTON_Y 458
#define PLAYAGAIN_BUTTON_WIDTH 210
#define PLAYAGAIN_BUTTON_HEIGHT 123

#define MENU_BUTTON_X 490
#define MENU_BUTTON_Y 603
#define MENU_BUTTON_WIDTH 210
#define MENU_BUTTON_HEIGHT 123
#endif

