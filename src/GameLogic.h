#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <raylib.h>
#include <math.h>
#include <iostream>

struct Block{
    Vector2 position;
    Color color;
};

struct Shape{
    Vector2 blocks[4];
    Color color;
};

class GameLogic{
public:
    GameLogic(int rows = 0, int cols = 0);

    Block grid[20][20];
    Shape shapes[7];

    int getScore();
    Shape getShape(int id);

    int getRandomShapeIndex(int lastIndex);

    void applyShape(Shape shape, int startX, int startY);
    Shape rotateShape(Shape shape, int rotationDirection);

    bool canMoveShape(Shape shape, int startX, int startY);
    bool canMoveShapeLeftRight(Shape shape, int startX, int startY, int deltaX);
    bool canRotateShape(Shape shape, int startX, int startY, int rotationDirection);

    void checkAndRemoveCompletedRows();

private:
    int score;

    int rows;
    int cols;

    bool colorsAreEqual(Color c1, Color c2);
};

#endif // GAMELOGIC_H