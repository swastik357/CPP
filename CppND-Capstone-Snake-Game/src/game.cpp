#include "game.h"
#include <iostream>
#include "SDL.h"

bool Game::running=true;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceObstacles();      
  PlaceFood();      
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  //running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item or obstacle before placing
    // food.
    if (!snake.SnakeCell(x, y) and !isPointInObstacle(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceObstacles() {
  for(int i=0;i<10;i++)
  {
    SDL_Point obstacle;
    obstacle.x=random_w(engine);
    obstacle.y=random_h(engine);
    obstacles.emplace_back(obstacle);
  }
    return; 
}

bool Game::isPointInObstacle(int x, int y){
  for(int i=0;i<10;i++)
  {
   if(obstacles[i].x==x && obstacles[i].y==y)
   {
     return true;
   }    
  }
  return false;
}

void Game::Update() {
  if (!snake.alive) return;
  
  if (isPointInObstacle(static_cast<int>(snake.head_x),static_cast<int>(snake.head_y)))
  {
    snake.alive=false;
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.2*snake.speed;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }