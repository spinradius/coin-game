#include "game.hpp"
#include "sound_manager.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

Game::Game()
    : state(GameState::MENU), scorePlayer(0), scoreComputer(0),
      difficultyLevel(1), matchDurationMinutes(2), running(true),
      remainingTime(120.f) {}

bool Game::initialize() {
  reset();
  return true;
}

void Game::cleanup() {}

void Game::start() {
  while (isRunning()) {
    handleInput();
    update();
    render();
  }
}

void Game::handleEntityBallCollision(Player &entity) {
  sf::Vector2f ePos = entity.getPosition();
  sf::Vector2f bPos = ball.getPosition();
  float dx = bPos.x - ePos.x;
  float dy = bPos.y - ePos.y;
  float dist = std::sqrt(dx * dx + dy * dy);
  float minDist = entity.getRadius() + 10.f;

  if (dist < minDist) {
    sf::Vector2f dir = {dx / dist, dy / dist};
    ball.setVelocity(dir * 10.f);
    SoundManager::getInstance().play("kick");
  }
}

void Game::handleAIBallCollision() {
  sf::Vector2f ePos = computer.getPosition();
  sf::Vector2f bPos = ball.getPosition();
  float dx = bPos.x - ePos.x;
  float dy = bPos.y - ePos.y;
  float dist = std::sqrt(dx * dx + dy * dy);
  float minDist = computer.getRadius() + 10.f;

  if (dist < minDist) {
    sf::Vector2f dir = {dx / dist, dy / dist};
    ball.setVelocity(dir * 10.f);
    SoundManager::getInstance().play("kick");
  }
}

void Game::checkScoring() {
  const float goalY = 300.f;
  const float goalTolerance = 50.f;
  
  // Player scores (right goal)
  if (ball.getPosition().x > 788 &&
      std::abs(ball.getPosition().y - goalY) < goalTolerance) {
    scorePlayer++;
    SoundManager::getInstance().play("goal");
    reset();
  }
  // Computer scores (left goal)
  else if (ball.getPosition().x < 12 &&
           std::abs(ball.getPosition().y - goalY) < goalTolerance) {
    scoreComputer++;
    SoundManager::getInstance().play("goal");
    reset();
  }
}

std::string Game::getDifficultyName() const {
  switch (difficultyLevel) {
    case 1: return "Amateur";
    case 2: return "Professional";
    case 3: return "World Class";
    default: return "Unknown";
  }
}

void Game::update() {
  canvas.pollEvents();
  if (!canvas.isOpen())
    running = false;

  if (state == GameState::MENU) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
      state = GameState::PLAYING;
      remainingTime = matchDurationMinutes * 60.f;
      gameClock.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
      difficultyLevel = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
      difficultyLevel = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
      difficultyLevel = 3;

    // Time selection with T key (toggle/cycle)
    static bool tPressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
      if (!tPressed) {
        matchDurationMinutes++;
        if (matchDurationMinutes > 4)
          matchDurationMinutes = 2;
        tPressed = true;
      }
    } else {
      tPressed = false;
    }
  } else if (state == GameState::PLAYING) {
    float dt = 1.f / 60.f;
    remainingTime -= dt;
    if (remainingTime <= 0) {
      remainingTime = 0;
      state = GameState::GAME_OVER;
    }

    player.update();
    computer.update(ball, difficultyLevel);
    ball.update(dt);

    // Handle collisions
    handleEntityBallCollision(player);
    handleAIBallCollision();

    // Check scoring
    checkScoring();
  } else if (state == GameState::GAME_OVER) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
      scorePlayer = 0;
      scoreComputer = 0;
      state = GameState::MENU;
    }
  }
}

void Game::render() {
  canvas.clear();

  if (state == GameState::MENU) {
    renderMenu();
  } else {
    renderGameplay();
    
    if (state == GameState::GAME_OVER) {
      renderGameOver();
    }
  }

  canvas.display();
}

void Game::renderMenu() {
  // Title
  canvas.drawText("COIN SOCCER", {250, 80}, 60, sf::Color::Yellow);

  // Level Selection
  canvas.drawText("SELECT LEVEL:", {280, 200}, 24, sf::Color::White);
  canvas.drawText("[1] Amateur", {300, 240}, 20,
                  (difficultyLevel == 1) ? sf::Color::Green
                                         : sf::Color::White);
  canvas.drawText("[2] Professional", {300, 270}, 20,
                  (difficultyLevel == 2) ? sf::Color::Green
                                         : sf::Color::White);
  canvas.drawText("[3] World Class", {300, 300}, 20,
                  (difficultyLevel == 3) ? sf::Color::Green
                                         : sf::Color::White);

  // Time Selection
  canvas.drawText("SELECT TIME (Press T):", {280, 360}, 24, sf::Color::White);
  canvas.drawText(std::to_string(matchDurationMinutes) + " MINUTES",
                  {350, 400}, 30, sf::Color::Cyan);

  // Start hint with flashing effect
  static float flashTimer = 0;
  flashTimer += 1.f / 60.f;
  sf::Color flashColor = (std::sin(flashTimer * 5.f) > 0)
                             ? sf::Color::White
                             : sf::Color::Transparent;
  canvas.drawText("PRESS ENTER TO PLAY", {280, 500}, 24, flashColor);
}

void Game::renderGameplay() {
  canvas.drawField();
  canvas.drawPlayer(player.getPosition(), sf::Color::Blue,
                    player.getRadius());
  canvas.drawPlayer(computer.getPosition(), sf::Color::Red,
                    computer.getRadius());
  canvas.drawBall(ball.getPosition(), 10.f);

  // UI Header
  std::string scoreStr =
      std::to_string(scorePlayer) + " - " + std::to_string(scoreComputer);
  canvas.drawText(scoreStr, {370, 20}, 30, sf::Color::White);

  // Timer
  std::stringstream ss;
  int mins = static_cast<int>(remainingTime) / 60;
  int secs = static_cast<int>(remainingTime) % 60;
  ss << mins << ":" << std::setfill('0') << std::setw(2) << secs;
  canvas.drawText(ss.str(), {380, 55}, 20, sf::Color::Yellow);

  // Level indicator
  canvas.drawText("Level: " + getDifficultyName(), {20, 20}, 16,
                  sf::Color(200, 200, 200));
}

void Game::renderGameOver() {
  std::string scoreStr =
      std::to_string(scorePlayer) + " - " + std::to_string(scoreComputer);
  canvas.drawText("MATCH ENDED", {260, 200}, 50, sf::Color::Red);
  canvas.drawText(scoreStr, {370, 270}, 40, sf::Color::White);
  canvas.drawText("PRESS R TO RESTART", {285, 350}, 24, sf::Color::White);
}

void Game::handleInput() {
  // Handled in update via sf::Keyboard
}

void Game::reset() {
  player.resetPosition();
  computer.resetPosition();
  ball.reset();
}

bool Game::isRunning() const { return running; }

void Game::setDifficulty(int level) { difficultyLevel = level; }
