#include "draw.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void DrawBorder(int boardDimension, Color borderColor) {
    DrawRectangleLines(0, 0, boardDimension, boardDimension, borderColor);
    for (size_t r = 0; r < 8; r += 1) {
        for (size_t c = 0; c < 8; c += 1) {
            DrawRectangleLines(c * boardDimension / 8, r * boardDimension / 8, boardDimension / 8, boardDimension / 8, borderColor);
        }
    }
}

void DrawBoardSquares(Board board, int squareDimension) {
    for (size_t r = 0; r < 8; r += 1) {
        for (size_t c = 0; c < 8; c += 1) {
            DrawRectangle(
                    c * squareDimension,
                    r * squareDimension,
                    squareDimension,
                    squareDimension,
                    board[r][c].color
            );
        }
    }
}

void DrawBoardPieces(Board board, Texture2D texture, int pieceDimension) {
    int textureOffsetX = 0;
    int textureOffsetY = 0;

    for (size_t r = 0; r < 8; r++) {
        for (size_t c = 0; c < 8; c++) {
            switch(board[r][c].piece.type) {
                case 'P':
                    textureOffsetX = 5 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'N':
                    textureOffsetX = 3 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'B':
                    textureOffsetX = 2 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'R':
                    textureOffsetX = 4 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'Q':
                    textureOffsetX = 1 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'K':
                    textureOffsetX = 0 * pieceDimension;
                    textureOffsetY = 0;
                    break;
                case 'p':
                    textureOffsetX = 5 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                case 'n':
                    textureOffsetX = 3 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                case 'b':
                    textureOffsetX = 2 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                case 'r':
                    textureOffsetX = 4 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                case 'q':
                    textureOffsetX = 1 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                case 'k':
                    textureOffsetX = 0 * pieceDimension;
                    textureOffsetY = 1 * pieceDimension;
                    break;
                default:
                    continue;
            }

            DrawTexturePro(
                    texture,
                    (Rectangle){textureOffsetX, textureOffsetY, pieceDimension, pieceDimension},
                    (Rectangle){board[r][c].piece.x * pieceDimension, board[r][c].piece.y * pieceDimension, pieceDimension, pieceDimension},
                    (Vector2){0, 0},
                    0,
                    WHITE
            );
        }
    }

}

void DrawSelectSquare(Board board, Vector2 mouse, int squareDimension) {
    Vector2 sq = findNearestSquare(mouse, squareDimension);
    Color selColor = SELCOLOR;
    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) {
        selColor = SELCOLOR2;
    } else if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        selColor = SELCOLOR3;
    }
    board[(int)sq.y][(int)sq.x].color = selColor;
}

void ClearSelectSquare(Board board) {
    for (size_t r = 0; r < 8; r++) {
        for (size_t c = 0; c < 8; c++) {
            if (board[r][c].type == 'L') board[r][c].color = LSC;
            if (board[r][c].type == 'D') board[r][c].color = DSC;
        }
    }
}


void DrawArrow(Vector2 startSquare, Vector2 endSquare, int squareDimension, Color color) {
    float length = sqrt(pow(startSquare.x - endSquare.x, 2) + pow(startSquare.y - endSquare.y, 2));
    float width = 0.25;
    float angle = atan2(endSquare.y - startSquare.y, endSquare.x - startSquare.x);

    Rectangle rec = (Rectangle) {
        squareDimension * (startSquare.x + 0.5),
        squareDimension * (startSquare.y + 0.5),
        squareDimension * length,
        squareDimension * width
    };
    DrawRectanglePro(rec, (Vector2) {0, rec.height * 0.5}, angle * RAD2DEG, color);

    float ca = cos(angle);
    float sa = sin(angle);
    float p1x, p1y, p2x, p2y, p3x, p3y;
    p1x = squareDimension * 0.5;
    p1y = squareDimension * 0.25;
    p2x = squareDimension * 0.5;
    p2y = squareDimension * 0.75;
    p3x = squareDimension * 0.75;
    p3y = squareDimension * 0.5;

    DrawTriangle(
        (Vector2) {
            ca * (p1x - 0.5 * squareDimension) - sa * (p1y - 0.5 * squareDimension) + (endSquare.x + 0.5) * squareDimension,
            sa * (p1x - 0.5 * squareDimension) + ca * (p1y - 0.5 * squareDimension) + (endSquare.y + 0.5) * squareDimension
        },
        (Vector2) {
            ca * (p2x - 0.5 * squareDimension) - sa * (p2y - 0.5 * squareDimension) + (endSquare.x + 0.5) * squareDimension,
            sa * (p2x - 0.5 * squareDimension) + ca * (p2y - 0.5 * squareDimension) + (endSquare.y + 0.5) * squareDimension
        },
        (Vector2) {
            ca * (p3x - 0.5 * squareDimension) - sa * (p3y - 0.5 * squareDimension) + (endSquare.x + 0.5) * squareDimension,
            sa * (p3x - 0.5 * squareDimension) + ca * (p3y - 0.5 * squareDimension) + (endSquare.y + 0.5) * squareDimension
        },
        color
    );
}

void DrawArrows(ArrowList *arrowList, int squareDimension) {
    for (size_t i = 0; i < arrowList->len; i++) {
        DrawArrow(arrowList->startSquares[i], arrowList->endSquares[i], squareDimension, SELCOLOR);
    }
}


void ArrowListInit(ArrowList *arrowList) {
    arrowList->startSquares = malloc(10 * sizeof(arrowList->startSquares));
    arrowList->endSquares = malloc(10 * sizeof(arrowList->endSquares));
    arrowList->len = 0;
    arrowList->capacity = 10;
}

void ArrowListAdd(ArrowList *arrowList, Vector2 startSquare, Vector2 endSquare) {
    if (arrowList->len < arrowList->capacity) {
        arrowList->startSquares[arrowList->len] = startSquare;
        arrowList->endSquares[arrowList->len] = endSquare;
        arrowList->len += 1;
    }
}

void ArrowListFree(ArrowList *arrowList) {
    free(arrowList->startSquares);
    free(arrowList->endSquares);
}
