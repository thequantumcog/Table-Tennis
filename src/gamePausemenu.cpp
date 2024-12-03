#include "main.hpp"

int CurPSelection =0;
bool PkeyboardUsed =0;

Rectangle PbtnBounds[] = {
    { (screenWidth - btn_width)/2.0, 300 - frameHeight / 2.0f, btn_width, frameHeight }, // Play
    { (screenWidth - btn_width)/2.0, 450 - frameHeight / 2.0f, btn_width, frameHeight }, // Options
    { (screenWidth - btn_width)/2.0, 600 - frameHeight / 2.0f, btn_width, frameHeight }, // Score
    { (screenWidth - btn_width)/2.0, 750 - frameHeight / 2.0f, btn_width, frameHeight }  // Exit
};


int PbtnStates[3] = { 0 };       // Button states: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED

Vector2 mousePPoint = { 0.0f, 0.0f };

bool PbtnActions[4] = { false }; // Button actions
void drawPauseMenu(State &gameState, bool &gamePaused,int &score,Ball &ball,Paddle &paddle,bool &exitWindow){

    DrawTexture(board, screenWidth/2.0f-360, screenHeight/2.0f-360, WHITE);
    handleMenu(PbtnActions,btnTextures,PbtnStates, PbtnBounds, PkeyboardUsed, CurPSelection,1);
    for(int i=0;i<4;i++){

        // Perform button-specific actions
        if (PbtnActions[i]) {
            switch (i) {
                case 0: // Play button
                    gamePaused=0;
                    break;
                case 1: 
                    paddle = { { screenWidth - paddleRadius - wallSize, screenHeight / 2.0f }, 700.0f, 59.5f, BLACK, 0 }; // pos, size, speed, color, hit
                    ball = { { paddle.pos.x, paddle.pos.y }, { 500.0f, 0.0f }, 20.0f, PURPLE, 0 }; // pos, speed, radius, color, visible
                    score =0;
                    gamePaused=0;
                    break;
                case 2: 
                    gameState = MENU;
                    break;
                case 3: 
                    exitWindow = true;
                    break;
            }
        }

    }
}
