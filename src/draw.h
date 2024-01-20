#pragma once
#include "raylib.h"
#include "piece.h"

typedef struct ArrowList {
    Vector2 *startSquares;
    Vector2 *endSquares;
    Color *colors;
    size_t len;
    size_t capacity;
} ArrowList;

void DrawBorder(int boardDimension, Color borderColor);
void DrawBoardSquares(Board board, int squareDimension);
void DrawBoardPieces(Board board, Texture2D texture, int pieceDimension);
void DrawSelectSquare(Board board, Vector2 mouse, int squareDimension);
void ClearSelectSquare(Board board);
void DrawArrow(Vector2 startSquare, Vector2 endSquare, int squareDimension, Color color);
void DrawArrows(ArrowList *arrowList, int squareDimension);
void ArrowListInit(ArrowList *arrowList);
void ArrowListAdd(ArrowList *arrowList, Vector2 startSquare, Vector2 endSquare, Color color);
void ArrowListRemove(ArrowList *arrowList, int i);
int ArrowListArrowInList(ArrowList *arrowList, Vector2 startSquare, Vector2 endSquare, Color color);
void ArrowListFree(ArrowList *arrowList);
