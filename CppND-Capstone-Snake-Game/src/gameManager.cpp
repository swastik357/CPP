#include "gameManager.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl; 
using std::ifstream;
using std::cin;

bool GameManager::quit_game_flag = false;

bool GameManager::InitManager()
{

    cout << " ### WELCOME TO THE SNAKE GAME ###" << endl;
    cout << "   " << endl;
    cout << " 1. Start New Game" << endl;
    cout << " 2. Display Recent 5 Scores" << endl;
    cout << " 3. Quit" << endl;
    cout << "   " << endl;
    cout << "Enter your choice (1-3) --> ";

    int key_pressed;

    while (!(std::cin >> key_pressed))
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
      
        // Asking user to try again:
        cout << "FAILED. Only (1-3) number is allowed. Please enter correct number -->  ";
    }
    if ((key_pressed < 1) || (key_pressed > 3))
    {
        cout << "You pressed : " << key_pressed << endl;
        cout << "FAILED. Please enter correct number!"<< "\n\n";
        return false;
    }

    switch (key_pressed)
    {
    case 1:
    {
        return true;
    };
    break;

    case 2:
    {
        ReadLastFiveScores();
        return false;
       };
    break;
   
    case 3:
    {
        cout << "Quiting the game ...Bye Bye" << endl;
        quit_game_flag = true;
    };

        return false;
    }
}

void GameManager::ReadLastFiveScores(){
      /*Below code reads last 5 lines from ../data.txt*/
        ifstream myfile("../data.txt");
        string line, buffer[5];//to read last 5 lines of the file
        const size_t size = sizeof buffer / sizeof *buffer;
        size_t i = 0;
      /*
       * Read all lines of file, putting them into
       * a circular buffer of strings.
      */
        while ( getline(myfile, line) )
        {
          buffer[i] = line;
          if ( ++i >= size )
          {
           i = 0;
          }
        }
   /*
    * Print the lines.
    */
        for ( size_t j = 0; j < size; ++j )
        {
         cout << buffer[i] << "\n";
         if ( ++i >= size )
         {
          i = 0;
         }
        }
}
  