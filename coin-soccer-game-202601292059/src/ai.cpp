#include "ai.hpp"
#include "utils.hpp"
#include <cmath>
#include <cstdlib>

AI::AI()
    : position(700.f, 300.f), speed(3.f), radius(15.f), retreatTimer(0.f),
      isRetreating(false) {}

void AI::update(const Ball &ball, int level) {
  sf::Vector2f bPos = ball.getPosition();
  sf::Vector2f dir = bPos - position;
  float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
  float dt = 1.f / 60.f;

  // Detect if we are stuck at boundaries
  bool atBoundaryX = (position.x <= radius + 15.f ||
                      position.x >= SCREEN_WIDTH - radius - 15.f);
  bool atBoundaryY = (position.y <= radius + 15.f ||
                      position.y >= SCREEN_HEIGHT - radius - 15.f);

  // Trigger retreat if touching the ball at a boundary
  if (!isRetreating && (atBoundaryX || atBoundaryY) && dist < radius + 15.f) {
    isRetreating = true;
    retreatTimer = 0.6f; // Retreat for 0.6 seconds
  }

  // difficulty multiplier
  float currentSpeed = speed;
  if (level == 2)
    currentSpeed *= 1.5f;
  if (level == 3)
    currentSpeed *= 2.0f;

  if (isRetreating) {
    retreatTimer -= dt;
    if (retreatTimer <= 0) {
      isRetreating = false;
    }
    // Move AWAY from the ball
    if (dist > 0) {
      position -= (dir / dist) * currentSpeed;
    }
  } else {
    // SAFER: if AI is reasonably close to the ball, approach a point slightly
    // behind the ball (relative to the left goal) so kicks are biased toward
    // the goal. Otherwise, keep normal tracking behavior.
    sf::Vector2f goalPos = sf::Vector2f(12.f, SCREEN_HEIGHT / 2.f);
    sf::Vector2f aim = bPos - goalPos; // vector from goal to ball
    float aimLen = std::sqrt(aim.x * aim.x + aim.y * aim.y);
    sf::Vector2f aimDir = (aimLen > 0) ? (aim / aimLen) : sf::Vector2f(1.f, 0.f);

    float aimTriggerDist = 150.f; // start aiming when within this distance
    if (dist < aimTriggerDist) {
      float approachOffset = radius + 8.f;
      sf::Vector2f approachPoint = bPos + aimDir * approachOffset; // stand behind ball toward goal

      sf::Vector2f toApproach = approachPoint - position;
      float distApproach = std::sqrt(toApproach.x * toApproach.x + toApproach.y * toApproach.y);
      if (distApproach > 1.f) {
        sf::Vector2f moveDir = toApproach / distApproach;
        position += moveDir * currentSpeed;
      }
    } else {
      // Normal tracking
      if (dist > 0) {
        sf::Vector2f moveDir = dir / dist;
        position += moveDir * currentSpeed;
      }
    }
  }

  // Boundaries clamping (ensure AI always visible)
  float offset = 10.f;
  if (position.x < offset + radius)
    position.x = offset + radius;
  if (position.x > SCREEN_WIDTH - offset - radius)
    position.x = SCREEN_WIDTH - offset - radius;
  if (position.y < offset + radius)
    position.y = offset + radius;
  if (position.y > SCREEN_HEIGHT - offset - radius)
    position.y = SCREEN_HEIGHT - offset - radius;
}

void AI::move(float dx, float dy) {
  position.x += dx;
  position.y += dy;
}

sf::Vector2f AI::getPosition() const { return position; }

float AI::getRadius() const { return radius; }

void AI::resetPosition() {
  position = sf::Vector2f(700.f, 300.f);
  isRetreating = false;
  retreatTimer = 0.f;
}