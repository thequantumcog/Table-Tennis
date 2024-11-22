#ifndef MAIN_H
#define MAIN_H
#define STORAGE_DATA_FILE   "playerData"   // Storage file

#include "raylib.h"
#include <iostream>
#include <fstream>

const int screenWidth = 1920;
const int screenHeight = 1080;

enum MenuOption {START_GAME, OPTIONS,SCORES, EXIT, TOTAL_OPTIONS };
enum State {INPUT,MENU,GAME,SCOREMENU};
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
void beginGame(int &score,State &gameState);
void ScoreMenu(State &gameState);
void Menu(State &gameState,bool &exitWindow);
void input(State &gameState);
void initializeDB(char name[]);
void ChangeScore(int score);
void WriteScore();
#endif // MAIN_H

