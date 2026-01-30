#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Canvas {
public:
  Canvas();
  void clear();
  void drawField();
  void drawPlayer(sf::Vector2f position, sf::Color color, float radius);
  void drawBall(sf::Vector2f position, float radius);
  void drawText(const std::string &text, sf::Vector2f position,
                unsigned int size = 24, sf::Color color = sf::Color::White);
  void display();
  bool isOpen() const;
  void pollEvents();

private:
  sf::RenderWindow window;
  sf::Font font;
  bool fontLoaded;
};

#endif // CANVAS_HPP