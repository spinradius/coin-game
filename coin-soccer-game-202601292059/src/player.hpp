#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/System/Vector2.hpp>

class Player {
public:
  Player();
  void update();
  void move(float dx, float dy);
  void shoot();
  sf::Vector2f getPosition() const;
  float getRadius() const;
  void resetPosition();

private:
  sf::Vector2f position;
  float speed;
  float radius;
  
  // Helper method
  void clampToBounds(float offset);
};

#endif // PLAYER_HPP