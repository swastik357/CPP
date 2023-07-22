#include <iostream>
#include "gamePlayer.h"

class GameManager
{

public:
    GameManager()
    {
        std::cout << " " << std::endl;
    };

    bool InitManager();
    static bool quit_game_flag;

private:
    void ReadLastFiveScores(); 

};