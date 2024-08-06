# Tetris Project

Tetris is a classic puzzle game where the player must arrange falling shapes, known as tetrominoes, to complete horizontal lines without any gaps. This project implements the Tetris game.

## Features

- Implementation of the Tetris game logic.
- Graphical user interface using Raylib.
- Display of the next shape in the game.
- Ability to rotate shapes and speed up their fall.
- Scoring system with visual score display.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Vetterli65/tetris.git
   cd tetris
   ```
2. Ensure you have the necessary dependencies installed. This project requires:
    * A C++ compiler for Linux e.g., g++, clang++ or for windows a MinGW
    * Raylib and RayGUI included as dependencies in Cmake file
3. Naviagate to the build directory and build project:
    * For Linux
    ```bash
    cd build-linux
    cmake ..
    make
    ```
    * For Windows
    ```bash
    cd build-windows
    cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-toolchain.cmake ..
    make
4. Run the executable:
    ```bash
    ./tetris
    ```

## Usage

The **main.cpp** file contains an example of how to set up and run the Tetris game. Below is a brief explanation of the key components and how to use them.

### Example

The example in **main.cpp** demonstrates setting up the game and running it with a graphical interface.

```cpp
#include "Scene.h"

int main(){
    Scene scene();
    scene.run();
}
```

### Controls

- Arrow Keys: Move shapes left, right, or down.
- UP Arrow Key: Rotate the shape clockwise.
- DOWN Arrow Key: Rotate the shape counter clockwise.
- S key: to speed up the falling velocity.
