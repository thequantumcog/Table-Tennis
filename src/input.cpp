#include "main.hpp"
#define MAX_INPUT_CHARS 30

char name[MAX_INPUT_CHARS + 1] = "\0";      
char lowerName[MAX_INPUT_CHARS + 1] = "\0";      
int framesCounter = 0;
int letterCount = 0;
bool mouseOnText = false;
Rectangle textBox = { screenWidth/2.0f - 150, screenHeight/2.0f-100, 300, 50 };


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

        static int backspaceHoldCounter = 0;
        if (IsKeyDown(KEY_BACKSPACE))
        {
            backspaceHoldCounter++;
            if(backspaceHoldCounter ==1 || (backspaceHoldCounter> 10 && backspaceHoldCounter % 2 == 0)){
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else
            backspaceHoldCounter=0;
        if(IsKeyPressed(KEY_ENTER) && letterCount >=1){
            gameState = MENU;
            for(int i=0;i<letterCount;i++){
                if(name[i] >= 'A' && name[i] <= 'Z')
                    lowerName[i] = name[i] + 32;
                else
                    lowerName[i] = name[i];
            }
            initDB(lowerName);
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    drawInput(textBox,mouseOnText,letterCount,framesCounter);
}


void drawInput(Rectangle &textBox,bool &mouseOnText,int &letterCount,int &framesCounter){


    DrawTexture(background_wood, 0, 0, WHITE);

    DrawTexture(nameplate, screenWidth/2.0f-290, screenHeight/2.0f-250, WHITE);
    Vector2 textSize = MeasureTextEx(font, "Enter Your Name", 40, 2);
    DrawTextEx(font,"Enter Your Name ", (Vector2){screenWidth/2.0f-textSize.x/2.0f, screenHeight/2.0f-200}, 40,2, WHITE);

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BROWN);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, DARKBROWN);


    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, DARKBROWN);
        }
        else DrawText("Press BACKSPACE to delete chars...", screenWidth/2.0f - 170, screenHeight/2.0f, 20, GRAY);
    }

}

