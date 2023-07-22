#include "gamePlayer.h"
#include <iostream>
#include <string>
#include<ctime>
#include<vector>

using std::string;
using std::vector;


gamePlayer::gamePlayer(string player_name, int player_score){

    std::cout<<"****WELCOME New Player****"<< std::endl;

    this->player_name = player_name;
    this->player_score = player_score;
}

string gamePlayer::GetPlayerName(){

    return player_name;
}

int gamePlayer::GetPlayerScore(){
    
    return player_score;
}

void gamePlayer::SetPlayerName(){
    
    string player_name;
    std::cout<<"Player NAME :::  ";
    std::cin >> player_name;
    this->player_name = player_name;
}

void gamePlayer::SetPlayerSpeed(){
    int difficulty=10;
    while(difficulty<1 or difficulty>5)
    {
    std::cout<<"Enter Difficulty Level (1-5)"; 
    std::cin >> difficulty; 
    Snake::speed=difficulty*0.1;
    }
}

void gamePlayer::SetPlayerScore(){
    int player_score;
    std::cout<< "Player game score :::  ";
    std::cin >> player_score;
    this->player_score = player_score;

}