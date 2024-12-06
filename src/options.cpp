#include "main.hpp"

void cycleOptions(int maxOptions,int &controlVar);
void saveClicked(State &gameState);

int cps = 1;
int sBS=1;
bool onSpeed=1;
int saveState=0;
paddleColor pC=PBLUE;
Vector2 BallSpeed = {700.0f,0.0f};
Texture2D speed=selector,color=selector;
void options(State &gameState){
    DrawTexture(background_wood, 0,0,WHITE);
    DrawTexture(board, screenWidth/2.0f - 360, 230, WHITE);
    DrawTextEx(font, "Ball Speed",{screenWidth/2.0f-MeasureTextEx(font,"Ball Speed",40,2).x/2.0f+10.0f,screenHeight/2.0f-250},40,2, WHITE);
    DrawText("Slow",screenWidth/2.0f - MeasureText("Slow", 40)/2.0f - 100.0f,screenHeight/2.0f-150 , 40, WHITE);
    DrawText("Medium",screenWidth/2.0f - MeasureText("Medium", 40)/2.0f + 100.0f,screenHeight/2.0f-150 , 40, WHITE);
    DrawText("Fast",screenWidth/2.0f - MeasureText("Fast", 40)/2.0f+10.0f,screenHeight/2.0f-90 , 40, WHITE);
    if(onSpeed) {speed = selected; color = selector; cycleOptions(3,sBS);}
    if(sBS == 0)
        DrawTexture(speed,screenWidth / 2.0f - 190.0f, screenHeight / 2.0f - 150.0f,WHITE);
    else if (sBS == 1)
        DrawTexture(speed,screenWidth / 2.0f - 10.0f , screenHeight / 2.0f - 150.0f,WHITE);
    else
        DrawTexture(speed,screenWidth / 2.0f - 80.0f , screenHeight / 2.0f - 90.0f,WHITE);

    DrawTextEx(font, "Paddle Color",{screenWidth/2.0f-MeasureTextEx(font,"Paddle Color",40,2).x/2.0f+10.0f,screenHeight/2.0f-20},40,2, WHITE);
    DrawText("Red",screenWidth/2.0f - MeasureText("Red", 40)/2.0f - 100.0f,screenHeight/2.0f + 30.0f , 40, WHITE);
    DrawText("Blue",screenWidth/2.0f - MeasureText("Blue", 40)/2.0f + 100.0f,screenHeight/2.0f + 30.0f , 40, WHITE);
    if(!onSpeed) {color = selected; speed = selector; cycleOptions(2,cps);}
    if(cps == 0)
        DrawTexture(color,screenWidth / 2.0f - 190.0f, screenHeight / 2.0f + 30.0f,WHITE);
    else if (cps == 1)
        DrawTexture(color,screenWidth / 2.0f , screenHeight / 2.0f +30.0f,WHITE);

    Rectangle btnPos= { screenWidth/2.0f-90, screenHeight/2.0f + 200,202,79};
    Rectangle sourceRec = { 0, (float)saveState * 79, btnPos.width, btnPos.height };
    if(CheckCollisionPointRec(GetMousePosition(), btnPos)){
        saveState=1;
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            saveClicked(gameState);
    }
    else 
        saveState=0;
    DrawTextureRec(savesettings, sourceRec, (Vector2){btnPos.x,btnPos.y}, WHITE);

    if(IsKeyPressed(KEY_DOWN)){ if(onSpeed) onSpeed=0; else onSpeed=1;}
    else if(IsKeyPressed(KEY_UP)){if(!onSpeed) onSpeed=1; else onSpeed=0;}

    else if(IsKeyReleased(KEY_BACKSPACE))
        gameState = MENU;
    else if(IsKeyReleased(KEY_ENTER)){
        saveClicked(gameState);
    }
}
void cycleOptions(int maxOptions,int &controlVar){
    if(IsKeyPressed(KEY_RIGHT)){
        if(controlVar==maxOptions-1)
            controlVar=0;
        else
        controlVar++;
    }
    else if(IsKeyPressed(KEY_LEFT)){
        if(controlVar==0)
            controlVar=maxOptions-1;
        else
        controlVar--;
    }
}
void saveClicked(State &gameState){
    gameState = MENU;
    if(sBS == 0)
        BallSpeed.x = 400.0f;
    else if(sBS ==1)
        BallSpeed.x = 700.0f;
    else
        BallSpeed.x = 1500.0f;
    if(cps == 0)
        pC = PRED;
    else
        pC = PBLUE;
}
