#include "canvas.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

Canvas::Canvas()
    : window(sf::VideoMode(800, 600), "Coin Soccer"), fontLoaded(false) {
  window.setFramerateLimit(60);

  namespace fs = std::filesystem;

  // Try several candidate locations for the font. When the game is launched
  // from a different working directory (for example from the user's home
  // folder), a plain relative path may not resolve to the repo's assets.
  std::vector<fs::path> candidates = {
      fs::path("assets/fonts/arial.ttf"), fs::path("./assets/fonts/arial.ttf"),
      fs::path("../assets/fonts/arial.ttf")};

  // Walk up parent directories looking for an `assets/fonts/arial.ttf`
  fs::path cwd = fs::current_path();
  fs::path p = cwd;
  for (int i = 0; i < 6; ++i) { // check up to 6 parent levels
    candidates.push_back(p / "assets" / "fonts" / "arial.ttf");
    if (!p.has_parent_path())
      break;
    p = p.parent_path();
  }

  // Common system font locations (helpful on macOS if bundled font is missing)
  candidates.push_back(fs::path("/Library/Fonts/Arial.ttf"));
  candidates.push_back(fs::path("/System/Library/Fonts/Supplemental/Arial.ttf"));

  bool loaded = false;
  for (const auto &cand : candidates) {
    if (fs::exists(cand)) {
      if (font.loadFromFile(cand)) {
        fontLoaded = true;
        loaded = true;
        std::cerr << "Loaded font from: " << cand << std::endl;
        // Also create a small debug file so automated runs can inspect the
        // resolved font path.
        std::ofstream dbg("font_debug.txt");
        if (dbg) {
          dbg << cand << std::endl;
          // Sanity-check glyph metrics for a common character
          try {
            auto glyph = font.getGlyph('A', 30, false);
            dbg << "glyph.advance=" << glyph.advance << "\n";
          } catch (...) {
            dbg << "glyph check failed\n";
          }
        }
        break;
      }
    }
  }

  if (!loaded) {
    std::cerr << "Warning: Could not load default font. UI text will not be "
                 "displayed.\n"
              << "Tried paths relative to CWD: " << cwd << std::endl;
  }
}

void Canvas::clear() {
  window.clear(sf::Color(34, 139, 34)); // Forest Green
}

void Canvas::drawField() {
  sf::RectangleShape pitchLine({780, 580});
  pitchLine.setPosition({10, 10});
  pitchLine.setFillColor(sf::Color::Transparent);
  pitchLine.setOutlineColor(sf::Color::White);
  pitchLine.setOutlineThickness(2);
  window.draw(pitchLine);

  sf::RectangleShape midLine({2, 580});
  midLine.setPosition({400, 10});
  midLine.setFillColor(sf::Color::White);
  window.draw(midLine);

  sf::CircleShape centerCircle(70);
  centerCircle.setPosition({330, 230});
  centerCircle.setFillColor(sf::Color::Transparent);
  centerCircle.setOutlineColor(sf::Color::White);
  centerCircle.setOutlineThickness(2);
  window.draw(centerCircle);

  // Goal areas
  sf::RectangleShape goalLeft({2, 100});
  goalLeft.setPosition({10, 250});
  goalLeft.setFillColor(sf::Color::Red);
  window.draw(goalLeft);

  sf::RectangleShape goalRight({2, 100});
  goalRight.setPosition({788, 250});
  goalRight.setFillColor(sf::Color::Blue);
  window.draw(goalRight);
}

void Canvas::drawPlayer(sf::Vector2f position, sf::Color color, float radius) {
  sf::CircleShape shape(radius);
  shape.setOrigin({radius, radius});
  shape.setPosition(position);
  shape.setFillColor(color);
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(2);
  window.draw(shape);
}

void Canvas::drawBall(sf::Vector2f position, float radius) {
  sf::CircleShape shape(radius);
  shape.setOrigin({radius, radius});
  shape.setPosition(position);
  shape.setFillColor(sf::Color::White);
  window.draw(shape);
}

void Canvas::drawText(const std::string &textStr, sf::Vector2f position,
                      unsigned int size, sf::Color color) {
  if (fontLoaded) {
    sf::Text text;
    text.setFont(font);
    text.setString(textStr);
    text.setCharacterSize(size);
    text.setPosition(position);
    text.setFillColor(color);
    window.draw(text);
  }
}

void Canvas::display() { window.display(); }

bool Canvas::isOpen() const { return window.isOpen(); }

void Canvas::pollEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}