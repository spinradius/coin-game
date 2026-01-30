#ifndef GAME_HPP
#define GAME_HPP

#include "ai.hpp"
#include "ball.hpp"
#include "graphics/canvas.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <SFML/System/Clock.hpp>

enum class GameState { MENU, PLAYING, GAME_OVER };

class Game {
public:
  Game();
  bool initialize();
  void cleanup();
  void start();
  void update();
  void render();
  void handleInput();
  void setDifficulty(int level);
  void setMatchDuration(int minutes);
  void reset();
  bool isRunning() const;

private:
  Player player;
  AI computer;
  Ball ball;
  Canvas canvas;

  GameState state;
  int scorePlayer;
  int scoreComputer;
  int difficultyLevel;
  int matchDurationMinutes;
  bool running;

  sf::Clock gameClock;
  float remainingTime;
};

#endif // GAME_HPP