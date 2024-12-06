#include "main.hpp"
#include <raylib.h>
Texture2D leaderboard,nameplate,board,backgroundTexture, ballTexture, paddleTexture,paddleblue,paddlered,background_wood;
Texture2D btn_newgame,btn_options,btn_play,btn_score,btn_exit,btn_continue,btn_menu;
Texture2D selector,selected,savesettings;
Sound hit,hit2,paddlesound;
Font font;
void loadResources() {
    backgroundTexture = LoadTexture("assets/background.png");
    ballTexture = LoadTexture("assets/ball.png");
    paddleblue = LoadTexture("assets/paddle_blue.png");
    paddlered = LoadTexture("assets/paddle_red.png");
    btn_options = LoadTexture("assets/options.png");
    btn_play = LoadTexture("assets/play.png");
    btn_score = LoadTexture("assets/scores.png");
    btn_exit = LoadTexture("assets/exit.png");
    btn_menu = LoadTexture("assets/menu.png");
    btn_continue = LoadTexture("assets/continue.png");
    btn_newgame = LoadTexture("assets/newgame.png");
    background_wood = LoadTexture("assets/wood.png");
    board = LoadTexture("assets/board.png");
    leaderboard = LoadTexture("assets/leaderboard.png");
    nameplate = LoadTexture("assets/name.png");
    selector = LoadTexture("assets/selector.png"); 
    selected = LoadTexture("assets/selected.png");
    savesettings = LoadTexture("assets/save.png");
    hit = LoadSound("assets/hit.mp3");
    hit2 = LoadSound("assets/hit2.mp3");
    paddlesound = LoadSound("assets/paddle.mp3");
    font = LoadFontEx("assets/font.otf", 40, NULL, 0);
}

void unloadResources() {
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(paddleblue);
    UnloadTexture(paddlered);
    UnloadTexture(backgroundTexture);
    UnloadTexture(btn_play);  
    UnloadTexture(btn_options);  
    UnloadTexture(btn_score);  
    UnloadTexture(btn_exit);  
    UnloadTexture(btn_continue);  
    UnloadTexture(btn_menu);  
    UnloadTexture(btn_newgame);  
    UnloadTexture(background_wood);  
    UnloadTexture(board);  
    UnloadTexture(leaderboard);  
    UnloadTexture(nameplate);  
    UnloadTexture(selector);  
    UnloadTexture(selected);  
    UnloadTexture(savesettings);  
    UnloadSound(hit);
    UnloadSound(hit2);
    UnloadSound(paddlesound);
    UnloadFont(font);
}

