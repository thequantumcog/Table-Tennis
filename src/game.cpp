#include "main.hpp"

const Color background = ColorFromHSV(0.12, 0.20, 0.20);
const Color scoreColor = ColorFromHSV(191.25f, 0.9697f, 0.9059f);
const float wallSize = 45.0f;
const float paddleRadius = 59.5f;
Texture2D backgroundTexture, ballTexture, paddleTexture;

bool gameover = 0;
Paddle paddle = { { screenWidth - paddleRadius - wallSize, screenHeight / 2.0f }, 700.0f, 59.5f, BLACK, 0 }; // pos, size, speed, color, hit
Ball ball = { { paddle.pos.x, paddle.pos.y }, { 700.0f, 0.0f }, 20.0f, PURPLE, 0, 0 }; // pos, speed, radius, color, visible
double deltaTime = 0;
double lasthit = 0.0;

void checkCollision(Ball &ball, Paddle &paddle, int &score, double &lasthit);
void takeInput(Paddle &paddle, Ball &ball, double &lasthit, double deltaTime, State &gameState);
void drawGame(int &score);

void beginGame(int &score, State &gameState) {
    HideCursor();
    deltaTime = GetFrameTime();

    if (!gameover) {
        takeInput(paddle, ball, lasthit, deltaTime, gameState);
        if (ball.thrown) {
            checkCollision(ball, paddle, score, lasthit);
            if (ball.pos.x - (wallSize + ball.radius) <= 0)
                ball.speed.x *= -1;
            if (ball.pos.y - (wallSize + 10.0f + ball.radius) <= 0 || ball.pos.y + (wallSize + 10.0f + ball.radius) >= screenHeight)
                ball.speed.y *= -1;
            ball.pos.y += ball.speed.y * deltaTime;
            ball.pos.x -= ball.speed.x * deltaTime;
            if (ball.pos.x > screenWidth + 100) { // 100 is added here to add a delay in gameover
                ball.thrown = 0;
                gameover = 1;
                ball = { { paddle.pos.x, paddle.pos.y }, { 500.0f, 0.0f }, 20.0f, PURPLE, 0 }; // pos, speed, radius, color, visible
            }
        }
    }
    else{
        if (IsKeyPressed(KEY_ENTER)){
            ChangeScore(score);
            gameover = 0;
            score = 0;
        }
    }
    drawGame(score);
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
        ball.speed.y = ((ball.pos.y - paddle.pos.y) / paddle.radius) * 500.0f; // amplify
        ball.speed.x *= -1;
        score++;
        lasthit = GetTime();
        paddle.hit = 0;
    }
}

void takeInput(Paddle &paddle, Ball &ball, double &lasthit, double deltaTime, State &gameState) {
    if (IsKeyPressed(KEY_BACKSPACE)) {
            gameState = MENU;
    }
    if (IsKeyDown(KEY_UP) && paddle.pos.y > wallSize + paddle.radius)
        paddle.pos.y -= paddle.speed * deltaTime;
    if (IsKeyDown(KEY_DOWN) && paddle.pos.y + wallSize < screenHeight - paddle.radius)
        paddle.pos.y += paddle.speed * deltaTime;

    if (IsKeyPressed(KEY_SPACE) && !ball.thrown) {
        ball.pos.y = paddle.pos.y;
        ball.thrown = 1;
        ball.canCollide = 0;
        lasthit = GetTime();
    }
}

void drawGame(int &score) {
    ClearBackground(background);


    if (!gameover) {
        int fps = GetFPS();
        DrawTexture(backgroundTexture, 15, 30, WHITE);
        DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, DARKGRAY);
        DrawTexture(paddleTexture, paddle.pos.x - paddle.radius, paddle.pos.y - paddle.radius, WHITE);
        if (ball.thrown) {
            DrawTexture(ballTexture, ball.pos.x - ball.radius, ball.pos.y - ball.radius, WHITE);
            DrawText(TextFormat("%02d", score), screenWidth / 2.0f - 35, 25, 60, scoreColor);
        }
    } else {
        DrawText("GAME OVER!", screenWidth / 2.0f - MeasureText("GAME OVER!", 40)/2.0f, screenHeight / 2.0f - 15.0f, 40, RED);
    }
}

void loadResources() {
    backgroundTexture = LoadTexture("assets/background.png");
    ballTexture = LoadTexture("assets/ball.png");
    paddleTexture = LoadTexture("assets/paddle.png");
}

void unloadResources() {
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(backgroundTexture);
}
