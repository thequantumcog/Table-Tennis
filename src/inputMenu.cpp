#include "main.hpp"
#define MAX_INPUT_CHARS 30

std::string name = "";
int backspaceHoldCounter = 0;
int framesCounter = 0;
bool mouseOnText = false;
Rectangle textBox = { screenWidth/2.0f - 150, screenHeight/2.0f-100, 300, 50 };

bool isWhitespace(std::string s);
void drawInput(Rectangle &textBox,bool &mouseOnText,int &framesCounter);
void inputMenu(State &gameState)
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
            if ((key >= 32) && (key <= 125) && (name.size() < MAX_INPUT_CHARS))
            {
                name += (char)key;
            }
            key = GetCharPressed();  // Check next character in the queue
        }

        // Backspace removes char plus hold removes all logic
        if (IsKeyDown(KEY_BACKSPACE))
        {
            backspaceHoldCounter++;
            if(backspaceHoldCounter ==1 || (backspaceHoldCounter> 10 && backspaceHoldCounter % 2 == 0)){
                if(!name.empty())
                    name.resize(name.size()-1);
            }
        }
        else
            backspaceHoldCounter=0;

        if(IsKeyReleased(KEY_ENTER)){
            if(name.empty() || isWhitespace(name))
                name = "Anonymus";
            else{
                name[0] = toupper(name[0]);
                for(int i=1;i<name.size();i++){
                    if(i-1>0 && name[i-1] == ' '){
                        name[i] = toupper(name[i]);
                    }
                    else
                    name[i] = tolower(name[i]);
                }
            }
            readScore();
            gameState = MENU;
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    drawInput(textBox,mouseOnText,framesCounter);
}

void drawInput(Rectangle &textBox,bool &mouseOnText,int &framesCounter){


    DrawTexture(background_wood, 0, 0, WHITE);

    DrawTexture(nameplate, screenWidth/2.0f-290, screenHeight/2.0f-250, WHITE);
    Vector2 textSize = MeasureTextEx(font, "Enter Your Name", 40, 2);
    DrawTextEx(font,"Enter Your Name ", (Vector2){screenWidth/2.0f-textSize.x/2.0f, screenHeight/2.0f-200}, 40,2, WHITE);

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BROWN);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name.c_str(), (int)textBox.x + 5, (int)textBox.y + 8, 40, DARKBROWN);

    if (mouseOnText)
    {
        if (name.size() < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name.c_str(), 40), (int)textBox.y + 12, 40, DARKBROWN);
        }
        else DrawText("Press BACKSPACE to delete chars...", screenWidth/2.0f - 170, screenHeight/2.0f, 20, GRAY);
    }

}
bool isWhitespace(std::string s){
    for(int index = 0; index < s.length(); index++){
        if(!std::isspace(s[index]))
            return false;
    }
    return true;
}
