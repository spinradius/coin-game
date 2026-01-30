#ifndef AI_HPP
#define AI_HPP

#include "ball.hpp"
#include "player.hpp"
#include <SFML/System/Vector2.hpp>

class AI {
public:
  AI();
  void update(const Ball &ball, int level);
  void move(float dx, float dy);
  sf::Vector2f getPosition() const;
  float getRadius() const;
  void resetPosition();

private:
  sf::Vector2f position;
  float speed;
  float radius;

  // Stuck detection logic
  float retreatTimer;
  bool isRetreating;
};

#endif // AI_HPP