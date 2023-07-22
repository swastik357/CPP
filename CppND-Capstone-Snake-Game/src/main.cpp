#include "game.h"
#include "renderer.h"
#include "gameManager.h"
#include <bits/stdc++.h>
#include "snake.h"

using std::cerr;
using std::endl;
using std::ofstream;

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  bool start_game = false;
  bool quit_game_flag = false;
  
  while (true)
  {
  
  while (start_game == false)
  {
    GameManager gm; 
    
    if (gm.quit_game_flag == true)
    {
      return 0;
    }
    start_game = gm.InitManager();
  }
  
  start_game = false;
  gamePlayer *newplayer = new gamePlayer();
  newplayer->SetPlayerName();
  newplayer->SetPlayerSpeed();
  
  std::cout << "Starting The Game" << std::endl;
    
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
   
  /*Below storing player name and score in data.txt file*/
  ofstream outdata;
  outdata.open("../data.txt", std::ios_base::app); // opens the file
  if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
   }
   else 
   {
     outdata << newplayer->GetPlayerName() << " " << game.GetScore() << endl;
     outdata.close();
   }
    
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  }
  return 0;
}