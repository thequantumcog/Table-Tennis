#include "raylib.h"
    typedef struct Ball{
        Vector2 pos;
        Vector2 speed;
        float radius;
        Color color;
        bool thrown;
        bool canCollide;
    } Ball;
    typedef struct Paddle{
        Vector2 pos;
        float speed;
        float radius;
        Color color;
        bool hit;
    } Paddle;
void checkCollision(Ball * ball , Paddle * paddle, int* score, double * lasthit);
void addScore();
void loadResources();
void unloadResources();
void draw(bool * gameover, Ball * ball, Paddle * paddle,int *score);

const Color background = ColorFromHSV(0.12,0.20,0.20);
const int screenWidth = 1920;
const int screenHeight = 1080;
const Color scoreColor = ColorFromHSV(191.25f, 0.9697f, 0.9059f);
const float wallSize = 45.0f;
Texture2D backgroundTexture,ballTexture,paddleTexture;


int main() {
       InitWindow(screenWidth, screenHeight, "Ping Ball!"); 
    Paddle paddle = {0.0f,0.0f,500.0f,59.5f,BLACK,0}; //pos,size,speed,color,hit 
    paddle.pos = { screenWidth - paddle.radius - wallSize, screenHeight/2.0f};  // Starting paddle.pos of the ball
    Ball ball = {{paddle.pos.x,paddle.pos.y},{500.0f,0.0f},20.0f,PURPLE,0,0}; // pos,speed,radius,color,visible
    float deltaTime=0, offset=0;
    bool hardmode=0;
    double lasthit = 0.0;
    bool gameover=0;
    int score=0;
    loadResources();
    SetTargetFPS(60);
    HideCursor();

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if(!gameover){
        deltaTime = GetFrameTime();
        
        if (IsKeyDown(KEY_UP) && paddle.pos.y > wallSize + paddle.radius) paddle.pos.y -= paddle.speed * deltaTime;
        if (IsKeyDown(KEY_DOWN) && paddle.pos.y + wallSize < screenHeight-paddle.radius) paddle.pos.y += paddle.speed * deltaTime;

        if(IsKeyPressed(KEY_SPACE) && !ball.thrown){
            ball.pos.y = paddle.pos.y;
            ball.thrown=1;
            ball.canCollide =0;
            lasthit = GetTime();
        }
        if(ball.thrown){
                checkCollision(&ball ,&paddle,&score,&lasthit);
            if (ball.pos.x - (wallSize + ball.radius)<=0 ) ball.speed.x *=-1;
            if (ball.pos.y - (wallSize +10.0f + ball.radius) <=0 || ball.pos.y + (wallSize +10.0f + ball.radius) >=screenHeight)
                ball.speed.y *= -1;
            ball.pos.y += ball.speed.y * deltaTime;
            ball.pos.x -= ball.speed.x * deltaTime;
            if(ball.pos.x>screenWidth + 100){ // 100 is added here to add a delay in gameover
                ball.thrown=0;
                gameover=1;
                ball = {{paddle.pos.x,paddle.pos.y},{500.0f,0.0f},20.0f,PURPLE,0}; // pos,speed,radius,color,visible
            }
            }
        }
       draw(&gameover, &ball, &paddle,&score); 
    }
        unloadResources();
        CloseWindow();

    return 0;
}

void checkCollision(Ball * ball , Paddle * paddle, int *score,double * lasthit){
             bool collision = CheckCollisionCircles(ball->pos, ball->radius, paddle->pos, paddle->radius);
                //if(CheckCollisionPointCircle(ball->pos, paddle->pos, paddle->radius) || ball->pos.x>paddle->pos.x || GetTime() - *lasthit <0.5)
    //IF the Bug Occurrs Uncomment this
                if(ball->pos.x>paddle->pos.x || GetTime() - *lasthit <0.5f)
                    ball->canCollide = 0;
                else
                    ball->canCollide =1;
            if (collision && ball->canCollide)
                paddle->hit = 1;
            else
                paddle->hit=0;
            if( paddle->hit ){
                ball->speed.y = ((ball->pos.y -paddle->pos.y)/paddle->radius)*300.0f; //amplify
                ball->speed.x *=-1;
                (*score)++;
                *lasthit = GetTime();
                paddle->hit=0;
    }
}
void draw(bool * gameover, Ball * ball, Paddle * paddle, int * score){
    
        BeginDrawing();
        ClearBackground(background);
        DrawTexture(backgroundTexture, 15, 30, WHITE);
         int fps = GetFPS();
        DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, DARKGRAY);
        if(!(*gameover)){
        DrawTexture(paddleTexture, paddle->pos.x -60.0f, paddle->pos.y - 60.0f, WHITE);
        if(ball->thrown){
        DrawTexture(ballTexture, ball->pos.x - ball->radius, ball->pos.y - ball->radius, WHITE);
            DrawText(TextFormat("%02d", *score), screenWidth/2.0f - 35, 25, 60, scoreColor);
            }
            }
        else{
            *score =0;
            DrawText("GAME OVER!", screenWidth/2.0f - 100, screenHeight/2.0f -15.0f, 40, RED);
            if(IsKeyPressed(KEY_ENTER)){
                *gameover=0;
            }
        }
        EndDrawing();
}
void loadResources(){
    backgroundTexture = LoadTexture("background.png");
    ballTexture = LoadTexture("ball.png");
    paddleTexture = LoadTexture("paddle.png");

}
void unloadResources(){
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(backgroundTexture);
}
