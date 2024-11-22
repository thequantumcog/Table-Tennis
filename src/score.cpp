// TODO: Seprate Personal Index to argument i.e remove personal index from global variable
// TODO: Seprate DB to a new file


#include "main.hpp"

using namespace std;

const int maxLines = 100;
const int sHistory = 10;
const int sDigits = 10;
const int containers = 3;
const int containerSize = 50;
const int lineSize = containers*containerSize;

int line = 1;
char scoreData[maxLines][containers][containerSize];
char scoreHistory[sHistory][sDigits];

int PersonalIndex=0;

void scoreCheckInput(State &gameState);
void CompareScore();

int ReadScore(){

    ifstream readData("playerData");

    //Open File
    if (!readData.is_open()) {
        cout << "Error Reading File" << endl;
        return -1;
    }
        // Need temp Variable to store Line
        char storeLine[lineSize];
        // Read Line
        readData.getline(storeLine,lineSize);
        int i=0;
        for(i=0;storeLine[i] != '\0';i++){
            scoreData[0][1][i] = storeLine[i];
        }
        scoreData[0][1][i] = '\0';

        while(!readData.eof()){
            readData.getline(storeLine,lineSize);
            int col=0;
            int start = 0;
            // iterate over each char
            for(int i=0;storeLine[i] != '\0';i++){
                // if char == ';' max=i-1.
                if(storeLine[i] == ';'){
                    int j=0;
                    //consider start as start of line.
                    for(j=0;j<i-start;j++){
                        scoreData[line][col][j] = storeLine[j+start];
                    }
                    scoreData[line][col][j] = '\0';
                    start = i+1;
                col++;
                }
            }
            line++;
        }

    readData.close();
    line--;
    return 0;

}
void WriteScore(){
    ofstream writeData("playerData");
    writeData << scoreData[0][1];
    writeData << "\n";
    for(int i=1;i<line;i++){
        for(int j=0;j<containers;j++){
            if(i==PersonalIndex && j==2){
                for(int l=0;l<10;l++){
                    writeData << scoreHistory[i];
                    writeData << ',';
                }
            }
            else{
            for(int k=0;scoreData[i][j][k] != '\0';k++){
                writeData << scoreData[i][j][k];
            }
            }
            writeData << ";";
        }
        writeData << "\n";
    }
    writeData.close();

}
int charToInteger(const char* str) {
    int result = 0;
    int i = 0;

    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}
void CompareScore(){
    int hiscore = charToInteger(scoreData[0][1]);
    int pb = charToInteger(scoreData[PersonalIndex][1]);
    int ns =  charToInteger(scoreHistory[0]);
    if(ns > pb)
        for(int i=0;scoreHistory[0][i] != '\0';i++){
            scoreData[PersonalIndex][1][i] = scoreHistory[0][i];
        }
    if (ns > hiscore)
        for(int i=0;scoreHistory[0][i] != '\0';i++){
            scoreData[0][1][i] = scoreHistory[0][i];
        }

}
void ChangeScore(int score) {
    for (int i = 9; i > 0; i--) {
        for (int j = 0; j < scoreHistory[i - 1][j] == '\0'; j++) {
            scoreHistory[i][j] = scoreHistory[i - 1][j];
            }
    }
    snprintf(scoreHistory[0], sDigits, "%d", score);
    CompareScore();
}
int getPersonalIndex(char name[]){
    int nameSize=0;
    int index=1;
        while(name[nameSize] != '\0')
            nameSize++;
    for(index=1;index<line;index++){
        int dataSize=0;
        while(scoreData[index][0][dataSize] !='\0'){
            dataSize++;
        }
        if(nameSize == dataSize){
            bool same = 1;
            for(int j=0;j<nameSize;j++){
                if(scoreData[index][0][j] != name[j]){
                    same=0;
                    break;
                    }
            }
        if(same){
            return index;
            }
        }
        }
    int i=0;
    while(name[i] != '\0'){
        scoreData[line][0][i] = name[i];
        i++;
    }
    scoreData[line][1][0] = '0';
    scoreData[line][1][1] = {'\0'};
    line++;
    return line-1;
}
void parseHistory(){
    int start=0;
    int pline=0;
    int j=0;
    if(PersonalIndex != line-1){
    for(int i=0;scoreData[PersonalIndex][2][i] != '\0';i++){
        if(scoreData[PersonalIndex][2][i] == ','){
            for(j=0;j<i-start;j++){
                scoreHistory[pline][j] = scoreData[PersonalIndex][2][j+start]; 
            }
            scoreHistory[pline][j] = '\0';
            pline++;
            start = i+1;

        }
    }
}
    else
        for(int i=0;i<sHistory;i++){
            scoreHistory[i][0] = '0';
            scoreHistory[i][1] = '\0';
    }

}
void ScoreMenu(State &gameState){
    scoreCheckInput(gameState);
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("High Score: "), 10, 50, 40, BLACK);
    DrawText(scoreData[0][1], 10 + MeasureText("High Score: ", 40), 50, 40, BLACK);
    if(PersonalIndex != -1){
        DrawText("Perosnal Best: ", 10, 150, 40, BLACK);
        DrawText(scoreData[PersonalIndex][1], 10 + MeasureText("Perosnal Best: ", 40), 150, 40, BLACK);
        DrawText("Score History: ", 10, 250, 40, BLACK);
        for(int i=0;i<10;i++){
            DrawText(scoreHistory[i], 10, 300+(i*50), 40, BLACK);
        }
    }

}

void scoreCheckInput(State &gameState){
    if(IsKeyPressed(KEY_BACKSPACE)){
        gameState=MENU;
    }
}
void initializeDB(char name[]){
    ReadScore();
    PersonalIndex = getPersonalIndex(name);
    parseHistory();
}
