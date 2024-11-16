#include "main.hpp"

MenuOption currentOption = START_GAME;
void drawMenu();
void menuInput(int &gameState, bool &exitWindow);

void Menu(int &gameState,bool &exitWindow){
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
void menuInput(int &gameState, bool &exitWindow){

        if (IsKeyPressed(KEY_DOWN)) {
            currentOption = static_cast<MenuOption>((currentOption + 1) % TOTAL_OPTIONS);
        }
        if (IsKeyPressed(KEY_UP)) {
            currentOption = static_cast<MenuOption>((currentOption + TOTAL_OPTIONS - 1) % TOTAL_OPTIONS);
        }
        if (IsKeyPressed(KEY_ENTER)) {
            switch (currentOption) {
                case START_GAME:
                    gameState=1;
                    break;
                case OPTIONS:
                    break;
                case SCORES:
                    gameState=3;
                    break;
                case EXIT:
                    exitWindow = true;
                    break;
                default:
                    break;
            }
        }
}
