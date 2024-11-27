#include "main.hpp"
#include <string>

using namespace std;


int hiScore = 0;
string playerBest[PBCapacity][containers]; 
string previousScores [scoreCapacity][containers];
int pbIndex =0;
int scoreIndex=0;
int pbSI=-1;
string ok;
void initDB(char lowerName[]){
    readScore();
    ok = string(lowerName);
    for(int i=0;i<pbIndex;i++){
        if(playerBest[i][0] == string(lowerName))
            pbSI=i;
    }
    if(pbSI == -1){
        playerBest[pbIndex][0] = string(lowerName);
        playerBest[pbIndex][1] = '0';
        pbSI=pbIndex;
        pbIndex++;
    }

}
void readScore(){
    string storeLine = "";
    ifstream read("playerData");
    getline(read,storeLine);
    hiScore = stoi(storeLine);
    pbIndex=0;
    scoreIndex=0;
    bool StoringPB=1;
    while(getline(read,storeLine)){

        int start =0;
        int containerID = 0;
        if(storeLine == "###"){
            StoringPB=0;
            continue;
        }
        for(size_t i=0;i<storeLine.length();i++){
            if(storeLine[i] == ';'){
                if(StoringPB && pbIndex < PBCapacity){
                    playerBest[pbIndex][containerID] = storeLine.substr(start,i-start);
                }
                else if(!StoringPB){
                    previousScores[scoreIndex][containerID] = storeLine.substr(start,i-start);
                }
                start = i+1;
                containerID++;
            }
        }
        if(StoringPB) pbIndex++;
        else if (!StoringPB) scoreIndex++;
    }
}
void writeScore(){
    ofstream write("playerData1");
    write << hiScore << '\n';
    int j=0;
    for(int i=0;i<pbIndex;i++){
        for(j=0;j<2;j++){
            write << playerBest[i][j] << ";";
        }
        write << endl;
    }
    write << "###" << endl;
    for(int i=0;i<scoreIndex;i++){
        for(int j=0;j<2;j++){
            write << previousScores[i][j] << ";";
        }
        write << "\n";
    }
}
void addInList(int score){
    for(int i=scoreCapacity-1;i>0;i--)
        for(int j=0;j<2;j++){
            previousScores[i][j] = previousScores[i-1][j];
        }
    previousScores[0][0] = ok;
    previousScores[0][1] = to_string(score);
    if (scoreIndex<scoreCapacity-1)
        scoreIndex++;
}
void updateScore(int score){
    if(score > hiScore)
        hiScore = score;
    if(score > stoi(playerBest[pbSI][1])){
        playerBest[pbSI][1] = to_string(score);
    }
    addInList(score);
    
}
