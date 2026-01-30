#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// Constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PLAYER_SPEED = 5;
const int AI_SPEED = 3;

// Utility Functions
void initializeRandomSeed();

bool checkCollision(const sf::FloatRect &rect1, const sf::FloatRect &rect2);

#endif // UTILS_HPP