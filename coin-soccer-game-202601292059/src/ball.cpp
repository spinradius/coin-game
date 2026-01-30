#include "ball.hpp"
#include "utils.hpp"

Ball::Ball()
    : position(400.f, 300.f), velocity(0.f, 0.f), radius(10.f),
      friction(0.98f) {}

void Ball::update(float deltaTime) {
  // Apply friction
  velocity *= friction;

  // Stop ball if it's moving very slowly
  if (std::abs(velocity.x) < 0.1f)
    velocity.x = 0.f;
  if (std::abs(velocity.y) < 0.1f)
    velocity.y = 0.f;

  // Update position
  position += velocity * deltaTime * 60.f; // Scale by frame rate for now

  // Bouncing off walls
  if (position.x - radius < 0) {
    position.x = radius;
    velocity.x = -velocity.x * 0.8f; // Lose energy on bounce
  } else if (position.x + radius > SCREEN_WIDTH) {
    position.x = SCREEN_WIDTH - radius;
    velocity.x = -velocity.x * 0.8f;
  }

  if (position.y - radius < 0) {
    position.y = radius;
    velocity.y = -velocity.y * 0.8f;
  } else if (position.y + radius > SCREEN_HEIGHT) {
    position.y = SCREEN_HEIGHT - radius;
    velocity.y = -velocity.y * 0.8f;
  }
}

void Ball::reset() {
  position = sf::Vector2f(400.f, 300.f);
  velocity = sf::Vector2f(0.f, 0.f);
}

void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }

sf::Vector2f Ball::getPosition() const { return position; }

sf::Vector2f Ball::getVelocity() const { return velocity; }
