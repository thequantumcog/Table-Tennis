#ifndef MAIN_H
#define MAIN_H
#define STORAGE_DATA_FILE   "playerData"   // Storage file

#include "raylib.h"

const int screenWidth = 1920;
const int screenHeight = 1080;

enum MenuOption { START_GAME, OPTIONS,SCORES, EXIT, TOTAL_OPTIONS };
typedef struct Ball{
        Vector2 pos;
        Vector2 speed;
        float radius;
        Color color;
        bool thrown;
        bool canCollide;
} Ball;
typedef struct Paddle{
        Vector2 pos;
        float speed;
        float radius;
        Color color;
        bool hit;
} Paddle;


//Function Declaration
void loadResources();
void unloadResources();
void beginGame(int &score,int &gameState);
void ScoreMenu(int &gameState);
void Menu(int &gameState,bool &exitWindow);
#endif // MAIN_H

