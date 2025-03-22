# Menagerie
# Meangerie

## Overview
Meangerie is a tile-matching puzzle game developed using **C++** and **SFML**. Players swap tiles to form matches and score points. The game features two levels:

- **Level 1 (Easy Mode):** No time restriction, only limited moves.
- **Level 2 (Hard Mode):** A time-restricted challenge with limited moves.

## Features
- Two distinct game modes (easy and hard).
- A scoring system based on tile-matching mechanics.
- Background music and sound effects.
- Smooth tile animations for an engaging experience.
- SFML-based graphics for an interactive UI.

## Installation & Setup
### Prerequisites
Ensure you have the following installed on your system:
- **C++ Compiler** (GCC/Clang/MSVC)
- **SFML Library** (2.5 or later)

### Building the Game
1. Clone this repository:
   
   git clone https://github.com/your-username/meangerie.git
   cd meangerie
   
3. Install SFML (if not already installed):
   - **Ubuntu:**
       sudo apt-get install libsfml-dev
  
   - **Windows:**
       Download and install SFML from [https://www.sfml-dev.org](https://www.sfml-dev.org).
   
4. Compile the game:
   g++ main.cpp -o meangerie -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

5. Run the game:
   ./meangerie

## How to Play
1. Launch the game and choose a level.
2. Swap adjacent tiles to match three or more of the same type.
3. Earn points by making matches.
4. Level 1: Complete within the move limit.
5. Level 2: Complete before the timer runs out.
6. Reach the target score to win!

## Controls
- **Mouse Click**: Select and swap tiles.
- **Escape (Esc) Key**: Exit the game.

## Assets
- **Sprites**: Located in `sprites/`
- **Fonts**: Located in `fonts/`
- **Audio**: Located in `audio/`

## Contributing
Feel free to fork the repository and submit pull requests for improvements and bug fixes.

## License
This project is open-source and licensed under the MIT License.

## Credits
- Developed by Huzaifa Azam
- Powered by **SFML**

