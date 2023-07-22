#include <iostream>
#include <string>
#include <vector>
#include "snake.h"

using std::string;

class gamePlayer
{

public:
    gamePlayer() { std::cout << "****WELCOME New Player****" << std::endl; };
    gamePlayer(string, int);
    ~gamePlayer(){};

    string GetPlayerName();
    int GetPlayerScore();

    void SetPlayerName();
    void SetPlayerScore();
    void SetPlayerSpeed();

private:
    string player_name;
    int player_score;
};