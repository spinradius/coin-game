#include "utils.hpp"

void initializeRandomSeed() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

bool checkCollision(const sf::FloatRect &rect1, const sf::FloatRect &rect2) {
  return rect1.intersects(rect2);
}