#include "main.hpp"
#include <fstream>
#include <raylib.h>

using namespace std;

const int maxLines = 100;
const int containers = 3;
const int containerSize = 50;
const int lineSize = containers*containerSize;

int line = 1;
char storeData[maxLines][containers][containerSize];

void scoreCheckInput(int &gameState);

void ReadScore(){

    ifstream readData("playerData");

    //Open File
    if (readData.is_open()) {
        // Need temp Variable to store Line
        char storeLine[lineSize];
        // Read Line
        readData.getline(storeLine,lineSize);
        int i=0;
        for(i=0;storeLine[i] != '\0';i++){
            storeData[0][1][i] = storeLine[i];
        }
        storeData[0][1][i] = '\0';

        while(readData.getline(storeLine,lineSize)){
            int col=0;
            int start = 0;
            // iterate over each char
            for(int i=0;storeLine[i] != '\0';i++){
                // if char == ';' max=i-1.
                if(storeLine[i] == ';'){
                    int j=0;
                    //consider start as start of line.
                    for(j=0;j<i-start;j++){
                        storeData[line][col][j] = storeLine[j+start];
                    }
                    storeData[line][col][j] = '\0';
                    start = i+1;
                col++;
                }
            }
            line++;
        }

    }
    readData.close();

    /*cout << storeData[0][1] << endl;*/
    /*for(int i=1;i<line;i++){*/
    /*    cout << storeData[i][0] << " " << storeData[i][1] << " "<< storeData[i][2] << endl;*/
    /*}*/
    // lets say we want to update the pb of ahmad rehan; he's on line 1
}
void WriteScore(){
    ofstream writeData("playerData");
    char sco[5] = "190";
    for(int i=0;i<3;i++){
        storeData[0][1][i] = sco[i]; 
        writeData << storeData[0][1][i];
    }
    writeData << "\n";
    for(int i=1;i<line;i++){
        for(int j=0;j<containers;j++){
            for(int k=0;storeData[i][j][k] != '\0';k++){
                writeData << storeData[i][j][k];
            }
            writeData << ";";
        }
        writeData << "\n";
    }
    writeData.close();

}
bool flag=1;
void ScoreMenu(int &gameState){
    if(flag){
        ReadScore();
        flag=0;
    }
    scoreCheckInput(gameState);
    ClearBackground(WHITE);
    DrawText(storeData[0][1], 1080 / 2 - MeasureText(storeData[0][1], 40) / 2, screenHeight/2.0f, 40, BLACK);

}

void scoreCheckInput(int &gameState){
    if(IsKeyPressed(KEY_BACKSPACE)){
        gameState=0;
    }
}
