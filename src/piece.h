#pragma once
#include "raylib.h"
#include <stddef.h>

#define DSC (Color) {6, 52, 125, 185}
#define LSC WHITE
#define SELCOLOR (Color) {100, 250, 100, 185}
#define SELCOLOR2 (Color) {235, 65, 50, 185}
#define SELCOLOR3 (Color) {250, 185, 0, 185}

typedef struct ChessPiece {
    float x;
    float y;
    char type;
} ChessPiece;

typedef struct ChessSquare {
    int r;
    int c;
    ChessPiece piece;
    Color color;
    char type;
} ChessSquare;

typedef ChessSquare Board[8][8];

void initBoardSquares(Board board);
void initBoardPieces(Board board);
Vector2 findNearestSquare(Vector2 mouse, int squareDimension);
bool inBoardBounds(int x, int y);
