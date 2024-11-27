#include "main.hpp"
Texture2D board,backgroundTexture, ballTexture, paddleTexture,btn_options,btn_play,btn_score,btn_exit,background_wood;
void loadResources() {
    backgroundTexture = LoadTexture("assets/background.png");
    ballTexture = LoadTexture("assets/ball.png");
    paddleTexture = LoadTexture("assets/paddle.png");
    btn_options = LoadTexture("assets/options.png");
    btn_play = LoadTexture("assets/play.png");
    btn_score = LoadTexture("assets/scores.png");
    btn_exit = LoadTexture("assets/exit.png");
    background_wood = LoadTexture("assets/wood.png");
    board = LoadTexture("assets/board.png");
}

void unloadResources() {
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(btn_play);  
    UnloadTexture(btn_options);  
    UnloadTexture(btn_score);  
    UnloadTexture(btn_exit);  
    UnloadTexture(background_wood);  
    UnloadTexture(board);  
}

