PROJECT: This project extends the snake game by adding some features.

INSTRUCTIONS TO RUN THE PROJECT: In "build" folder run cmake.., make and then ./SnakeGame . After that follow the options/instructions on the screen.

FEATURES IN THE GAME: The following features have been added to usual snake game:
1) The game now has several obstacles placed randomly on the game screen. If the head of snake collides with any of those obstacles, the game ends.

2) The game now stores player and score history in data.txt file.

3) Upon the snake getting killed, the game terminates, game screen closes automatically, score and snake size are displayed and player name and score are stored in data.txt file.

4) The game has a welcome screen with 3 options: Start New Game, Display Recent 5 Scores and Quit. On choosing Start New Game, the player  is asked for player name and difficulty level. Higher difficulty level sets the snake to higher initial speed. Upon eating food, the speed increases by 20%. Hence higher initial speed has high influence on the difficulty of the game. Display Recent 5 Scores displays last 5 entries from data.txt file. Quit quits the interface.
 
OVERVIEW OF CODE STRUCTURE:

1) main.cpp : All aspects of game flow happen here: game interface display, game execution, data storage and score and snake size display

2) snake.h/snake.cpp : Handles snake object : updates, head, body, checks if snake is alive and gives a default initial speed of 0.1 (which is speed corresponding to difficulty level 1)

3) render.cpp/render.h : manage the game screen display: food, obstacles and snake; score and frames per second; and sets boolean "running" to false when the snake dies

4) gamePlayer.h/gamePlayer.cpp : Handle player attributes like get/set player name, score and speed (speed is directly proportional to difficulty level selected by player)

5) gameManager.h/gameManager.cpp : Take input from the user and take appropriate actions

6) game.cpp/game.h: Game engine

7) controller.h/controller.cpp: Handle user input to change direction during the game

EXPLANATION OF HOW IT SATISFIES NECESSARY RUBRIC:

1) The project demonstrates an understanding of C++ functions and control structures.:  gameManager.h/gameManager.cpp take input from user and acts accordingly.  gamePlayer.h/gamePlayer.cpp handle player attributes like get/set player name, score and speed (speed is directly proportional to difficulty level selected by player). main.cpp handles all aspects of game flow. render.cpp/render.h place food and obstacles on game screen.

2) The project reads data from a file and process the data, or the program writes data to a file.: main.cpp writes data to data.txt , GameManager::ReadLastFiveScores() reads last 5 lines from data.txt and prints them.

3) The project accepts user input and processes the input.: GameManager::InitManager(), gamePlayer::SetPlayerName() and gamePlayer::SetPlayerSpeed()

4) The project uses Object Oriented Programming techniques: Details in OVERVIEW OF CODE STRUCTURE above

5) Classes use appropriate access specifiers for class members.

6) Overloaded functions allow the same function to operate on different parameters: gamePlayer::gamePlayer(), gamePlayer::gamePlayer(string, int)
