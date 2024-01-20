#include <string.h>
#include <ctype.h>

#include "piece.h"

void InitBoardSquares(Board board) {
    for (size_t r = 0; r < 8; r += 2) {
        for (size_t c = 0; c < 8; c += 2) {
            board[r][c] = (ChessSquare) {c, r, (ChessPiece){0}, LSC, 'L'};
            board[r + 1][c + 1] = (ChessSquare) {c + 1, r + 1, (ChessPiece){0}, LSC, 'L'};
            board[r + 1][c] = (ChessSquare) {c + 1, r, (ChessPiece){0}, DSC, 'D'};
            board[r][c + 1] = (ChessSquare) {c, r + 1, (ChessPiece){0}, DSC, 'D'};
        }
    }
}

void ClearBoardPieces(Board board) {
    for (size_t r = 0; r < 8; r++) {
        for (size_t c = 0; c < 8; c++) {
            board[r][c].piece = (ChessPiece){c, r, '\0'};
        }
    }
}

void InitBoardPieces(Board board) {
    board[0][0].piece = (ChessPiece){0, 0, 'r'};
    board[0][1].piece = (ChessPiece){1, 0, 'n'};
    board[0][2].piece = (ChessPiece){2, 0, 'b'};
    board[0][3].piece = (ChessPiece){3, 0, 'q'};
    board[0][4].piece = (ChessPiece){4, 0, 'k'};
    board[0][5].piece = (ChessPiece){5, 0, 'b'};
    board[0][6].piece = (ChessPiece){6, 0, 'n'};
    board[0][7].piece = (ChessPiece){7, 0, 'r'};
    board[1][0].piece = (ChessPiece){0, 1, 'p'};
    board[1][1].piece = (ChessPiece){1, 1, 'p'};
    board[1][2].piece = (ChessPiece){2, 1, 'p'};
    board[1][3].piece = (ChessPiece){3, 1, 'p'};
    board[1][4].piece = (ChessPiece){4, 1, 'p'};
    board[1][5].piece = (ChessPiece){5, 1, 'p'};
    board[1][6].piece = (ChessPiece){6, 1, 'p'};
    board[1][7].piece = (ChessPiece){7, 1, 'p'};
    board[7][0].piece = (ChessPiece){0, 7, 'R'};
    board[7][1].piece = (ChessPiece){1, 7, 'N'};
    board[7][2].piece = (ChessPiece){2, 7, 'B'};
    board[7][3].piece = (ChessPiece){3, 7, 'Q'};
    board[7][4].piece = (ChessPiece){4, 7, 'K'};
    board[7][5].piece = (ChessPiece){5, 7, 'B'};
    board[7][6].piece = (ChessPiece){6, 7, 'N'};
    board[7][7].piece = (ChessPiece){7, 7, 'R'};
    board[6][0].piece = (ChessPiece){0, 6, 'P'};
    board[6][1].piece = (ChessPiece){1, 6, 'P'};
    board[6][2].piece = (ChessPiece){2, 6, 'P'};
    board[6][3].piece = (ChessPiece){3, 6, 'P'};
    board[6][4].piece = (ChessPiece){4, 6, 'P'};
    board[6][5].piece = (ChessPiece){5, 6, 'P'};
    board[6][6].piece = (ChessPiece){6, 6, 'P'};
    board[6][7].piece = (ChessPiece){7, 6, 'P'};
}

Vector2 FindNearestSquare(Vector2 mouse, int squareDimension) {
    int x = mouse.x / squareDimension;
    int y = mouse.y / squareDimension;

    return (Vector2) {x, y};
}

bool InBoardBounds(int x, int y) {
    if ((x < 8) && (x >= 0)) {
        if ((y < 8) && (y >= 0)) {
            return true;
        }
    }

    return false;
}

void BoardFromPosition(Board board, Position pos) {
    ClearBoardPieces(board);
    size_t r = 0;
    size_t c = 0;
    char ch;
    for (size_t i = 0; i < strlen(pos.piecePlacement); i++) {
        ch = pos.piecePlacement[i];
        if (ch == '/') {
            r += 1;
            c = 0;
        } else if (isdigit(ch)) {
            c += (ch - '0');
        } else {
            board[r][c].piece = (ChessPiece){c, r, ch};
            c += 1;
        }
    }

}
