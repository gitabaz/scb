#pragma once
#include "raylib.h"
#include <stddef.h>

#include "pgn.h"

#define DSC (Color) {6, 52, 125, 185}
#define LSC WHITE
#define SELCOLOR (Color) {100, 250, 60, 185}
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

void InitBoardSquares(Board board);
void InitBoardPieces(Board board);
Vector2 FindNearestSquare(Vector2 mouse, int squareDimension);
bool InBoardBounds(int x, int y);

void BoardFromPosition(Board board, Position pos);
