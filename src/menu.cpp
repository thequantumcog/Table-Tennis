#include "main.hpp"
#include <raylib.h>

#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

int btn_height = 403;
int btn_width = 367;

float frameHeight = (float)btn_height / NUM_FRAMES;

// Define an array of button bounds for easier management
Rectangle btnBounds[] = {
    { screenWidth/2.0f - btn_width/2.0f, 350 - frameHeight / 2.0f, (float)btn_width, frameHeight }, // Play
    { screenWidth/2.0f - btn_width/2.0f, 500 - frameHeight / 2.0f, (float)btn_width, frameHeight }, // Options
    { screenWidth/2.0f - btn_width/2.0f, 650 - frameHeight / 2.0f, (float)btn_width, frameHeight }, // Score
    { screenWidth/2.0f - btn_width/2.0f, 800 - frameHeight / 2.0f, (float)btn_width, frameHeight }  // Exit
};


int CurSelection=0;
int btnStates[4] = { 0 };       // Button states: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
bool btnActions[4] = { false }; // Button actions

Vector2 mousePoint = { 0.0f, 0.0f };

static bool keyboardUsed=0;
void menuInput(State &gameState, bool &exitWindow) {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    Texture2D btnTextures[] = { btn_play, btn_options, btn_score, btn_exit };
    mousePoint = GetMousePosition();
    DrawTexture(background_wood, 0, 0, WHITE);
    DrawTexture(board, screenWidth/2.0f - 360, 230, WHITE);

    if(IsKeyPressed(KEY_DOWN)&& CurSelection !=3){
        CurSelection++;
        keyboardUsed=1;
    }
    if(IsKeyPressed(KEY_UP) && CurSelection != 0){
        CurSelection--;
        keyboardUsed=1;
    }



    for (int i = 0; i < 4; i++) {
        btnActions[i] = false;

        if(GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
            keyboardUsed=0;
        // Check button state
        if(!keyboardUsed && CheckCollisionPointRec(mousePoint, btnBounds[i])){
            CurSelection=i;
        }
        if (CurSelection==i) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) btnStates[i] = 2;
            else btnStates[i] = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) btnActions[i] = true;
        } else {
            btnStates[i] = 0;
        }

        // Perform button-specific actions
        if (btnActions[i]) {
            switch (i) {
                case 0: // Play button
                    gameState = GAME;
                    break;
                case 1: // Options button
                    break;
                case 2: // Score button
                    gameState = SCOREMENU;
                    break;
                case 3: // Exit button
                    exitWindow = true;
                    break;
            }
        }

        // Calculate button frame rectangle to draw
        Rectangle sourceRec = { 0, btnStates[i] * frameHeight, (float)btn_width, frameHeight };
        DrawTextureRec(btnTextures[i], sourceRec, (Vector2){ btnBounds[i].x, btnBounds[i].y }, WHITE);
    }
}

void Menu(State &gameState, bool &exitWindow) {
    menuInput(gameState, exitWindow);
}
