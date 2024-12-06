#include "main.hpp"
#include <raylib.h>

const int nballs=5;
bool gameover = 0;
bool gamePaused=0;
bool scoreAdded = 0;
Paddle paddle = { { screenWidth - paddleRadius - wallSize, screenHeight / 2.0f }, 700.0f, 59.5f, BLACK, 0 }; // pos, size, speed, color, hit
Ball ball[5] = {{{ paddle.pos.x, paddle.pos.y }, BallSpeed, 20.0f, PURPLE, 0, 0 },{{ paddle.pos.x, paddle.pos.y }, BallSpeed, 20.0f, PURPLE, 0, 0 },{{ paddle.pos.x, paddle.pos.y }, BallSpeed, 20.0f, PURPLE, 0, 0 }
,{{ paddle.pos.x, paddle.pos.y }, BallSpeed, 20.0f, PURPLE, 0, 0 }
,{{ paddle.pos.x, paddle.pos.y }, BallSpeed, 20.0f, PURPLE, 0, 0 }
}; // pos, speed, radius, color, visible
double deltaTime = 0;
double lasthit = 0.0;
bool moveSelector=0;


void checkCollision(Ball &ball, Paddle &paddle, int &score, double &lasthit);
void takeGameInput(Paddle &paddle, Ball * ball, double &lasthit, double deltaTime, State &gameState);
void drawGame(int &score, State &gameState,bool &exitWindow);
// START
void beginGame(int &score, State &gameState,bool &exitWindow) {

    if(pC == PRED)
        paddleTexture = paddlered;
    else
        paddleTexture = paddleblue;

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if(!gamePaused){
            gamePaused = 1;
            ShowCursor();}
        else{
            gamePaused=0;
            HideCursor();

        }
    }
    deltaTime = GetFrameTime();

    if (!gameover && !gamePaused) {
        takeGameInput(paddle, ball, lasthit, deltaTime, gameState);
        for(int i=0;i<nballs;i++){
        if (ball[i].thrown) {
                checkCollision(ball[i], paddle, score, lasthit);
            if (ball[i].pos.x - (wallSize + ball[i].radius) <= 0){
                ball[i].speed.x *= -1;
                PlaySound(hit);
            }
            if (ball[i].pos.y - (wallSize + 10.0f + ball[i].radius) <= 0 || ball[i].pos.y + (wallSize + 10.0f + ball[i].radius) >= screenHeight){
                ball[i].speed.y *= -1;
                PlaySound(hit2);
            }
            ball[i].pos.y += ball[i].speed.y * deltaTime;
            ball[i].pos.x -= ball[i].speed.x * deltaTime;
            if (ball[i].pos.x > screenWidth - wallSize - ball[i].radius) { // 100 is added here to add a delay in gameover
                ball[i].thrown = 0;
                gameover = 1;
                ball[i] = { { paddle.pos.x, paddle.pos.y }, { 500.0f, 0.0f }, 20.0f, PURPLE, 0 }; // pos, speed, radius, color, visible
            }
        }
        }
    }
    else if(!gamePaused && gameover){
        if(!scoreAdded) {updateScore(score);     scoreAdded=1;}
    }
    drawGame(score, gameState,exitWindow);
}

void checkCollision(Ball &ball, Paddle &paddle, int &score, double &lasthit) {
    bool collision = CheckCollisionCircles(ball.pos, ball.radius, paddle.pos, paddle.radius);
    if (ball.pos.x > paddle.pos.x || GetTime() - lasthit < 0.5f)
        ball.canCollide = 0;
    else
        ball.canCollide = 1;
    if (collision && ball.canCollide)
        paddle.hit = 1;
    else
        paddle.hit = 0;
    if (paddle.hit) {
        PlaySound(paddlesound);
        ball.speed.y = ((ball.pos.y - paddle.pos.y) / paddle.radius) * 500.0f; // amplify
        ball.speed.x *= -1;
        score++;
        lasthit = GetTime();
        paddle.hit = 0;
    }
}

void takeGameInput(Paddle &paddle, Ball * ball, double &lasthit, double deltaTime, State &gameState) {
    if (IsKeyDown(KEY_UP) && paddle.pos.y > wallSize + paddle.radius)
        paddle.pos.y -= paddle.speed * deltaTime;
    if (IsKeyDown(KEY_DOWN) && paddle.pos.y + wallSize < screenHeight - paddle.radius)
        paddle.pos.y += paddle.speed * deltaTime;

    for(int i=0;i<nballs;i++){
    if (IsKeyPressed(KEY_SPACE) && !ball[i].thrown) {
        ball[i].pos.y = paddle.pos.y;
        ball[i].speed.x = BallSpeed.x;
        ball[i].speed.y = GetRandomValue(-500, 500);
        ball[i].thrown = 1;
        ball[i].canCollide = 0;
        lasthit = GetTime();
    }
    }
}

void drawGame(int &score,State &gameState,bool &exitWindow) {
    ClearBackground(background);
    
        int fps = GetFPS();
        DrawTexture(backgroundTexture, 15, 30, WHITE);
        DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, DARKGRAY);
        DrawTexture(paddleTexture, paddle.pos.x - paddle.radius, paddle.pos.y - paddle.radius, WHITE);
    for(int i=0;i<nballs;i++){
        if (ball[i].thrown) {
            DrawTexture(ballTexture, ball[i].pos.x - ball[i].radius, ball[i].pos.y - ball[i].radius, WHITE);
            DrawText(TextFormat("%02d", score), screenWidth / 2.0f - 35, 25, 60, scoreColor);
        }}
     if(gameover) {
        DrawTexture(nameplate, screenWidth/2.0f-270, screenHeight/2.0f-170, WHITE);
        DrawText("GAME OVER!", screenWidth / 2.0f - MeasureText("GAME OVER!", 40)/2.0f, screenHeight / 2.0f - 150.0f, 50, YELLOW);
        DrawText("Play Again?", screenWidth / 2.0f - MeasureText("Play Again?", 40)/2.0f, screenHeight / 2.0f - 50.0f, 50, RED);
        DrawText("Yes", screenWidth / 2.0f - MeasureText("Yes", 40)/2.0f- 100.0f, screenHeight / 2.0f + 50.0f, 50, BLACK);
        DrawText("NO", screenWidth / 2.0f + MeasureText("No", 40)/2.0f+ 100.0f, screenHeight / 2.0f + 50.0f, 50, BLACK);

        if(IsKeyPressed(KEY_RIGHT)){ 
            if(!moveSelector) moveSelector=1;
            else moveSelector=0;}
        if(IsKeyPressed(KEY_LEFT)){
            if(moveSelector) moveSelector=0;
            else moveSelector=1;}

        if(!moveSelector)
            DrawTexture(selector,screenWidth / 2.0f - MeasureText("Yes", 40)/2.0f- 150.0f, screenHeight / 2.0f + 55.0f,WHITE);
        else
            DrawTexture(selector,screenWidth / 2.0f + MeasureText("No", 40)/2.0f+ 50.0f, screenHeight / 2.0f + 55.0f,WHITE);
        if(IsKeyReleased(KEY_ENTER)){
                paddle = { { screenWidth - paddleRadius - wallSize, screenHeight / 2.0f }, 700.0f, 59.5f, BLACK, 0 }; // pos, size, speed, color, hit
            for(int i=0;i<nballs;i++)
                ball[i] = { { paddle.pos.x, paddle.pos.y }, { 500.0f, 0.0f }, 20.0f, PURPLE, 0 }; // pos, speed, radius, color, visible
            score =0;
                scoreAdded=0;
            if(moveSelector){
                gameState=MENU;
                gameover = 0;
            }
            else{
                    gameover = 0;
            }
        }
    }
    for(int i=0;i<nballs;i++)
    if(gamePaused && !gameover) drawPauseMenu(gameState,gamePaused,score,ball[i],paddle,exitWindow);
}

