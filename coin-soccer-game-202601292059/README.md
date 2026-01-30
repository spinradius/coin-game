# Coin Soccer Game

## Overview
Coin Soccer is a 2D soccer game where a player competes against a computer-controlled opponent. The game features three levels of difficulty, providing a challenging experience for players of all skill levels. The game is designed to be simple yet engaging, with intuitive controls and a vibrant graphical interface.

## Features
- Single-player mode against AI
- Three levels of difficulty: Easy, Medium, Hard
- Simple controls for player movement and shooting
- 2D graphics with a canvas size of 800x600
- Sound effects for actions and events
- Instructions and title screen

## Controls
- **Arrow Keys**: Move the player
- **Spacebar**: Shoot the ball

## Game Structure
The game is structured into several key components:
- **Game Class**: Manages the overall game state, including player actions and AI behavior.
- **Player Class**: Represents the human player and handles input and movement.
- **AI Class**: Controls the computer player and makes decisions based on the game state.
- **Utility Functions**: Provides common functionalities such as collision detection and score management.
- **Graphics**: Handles rendering of the game field and players on the screen.

## Requirements
To run the Coin Soccer game, ensure you have the following installed on your macOS system:
- A C++ compiler (e.g., g++)
- Make utility

## Installation
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/coin-soccer-game.git
   cd coin-soccer-game
   ```

2. Build the project using the Makefile:
   ```
   make
   ```

3. Run the game:
   ```
   ./coin-soccer-game
   ```

## External Libraries
This project may require additional libraries. Please refer to `requirements.txt` for a list of dependencies and installation instructions.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.