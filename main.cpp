#include "raylib.h"
#include <iostream>

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

void checkCollision(Ball * ball , Paddle * paddle, int * score, double * lasthit);
int main() {
    const Color background = ColorFromHSV(0.12,0.20,0.20);
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Ping Ball!"); 

    Paddle paddle = {0.0f,0.0f,500.0f,59.5f,BLACK,0}; //pos,size,speed,color,hit 
    paddle.pos = { screenWidth - paddle.radius - 45.0f, screenHeight/2.0f};  // Starting paddle.pos of the ball
    Ball ball = {{paddle.pos.x,paddle.pos.y},{500.0f,0.0f},20.0f,PURPLE,0,0}; // pos,speed,radius,color,visible
    float deltaTime=0, offset=0;
    bool hardmode=0;
    double lasthit = 0.0;
    bool gameover=0;
    int score =0;    

    const float wallSize = 50.0f + ball.radius;
    Texture2D backgroundTexture = LoadTexture("background.png");
    Texture2D ballTexture = LoadTexture("ball.png");
    Texture2D paddleTexture = LoadTexture("paddle.png");

    Color scoreColor = ColorFromHSV(191.25f, 0.9697f, 0.9059f);



    SetTargetFPS(60);
    //HideCursor();

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if(!gameover){
        deltaTime = GetFrameTime();
        
        if (IsKeyDown(KEY_UP) && paddle.pos.y > wallSize + paddle.radius) paddle.pos.y -= paddle.speed * deltaTime;
        if (IsKeyDown(KEY_DOWN) && paddle.pos.y + wallSize < screenHeight-paddle.radius) paddle.pos.y += paddle.speed * deltaTime;

        if(IsKeyPressed(KEY_SPACE) && !ball.thrown){
            //ball.pos.y = paddle.pos.y + (2*ball.radius) -10.0f - paddle.radius/2.0f;
            ball.pos.y = paddle.pos.y;
            ball.thrown=1;
            ball.canCollide =0;
            lasthit = GetTime();

        }
            if(!ball.canCollide && GetTime() - lasthit > 2.0f  )
                ball.canCollide =1;
        if(ball.thrown){
                checkCollision(&ball ,&paddle,&score,&lasthit);
            if (ball.pos.x - wallSize<=0 ) ball.speed.x *=-1;
            if (ball.pos.y - wallSize <=0 || ball.pos.y + wallSize >=screenHeight)
                ball.speed.y *= -1;
            // Limit Max Speed
            /*if (ball.speed.y > 300.0f )        ball.speed.y = 300.0f;*/
            /*else if (ball.speed.y < -300.0f )  ball.speed.y = -300.0f;*/
            ball.pos.y += ball.speed.y * deltaTime;
            ball.pos.x -= ball.speed.x * deltaTime;
            if(ball.pos.x>screenWidth + 100){ // 100 is added here to add a delay in gameover
                ball.thrown=0;
                gameover=1;
                ball = {{paddle.pos.x,paddle.pos.y},{500.0f,0.0f},20.0f,PURPLE,0}; // pos,speed,radius,color,visible
            }
            }
        }
            // Drawing
        BeginDrawing();
        ClearBackground(background);
        DrawTexture(backgroundTexture, 15, 30, WHITE);
        /*DrawRectangle(0, screenHeight/2.0f, screenWidth, 30.0f, WHITE);*/
        /*int borderthickness = 100.0f;*/
        /*DrawRectangle(screenWidth/2.0f, 0, 20.0f, screenHeight, DARKBLUE);*/
        /*DrawRectangle(screenHeight + borderthickness, borderthickness,*/
        /*              20.0f - 2 * borderthickness, screenHeight - 2 * borderthickness, RAYWHITE);*/
         int fps = GetFPS();
        DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, DARKGRAY);
        if(!gameover){
            //DrawRectangleV({paddle.pos.x,paddle.pos.y}, {paddle.rect.width, paddle.rect.height}, paddle.color);

        //DrawCircleV(paddle.pos, paddle.radius, YELLOW); 
        DrawTexture(paddleTexture, paddle.pos.x -60.0f, paddle.pos.y - 60.0f, WHITE);
        if(ball.thrown){
        DrawTexture(ballTexture, ball.pos.x - ball.radius, ball.pos.y - ball.radius, WHITE);
            DrawText(TextFormat("%02d", score), screenWidth/2.0f - 35, 25, 60, scoreColor);
            }
            }
        else{
            score =0;
            DrawText("GAME OVER!", screenWidth/2.0f - 100, screenHeight/2.0f -15.0f, 40, RED);
            if(IsKeyPressed(KEY_ENTER)){
                gameover=0;
            }
        }
        EndDrawing();
    }
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(backgroundTexture);
    CloseWindow();

    return 0;
}

void checkCollision(Ball * ball , Paddle * paddle, int * score,double * lasthit){
             bool collision = CheckCollisionCircles(ball->pos, ball->radius, paddle->pos, paddle->radius);
                if(CheckCollisionPointCircle(ball->pos, paddle->pos, paddle->radius) || ball->pos.x>paddle->pos.x || GetTime() - *lasthit <0.5)
                    ball->canCollide = 0;
            if (collision && ball->canCollide)
                paddle->hit = 1;
            else
                paddle->hit=0;
            if( paddle->hit ){
                ball->speed.y = ((ball->pos.y -paddle->pos.y)/paddle->radius)*300.0f; //amplify
                std::cout << ball->speed.y << std::endl;
                ball->speed.x *=-1;
                (*score)++;
                *lasthit = GetTime();
                paddle->hit=0;
    }
}
