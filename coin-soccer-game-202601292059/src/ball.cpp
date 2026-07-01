#include "ball.hpp"
#include "utils.hpp"
#include <cmath>

// Constants
namespace {
  constexpr float INITIAL_X = 400.f;
  constexpr float INITIAL_Y = 300.f;
  constexpr float BALL_RADIUS = 10.f;
  constexpr float FRICTION_COEFFICIENT = 0.98f;
  constexpr float BOUNCE_DAMPING = 0.8f;
  constexpr float VELOCITY_THRESHOLD = 0.1f;
  constexpr float FRAME_RATE_SCALE = 60.f;
}

Ball::Ball()
    : position(INITIAL_X, INITIAL_Y), velocity(0.f, 0.f), radius(BALL_RADIUS),
      friction(FRICTION_COEFFICIENT) {}

void Ball::update(float deltaTime) {
  applyFriction();
  updatePosition(deltaTime);
  clampToBounds();
}

void Ball::applyFriction() {
  velocity *= friction;
  
  // Stop ball if it's moving very slowly
  if (std::abs(velocity.x) < VELOCITY_THRESHOLD)
    velocity.x = 0.f;
  if (std::abs(velocity.y) < VELOCITY_THRESHOLD)
    velocity.y = 0.f;
}

void Ball::updatePosition(float deltaTime) {
  position += velocity * deltaTime * FRAME_RATE_SCALE;
}

void Ball::clampToBounds() {
  bounceX();
  bounceY();
}

void Ball::bounceX() {
  if (position.x - radius < 0) {
    position.x = radius;
    velocity.x = -velocity.x * BOUNCE_DAMPING;
  } else if (position.x + radius > SCREEN_WIDTH) {
    position.x = SCREEN_WIDTH - radius;
    velocity.x = -velocity.x * BOUNCE_DAMPING;
  }
}

void Ball::bounceY() {
  if (position.y - radius < 0) {
    position.y = radius;
    velocity.y = -velocity.y * BOUNCE_DAMPING;
  } else if (position.y + radius > SCREEN_HEIGHT) {
    position.y = SCREEN_HEIGHT - radius;
    velocity.y = -velocity.y * BOUNCE_DAMPING;
  }
}

void Ball::reset() {
  position = sf::Vector2f(INITIAL_X, INITIAL_Y);
  velocity = sf::Vector2f(0.f, 0.f);
}

void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }

sf::Vector2f Ball::getPosition() const { return position; }

sf::Vector2f Ball::getVelocity() const { return velocity; }
