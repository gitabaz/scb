#pragma once
#include "raylib.h"
#include "piece.h"

void DrawBorder(int boardDimension, Color borderColor);
void DrawBoardSquares(Board board, int squareDimension);
void DrawBoardPieces(Board board, Texture2D texture, int pieceDimension);
