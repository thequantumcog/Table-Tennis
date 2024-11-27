// TODO: Seprate Personal Index to argument i.e remove personal index from global variable
// TODO: Seprate DB to a new file


#include "main.hpp"
#include <raylib.h>

using namespace std;


int PersonalIndex=0;

void scoreCheckInput(State &gameState);
void CompareScore();

void ScoreMenu(State &gameState){
    scoreCheckInput(gameState);
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("High Score: "), 10, 50, 40, BLACK);
    DrawText(TextFormat("%i",hiScore), 10 + MeasureText("High Score: ", 40), 50, 40, BLACK);
    DrawText("Perosnal Best: ", 10, 150, 40, BLACK);
    DrawText(playerBest[pbSI][1].c_str(), 10 + MeasureText("Perosnal Best: ", 40), 150, 40, BLACK);
    DrawText("Score History: ", 10, 250, 40, BLACK);
    for(int i=0;i<scoreCapacity;i++){
        string name = previousScores[i][0];
        DrawText(name.c_str(), 10, 300+(i*50), 40, BLACK);
        DrawText(previousScores[i][1].c_str(), 50 + MeasureText(name.c_str(), 40), 300+(i*50), 40, BLACK);
        }

}

void scoreCheckInput(State &gameState){
    if(IsKeyPressed(KEY_BACKSPACE)){
        gameState=MENU;
    }
}
