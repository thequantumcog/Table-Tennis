#include "main.hpp"
#include <raylib.h>

int pos = 1;
Vector2 BallSpeed = {700.0f,0.0f};
void options(State &gameState){
    DrawTexture(background_wood, 0,0,WHITE);
    DrawTexture(board, screenWidth/2.0f - 360, 230, WHITE);
    DrawTextEx(font, "Ball Speed",{screenWidth/2.0f-MeasureTextEx(font,"Ball Speed",40,2).x/2.0f+10.0f,screenHeight/2.0f-250},40,2, WHITE);
    DrawText("Slow",screenWidth/2.0f - MeasureText("Slow", 40)/2.0f - 100.0f,screenHeight/2.0f-150 , 40, WHITE);
    DrawText("Medium",screenWidth/2.0f - MeasureText("Medium", 40)/2.0f + 100.0f,screenHeight/2.0f-150 , 40, WHITE);
    DrawText("Fast",screenWidth/2.0f - MeasureText("Fast", 40)/2.0f+10.0f,screenHeight/2.0f-90 , 40, WHITE);
    if(pos == 0)
        DrawTexture(selector,screenWidth / 2.0f - 190.0f, screenHeight / 2.0f - 150.0f,WHITE);
    else if (pos == 1)
        DrawTexture(selector,screenWidth / 2.0f - 10.0f , screenHeight / 2.0f - 150.0f,WHITE);
    else
        DrawTexture(selector,screenWidth / 2.0f - 80.0f , screenHeight / 2.0f - 90.0f,WHITE);

    if(IsKeyPressed(KEY_RIGHT)){
        if(pos==2)
            pos=0;
        else
        pos++;
    }
    else if(IsKeyPressed(KEY_LEFT)){
        if(pos==0)
            pos=2;
        else
        pos--;
    }
    else if(IsKeyPressed(KEY_BACKSPACE))
        gameState = MENU;
else if(IsKeyPressed(KEY_ENTER)){
    if(pos == 0)
        BallSpeed.x = 400.0f;
    else if(pos ==1)
        BallSpeed.x = 700.0f;
    else
        BallSpeed.x = 1500.0f;

}
}
