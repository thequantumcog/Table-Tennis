#include "main.hpp"
#include <raylib.h>

MenuOption currentOption = START_GAME;
void drawMenu();
void menuInput(State &gameState, bool &exitWindow);

void Menu(State &gameState,bool &exitWindow){
        menuInput(gameState,exitWindow);
        drawMenu();
}


void drawMenu(){
        ClearBackground(RAYWHITE);

        DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 40) / 2, 100, 40, BLACK);

        Color startColor = (currentOption == START_GAME) ? RED : BLACK;
        Color optionsColor = (currentOption == OPTIONS) ? RED : BLACK;
        Color scoresColor = (currentOption == SCORES) ? RED : BLACK;
        Color exitColor = (currentOption == EXIT) ? RED : BLACK;

        DrawText("Start Game", screenWidth / 2 - MeasureText("Start Game", 30) / 2, 200, 30, startColor);
        DrawText("Options", screenWidth / 2 - MeasureText("Options", 30) / 2, 250, 30, optionsColor);
        DrawText("Scores", screenWidth / 2 - MeasureText("Scores", 30) / 2, 300, 30, scoresColor);
        DrawText("Exit", screenWidth / 2 - MeasureText("Exit", 30) / 2, 350, 30, exitColor);
}
void menuInput(State &gameState, bool &exitWindow){

        if (IsKeyPressed(KEY_DOWN)) {
            currentOption = static_cast<MenuOption>((currentOption + 1) % TOTAL_OPTIONS);
        }
        else if (IsKeyPressed(KEY_UP)) {
            currentOption = static_cast<MenuOption>((currentOption + TOTAL_OPTIONS - 1) % TOTAL_OPTIONS);
        }
        else if (IsKeyPressed(KEY_BACKSPACE)){
            gameState=INPUT;
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            switch (currentOption) {
                case START_GAME:
                    gameState=GAME;
                    break;
                case OPTIONS:
                    break;
                case SCORES:
                    gameState=SCOREMENU;
                    break;
                case EXIT:
                    exitWindow = true;
                    break;
                default:
                    break;
            }
        }
}
