#include "Scene.h"

Scene::Scene(){
    screenWidth = 600;
    screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tetris");

    SetTargetFPS(60);

    rows = screenHeight / 30;
    cols = screenWidth / 30;

    game = GameLogic(rows, cols);
}

void Scene::run(){

    int lastShapeIndex = -1;
    int currentShapeIndex = game.getRandomShapeIndex(lastShapeIndex);
    int nextShapeIndex = game.getRandomShapeIndex(currentShapeIndex);
    Shape currentShape = game.getShape(currentShapeIndex);
    Shape nextShape = game.getShape(nextShapeIndex);
    int shapeX = 9, shapeY = 0;

    float timer = 0.0f;
    float tickRate = 0.5f;
    float fastTickRate = 0.05f;

    while (!WindowShouldClose())
    {
        timer += GetFrameTime();

        if (IsKeyPressed(KEY_LEFT) && game.canMoveShapeLeftRight(currentShape, shapeX, shapeY, -1)) {
            shapeX -= 1;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.canMoveShapeLeftRight(currentShape, shapeX, shapeY, 1)) {
            shapeX += 1;
        }

        if (IsKeyPressed(KEY_UP) && game.canRotateShape(currentShape, shapeX, shapeY, 1)) {
            currentShape = game.rotateShape(currentShape, 1);
        }
        if (IsKeyPressed(KEY_DOWN) && game.canRotateShape(currentShape, shapeX, shapeY, -1)) {
            currentShape = game.rotateShape(currentShape, -1);
        }

        float currentTickRate = IsKeyDown(KEY_S) ? fastTickRate : tickRate;

        if (timer >= currentTickRate) {
            timer = 0.0f;
            if (game.canMoveShape(currentShape, shapeX, shapeY + 1)) {
                shapeY += 1;
            } else {
                game.applyShape(currentShape, shapeX, shapeY);
                game.checkAndRemoveCompletedRows();

                lastShapeIndex = currentShapeIndex;
                currentShapeIndex = nextShapeIndex;
                currentShape = nextShape;
                nextShapeIndex = game.getRandomShapeIndex(currentShapeIndex);
                nextShape = game.getShape(nextShapeIndex);
                shapeX = 7;
                shapeY = 0;
            }
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            drawGrid(game.grid, rows, cols);

            for (int i = 0; i < 4; i++) {
                Vector2 blockPos = { (shapeX + (int)(currentShape.blocks[i].x / 30.0)) * 30.0, (shapeY + (int)(currentShape.blocks[i].y / 30.0)) * 30.0 };
                Vector2 v1 = { blockPos.x + 30.f, blockPos.y };
                Vector2 v2 = { blockPos.x, blockPos.y + 30.f };
                Vector2 v3 = { blockPos.x + 30.f, blockPos.y + 30.f };
                Vector2 v4 = { blockPos.x, blockPos.y };

                drawBlock(v1, v2, v3, v4, currentShape.color);
            }

            drawNextShape(nextShape, 16, 1);

            DrawText(TextFormat("Score: %d", game.getScore()), 30, 35, 20, WHITE);

        EndDrawing();
    }
}

float Scene::distance(Vector2 p1, Vector2 p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

void Scene::drawGrid(Block grid[][20], int rows, int cols){
    int centerStartCol = cols / 2 - 5;
    int centerEndCol = cols / 2 + 5;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color blockColor = (j >= centerStartCol && j < centerEndCol) 
                                ? grid[i][j].color : BLACK;
            Block block = grid[i][j];
            Vector2 v1 = { block.position.x + 30.f, block.position.y };
            Vector2 v2 = { block.position.x, block.position.y + 30.f };
            Vector2 v3 = { block.position.x + 30.f, block.position.y + 30.f };
            Vector2 v4 = { block.position.x, block.position.y };

            drawBlock(v1, v2, v3, v4, blockColor);
        }
    }
}

void Scene::drawBlock(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, Color color){
    DrawTriangle(v1, v2, v3, Fade(color, 0.8f));

    DrawTriangle(v1, v4, v2, Fade(color, 0.6f));

    float centerX = (v1.x + v2.x + v3.x + v4.x) / 4;
    float centerY = (v1.y + v2.y + v3.y + v4.y) / 4;

    float outerSquareSize = distance(v1, v2);
    float innerSquareSize = outerSquareSize / 1.8f;

    DrawRectangle(centerX - innerSquareSize / 2, centerY - innerSquareSize / 2, innerSquareSize, innerSquareSize, Fade(color, 0.4f));
}

void Scene::drawNextShape(Shape shape, int offsetX, int offsetY){
    for (int i = 0; i < 4; i++) {
        Vector2 blockPos = { (offsetX + (int)(shape.blocks[i].x / 30.0)) * 30.0, (offsetY + (int)(shape.blocks[i].y / 30.0)) * 30.0 };
        Vector2 v1 = { blockPos.x + 30.f, blockPos.y };
        Vector2 v2 = { blockPos.x, blockPos.y + 30.f };
        Vector2 v3 = { blockPos.x + 30.f, blockPos.y + 30.f };
        Vector2 v4 = { blockPos.x, blockPos.y };

        drawBlock(v1, v2, v3, v4, shape.color);
    }
}