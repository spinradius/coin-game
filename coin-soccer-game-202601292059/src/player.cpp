#include "player.hpp"
#include "utils.hpp"
#include <SFML/Window/Keyboard.hpp>

// Constants
namespace {
  constexpr float BOUNDARY_OFFSET = 10.f;
  constexpr float INITIAL_X = 100.f;
  constexpr float INITIAL_Y = 300.f;
}

Player::Player() : position(INITIAL_X, INITIAL_Y), speed(5.f), radius(15.f) {}

void Player::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    position.y -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    position.y += speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    position.x -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    position.x += speed;

  clampToBounds(BOUNDARY_OFFSET);
}

void Player::clampToBounds(float offset) {
  if (position.x < offset + radius)
    position.x = offset + radius;
  if (position.x > SCREEN_WIDTH - offset - radius)
    position.x = SCREEN_WIDTH - offset - radius;
  if (position.y < offset + radius)
    position.y = offset + radius;
  if (position.y > SCREEN_HEIGHT - offset - radius)
    position.y = SCREEN_HEIGHT - offset - radius;
}

void Player::move(float dx, float dy) {
  position.x += dx;
  position.y += dy;
}

void Player::shoot() {
  // Dash implementation
}

sf::Vector2f Player::getPosition() const { return position; }

float Player::getRadius() const { return radius; }

void Player::resetPosition() { position = sf::Vector2f(INITIAL_X, INITIAL_Y); }