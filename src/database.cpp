#include "main.hpp"
#include <cctype>

using namespace std;


string playerBest[PBCapacity][containers]; 
int pbIndex =0;
string lname;
void initDB(char lowerName[]){
    readScore();
    lname = string(lowerName);

}
void readScore(){
    string storeLine = "";
    ifstream read("playerData");
    pbIndex=0;
    while(getline(read,storeLine)){

        int start =0;
        int containerID = 0;
        for(size_t i=0;i<storeLine.length();i++){
            if(storeLine[i] == ';'){
                if(pbIndex < PBCapacity){
                    playerBest[pbIndex][containerID] = storeLine.substr(start,i-start);
                }
                start = i+1;
                containerID++;
            }
        }
        pbIndex++;
    }
}
void writeScore(){
    ofstream write("playerData");
    int j=0;
    for(int i=0;i<pbIndex;i++){
        for(j=0;j<2;j++){
            if(j==0)
                playerBest[i][j][0] = toupper(playerBest[i][j][0]);
            write << playerBest[i][j] << ";";
        }
        write << endl;
    }
}
void updateScore(int score){
    if(pbIndex < PBCapacity )
        pbIndex++;
    for(int i=0;i<pbIndex;i++){
        if(pbIndex == 1|| playerBest[i][0].empty()){
            playerBest[i][0] = lname;
            playerBest[i][1] = to_string(score);

        }
        else if( score>stoi(playerBest[i][1])){
            for(int j=pbIndex-1;j>i;j--){
                playerBest[j][0] = playerBest[j-1][0];
                playerBest[j][1] = playerBest[j-1][1];
            }
            playerBest[i][0] = lname;
            playerBest[i][1] = to_string(score);
                break;
        }
    }
    
}
