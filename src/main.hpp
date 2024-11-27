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

// Shenanigans

extern Texture2D board,btn_play, btn_options, btn_score, btn_exit, backgroundTexture, ballTexture, paddleTexture,background_wood;
const int scoreCapacity = 100;
const int PBCapacity = 100;
const int containers = 2;
//extern std::string personalBest[1][1];
extern int hiScore;
extern int pbSI;
extern std::string playerBest[PBCapacity][containers]; 
extern std::string previousScores [scoreCapacity][containers];



//Function Declaration
void loadResources();
void unloadResources();
void beginGame(int &score,State &gameState);
void ScoreMenu(State &gameState);
void Menu(State &gameState,bool &exitWindow);
void input(State &gameState);
void initDB(char lowerName[]);
//
void readScore();
void writeScore();
void updateScore(int score);
//
#endif // MAIN_H

