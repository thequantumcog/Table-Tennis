#include "main.hpp"
#include <raylib.h>

int main() {
    int score =0;
    State gameState = INPUT; // NOTE: INPUT,MENU,GAME,SCOREMENU

    InitWindow(screenWidth, screenHeight, "Ping Pong!");

    loadResources();
    ToggleFullscreen();
    SetTargetFPS(60);
    bool exitWindow = false;

    while (!WindowShouldClose() && !exitWindow) {
        BeginDrawing();
        if(gameState == INPUT)
            input(gameState);
        else if(gameState == MENU){
            Menu(gameState,exitWindow);
        }
        else if(gameState==GAME){
            beginGame(score,gameState);
        }
        else if(gameState==SCOREMENU)
            ScoreMenu(gameState);
        EndDrawing();
    }

    writeScore();
    unloadResources();
    CloseWindow();  

    return 0;
}
