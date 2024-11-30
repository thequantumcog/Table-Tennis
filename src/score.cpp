#include "main.hpp"
using namespace std;

int PersonalIndex = 0;

Vector2 calculateTextPosition(int index, const Vector2& textSize) {
    if (index == 0) {
        // First position is unique
        return {970.0f - textSize.x/2.0f, 455.0f - textSize.y/2.0f};
    } else if (index == 1 || index == 2) {
        // Second and third share the same y-coordinate
        float xOffset = index == 1 ? 500.0f - textSize.x/2.0f : 500.0f - textSize.x/2.0f + 935.0f; // Adjust for x difference
        return {xOffset, 550.0f};
    } else if (index >2 && index <6){
        // All other positions have a constant offset
        float x = 350.0f;
        float y = 695.0f + (index - 3) * 130.0f;
        return {x, y};
    } else {
        // All other positions have a constant offset
        float x = 1250.0f;
        float y = 695.0f + (index - 6) * 130.0f;
        return {x, y};
    }
}

Vector2 calculateScorePosition(int index, const Vector2& scoreSize) {
    if (index == 0) {
        // First position is unique
        return {930.0f - scoreSize.x/2.0f, 505.0f - scoreSize.y/2.0f};
    } else if (index == 1 || index == 2) {
        // Second and third share the same y-coordinate
        float xOffset = index == 1 ? 460.0f - scoreSize.x/2.0f : 460.0f - scoreSize.x/2.0f + 935.0f; // Adjust for x difference
        return {xOffset, 600.0f};
    } else if (index >2 && index <6){
        // All other positions have a constant offset
        float x = 750.0f;
        float y = 695.0f + (index - 3) * 130.0f;
        return {x, y};
    } else {
        // All other positions have a constant offset
        float x = 1650.0f;
        float y = 695.0f + (index - 6) * 130.0f;
        return {x, y};
    }
}
void scoreCheckInput(State &gameState) {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        gameState = MENU;
    }
}

void ScoreMenu(State &gameState) {
    scoreCheckInput(gameState);

    DrawTexture(leaderboard, 0, 0, WHITE);

    for (int i = 0; i < pbIndex && i<9; i++) {
        Vector2 textSize = MeasureTextEx(font, playerBest[i][0].c_str(), 40, 2);
        Vector2 scoreSize = MeasureTextEx(font, playerBest[i][1].c_str(), 40, 2);
        Vector2 textposition = calculateTextPosition(i, textSize);
        Vector2 scoreposition = calculateScorePosition(i, scoreSize);
        DrawTextEx(font, playerBest[i][0].c_str(), textposition, 40, 2, WHITE);
        DrawTextEx(font, TextFormat("0000%d", stoi(playerBest[i][1])), scoreposition, 40, 2, WHITE);
    }
}
