#include "draw.h"

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
