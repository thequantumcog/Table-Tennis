#ifndef MAIN_H
#define MAIN_H
#define STORAGE_DATA_FILE   "playerData"   // Storage file

#include "raylib.h"
#include <string>
#include <fstream>
#include <iostream>


const Color background = ColorFromHSV(0.12, 0.20, 0.20);
const Color scoreColor = ColorFromHSV(191.25f, 0.9697f, 0.9059f);
const float wallSize = 45.0f;
const float paddleRadius = 59.5f;

extern Vector2 BallSpeed;

#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

const int btn_height = 403;
const int btn_width = 367;
const float frameHeight = (float)btn_height / NUM_FRAMES;

const int screenWidth = 1920;
const int screenHeight = 1080;

enum State {INPUT,MENU,GAME,SCOREMENU,SETTINGS};
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

extern Texture2D board,leaderboard,nameplate, backgroundTexture, ballTexture, paddleTexture,background_wood;
extern Texture2D btn_newgame,btn_options,btn_play,btn_score,btn_exit,btn_menu,btn_continue;
extern Font font;
const int PBCapacity = 100;
const int containers = 2;
extern int pbIndex;
extern std::string playerBest[PBCapacity][containers]; 
extern Texture2D btnTextures[4],selector;
extern Sound hit,hit2,paddlesound;

//Function Declaration
void loadResources();
void unloadResources();
void beginGame(int &score,State &gameState,bool &exitWindow);
void ScoreMenu(State &gameState);
void Menu(State &gameState,bool &exitWindow);
void options(State &gameState);
void input(State &gameState);
void drawPauseMenu(State &gameState, bool &game_paused,int &score, Ball &ball,Paddle &paddle,bool &exitWindow);
void initDB(char lowerName[]);
void handleMenu(bool * btnActions,Texture2D * btnTextures,int *btnStates,Rectangle * btnBounds,bool &keyboardUsed,int &CurSelection,bool menuType);
void readScore();
void writeScore();
void updateScore(int score);
//
#endif // MAIN_H

