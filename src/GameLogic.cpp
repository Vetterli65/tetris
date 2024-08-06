#include "GameLogic.h"

GameLogic::GameLogic(int rows, int cols) : rows(rows), cols(cols){
    shapes[0] = { { {0, 0}, {0, 30}, {0, 60}, {0, 90} }, SKYBLUE };    // I
    shapes[1] = { { {0, 0}, {0, 30}, {30, 30}, {30, 60} }, ORANGE };    // L
    shapes[2] = { { {0, 0}, {30, 0}, {30, 30}, {30, 60} }, GOLD };      // Reverse L
    shapes[3] = { { {0, 0}, {30, 0}, {0, 30}, {30, 30} }, YELLOW };      // O
    shapes[4] = { { {0, 30}, {30, 0}, {30, 30}, {60, 0} }, GREEN };     // S
    shapes[5] = { { {0, 0}, {30, 0}, {30, 30}, {60, 30} }, PURPLE };    // T
    shapes[6] = { { {0, 0}, {0, 30}, {30, 30}, {30, 60} }, RED };        // Z

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].position = (Vector2){ j * 30.f, i * 30.f };
            grid[i][j].color = DARKGRAY;
        }
    }
    score = 0;
}

Shape GameLogic::getShape(int id){
    return shapes[id];
}

bool GameLogic::colorsAreEqual(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int GameLogic::getScore(){
    return score;
}

void GameLogic::applyShape(Shape shape, int startX, int startY){
    for (int i = 0; i < 4; i++) {
        int x = startX + (int)(shape.blocks[i].x / 30.0);
        int y = startY + (int)(shape.blocks[i].y / 30.0);

        if (x >= 0 && x < 20 && y >= 0 && y < 20) {
            grid[y][x].color = shape.color;
        }
    }
}

bool GameLogic::canMoveShape(Shape shape, int startX, int startY){
    for (int i = 0; i < 4; i++) {
        int x = startX + (int)(shape.blocks[i].x / 30.0);
        int y = startY + (int)(shape.blocks[i].y / 30.0);

        if (x < cols / 2 - 5 || x >= cols / 2 + 5 || y >= rows || (y >= 0 && !colorsAreEqual(grid[y][x].color, DARKGRAY))) {
            return false;
        }
    }
    return true;
}

bool GameLogic::canMoveShapeLeftRight(Shape shape, int startX, int startY, int deltaX){
    for (int i = 0; i < 4; i++) {
        int x = startX + (int)(shape.blocks[i].x / 30.0) + deltaX;
        int y = startY + (int)(shape.blocks[i].y / 30.0);

        if (x < cols / 2 - 5 || x >= cols / 2 + 5 || (y >= 0 && !colorsAreEqual(grid[y][x].color, DARKGRAY))) {
            return false;
        }
    }
    return true;
}

Shape GameLogic::rotateShape(Shape shape, int rotationDirection){
    Shape rotatedShape = shape;
    for (int i = 0; i < 4; i++) {
        float x = shape.blocks[i].x;
        float y = shape.blocks[i].y;
        if (rotationDirection == 1) {
            rotatedShape.blocks[i].x = y;
            rotatedShape.blocks[i].y = -x;
        } else {
            rotatedShape.blocks[i].x = -y;
            rotatedShape.blocks[i].y = x;
        }
    }
    return rotatedShape;
}

bool GameLogic::canRotateShape(Shape shape, int startX, int startY, int rotationDirection){
    Shape rotatedShape = rotateShape(shape, rotationDirection);
    return canMoveShape(rotatedShape, startX, startY);
}

int GameLogic::getRandomShapeIndex(int lastIndex){
    int newIndex;
    do {
        newIndex = GetRandomValue(0, 6);
    } while (newIndex == lastIndex);
    return newIndex;
}

void GameLogic::checkAndRemoveCompletedRows(){
    for (int i = 0; i < rows; i++) {
        bool rowComplete = true;
        for (int j = cols / 2 - 5; j < cols / 2 + 5; j++) {
            if (colorsAreEqual(grid[i][j].color, DARKGRAY)) {
                rowComplete = false;
                break;
            }
        }
        if (rowComplete) {
            score++;
            for (int k = i; k > 0; k--) {
                for (int j = cols / 2 - 5; j < cols / 2 + 5; j++) {
                    grid[k][j].color = grid[k - 1][j].color;
                }
            }
            for (int j = cols / 2 - 5; j < cols / 2 + 5; j++) {
                grid[0][j].color = DARKGRAY;
            }
        }
    }
}