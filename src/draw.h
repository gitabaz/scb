#pragma once
#include "raylib.h"
#include "piece.h"

void DrawBorder(int boardDimension, Color borderColor);
void DrawBoardSquares(Board board, int squareDimension);
void DrawBoardPieces(Board board, Texture2D texture, int pieceDimension);
void DrawSelectSquare(Board board, Vector2 mouse, int squareDimension);
void ClearSelectSquare(Board board);
