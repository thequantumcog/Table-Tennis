#include "main.hpp"
#include <raylib.h>


// Define an array of button bounds for easier management
Rectangle btnBounds[] = {
    { (screenWidth - btn_width)/2.0, 350 - frameHeight / 2.0f, btn_width, frameHeight }, // Play
    { (screenWidth - btn_width)/2.0, 500 - frameHeight / 2.0f, btn_width, frameHeight }, // Options
    { (screenWidth - btn_width)/2.0, 650 - frameHeight / 2.0f, btn_width, frameHeight }, // Score
    { (screenWidth - btn_width)/2.0, 800 - frameHeight / 2.0f, btn_width, frameHeight }  // Exit
};

int CurSelection=0;
int btnStates[4] = { 0 };       // Button states: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
bool btnActions[4] = { false }; // Button actions
bool keyboardUsed=0;

bool isInputAllowed=0;
Texture2D btnTextures[] = { btn_play, btn_options, btn_score, btn_exit };
void Menu(State &gameState, bool &exitWindow) {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    DrawTexture(background_wood, 0, 0, WHITE);
    DrawTexture(board, screenWidth/2.0f - 360, 230, WHITE);
    if(IsKeyReleased(KEY_BACKSPACE))
        gameState = INPUT;

    handleMenu(btnActions, btnTextures, btnStates, btnBounds, keyboardUsed, CurSelection, 0);
    for (int i = 0; i < 4; i++) {
        if (btnActions[i]) {
            switch (i) {
                case 0: // Play button
                    gameState = GAME;
                    break;
                case 1: // Options button
                    gameState = SETTINGS;
                    break;
                case 2: // Score button
                    gameState = SCOREMENU;
                    break;
                case 3: // Exit button
                    exitWindow = true;
                    break;
            }
        }
    }
}
void handleMenu(bool * btnActions,Texture2D * btnTextures,int *btnStates,Rectangle * btnBounds,bool &keyboardUsed,int &CurSelection,bool menuType){
        Vector2 mousePoint = GetMousePosition();

        btnTextures[0] = btn_play;
        btnTextures[1] = btn_options;
        btnTextures[2] = btn_score;
        btnTextures[3] = btn_exit;
    if(menuType == 1){
        btnTextures[0] = btn_continue;
        btnTextures[1] = btn_newgame;
        btnTextures[2] = btn_menu;
    }

    for (int i = 0; i < 4; i++) {
        btnActions[i] = false; 
        
    }

    if(IsKeyPressed(KEY_DOWN)&& CurSelection !=3){
        CurSelection++;
        keyboardUsed=1;
    }
    if(IsKeyPressed(KEY_UP) && CurSelection != 0){
        CurSelection--;
        keyboardUsed=1;
    }

    for (int i = 0; i < 4; i++) {

        if(GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
            keyboardUsed=0;
        // Check button state
        if(!keyboardUsed && CheckCollisionPointRec(mousePoint, btnBounds[i])){
            CurSelection=i;
        }
        if (CurSelection==i) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) btnStates[i] = 2;
            else btnStates[i] = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_ENTER)) btnActions[i] = true;
        } else {
            btnStates[i] = 0;
        }
        Rectangle sourceRec = { 0, btnStates[i] * frameHeight, (float)btn_width, frameHeight };
        DrawTextureRec(btnTextures[i], sourceRec, (Vector2){ btnBounds[i].x, btnBounds[i].y }, WHITE);
    }
}
