#ifndef SCENE_H
#define SCENE_H

#include "GameLogic.h"

class Scene{
public:
    Scene();
    void run();
private:
    int screenWidth;
    int screenHeight;

    int rows;
    int cols;

    GameLogic game;

    float distance(Vector2 p1, Vector2 p2);

    void drawGrid(Block grid[][20], int rows, int cols);
    void drawBlock(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, Color color);
    void drawNextShape(Shape shape, int offsetX, int offsetY);

};

#endif // SCENE_H