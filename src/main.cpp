#include "main.hpp"
#include <raylib.h>

int main() {
    int score =0;
    int gameState =0; // NOTE: 0 = inMenu, 1 = inGame, 3 = scoreMenu

    InitWindow(screenWidth, screenHeight, "Ping Pong!");

    loadResources();
    ToggleFullscreen();
    SetTargetFPS(60);
    bool exitWindow = false;

    while (!WindowShouldClose() && !exitWindow) {
        BeginDrawing();
        if(gameState == 0){
            Menu(gameState,exitWindow);
        }
        else if(gameState==1){
            beginGame(score,gameState);
        }
        else if(gameState==3)
            ScoreMenu(gameState);
        EndDrawing();
    }

    unloadResources();
    CloseWindow();  

    return 0;
}
