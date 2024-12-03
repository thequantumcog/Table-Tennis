#include "main.hpp"

int main() {
    int score =0;
    State gameState = INPUT; // NOTE: INPUT,MENU,GAME,SCOREMENU

    InitWindow(screenWidth, screenHeight, "Ping Pong!");
    InitAudioDevice();
    loadResources();
    ToggleFullscreen();
    SetTargetFPS(60);
    bool exitWindow = false;

    while (!WindowShouldClose() && !exitWindow) {
        BeginDrawing();
        if(gameState == INPUT)
            inputMenu(gameState);
        else if(gameState == MENU){
            Menu(gameState,exitWindow);
        }
        else if(gameState == SETTINGS){
            options(gameState);
        }
        else if(gameState==GAME){
            beginGame(score,gameState,exitWindow);
        }
        else if(gameState==SCOREMENU)
            ScoreMenu(gameState);
        EndDrawing();
    }

    writeScore();
    unloadResources();
    CloseAudioDevice();
    CloseWindow();  

    return 0;
}
