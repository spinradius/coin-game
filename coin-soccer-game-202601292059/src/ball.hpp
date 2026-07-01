#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/System/Vector2.hpp>

class Ball {
public:
  Ball();
  void update(float deltaTime);
  void reset();
  void setVelocity(sf::Vector2f velocity);
  sf::Vector2f getPosition() const;
  sf::Vector2f getVelocity() const;

private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  float radius;
  float friction;
  
  // Helper methods
  void applyFriction();
  void updatePosition(float deltaTime);
  void clampToBounds();
  void bounceX();
  void bounceY();
};

#endif // BALL_HPP
