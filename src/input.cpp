#include "main.hpp"
#include <raylib.h>

#define MAX_INPUT_CHARS 30

char name[MAX_INPUT_CHARS + 1] = "\0";      
char lowerName[MAX_INPUT_CHARS + 1] = "\0";      
int framesCounter = 0;
int letterCount = 0;
bool mouseOnText = false;
Rectangle textBox = { screenWidth/2.0f - 100, 180, 300, 50 };
void drawInput(Rectangle &textBox,bool &mouseOnText,int &letterCount,int &framesCounter);
void input(State &gameState)
{
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
            else if(IsKeyPressed(KEY_ENTER)){
            gameState = MENU;
            for(int i=0;i<letterCount;i++){
                if(name[i] >= 'A' && name[i] <= 'Z')
                    lowerName[i] = name[i] + 32;
                else
                    lowerName[i] = name[i];
            }
            initializeDB(lowerName);
        }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

    drawInput(textBox,mouseOnText,letterCount,framesCounter);
    }

void drawInput(Rectangle &textBox,bool &mouseOnText,int &letterCount,int &framesCounter){


            ClearBackground(RAYWHITE);

            /*DrawText("Enter Your Name: ", 240, 140, 20, GRAY);*/
            DrawText("Enter Your Name: ", 240, textBox.y+textBox.height/2, 20, GRAY);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), (textBox.x + textBox.width/2)-MeasureText("INPUT CHARS:", 20), 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }

}

