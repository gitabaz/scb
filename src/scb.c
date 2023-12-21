#include <stdio.h>
#include "raylib.h"

#include "piece.h"

//#define DSC (Color) {6, 52, 125, 185}
//#define LSC WHITE
//#define SELCOLOR (Color) {250, 185, 0, 185}

void DrawBorder(int boardDimension, Color borderColor) {
    DrawRectangleLines(0, 0, boardDimension, boardDimension, borderColor);
    for (size_t r = 0; r < 8; r += 1) {
        for (size_t c = 0; c < 8; c += 1) {
            DrawRectangleLines(c * boardDimension / 8, r * boardDimension / 8, boardDimension / 8, boardDimension / 8, borderColor);
        }
    }
}
//void DrawBoardSquares(int squareDimension, Color lightSquaresColor, Color darkSquaresColor) {
//    for (size_t x = 0; x < 8; x += 2) {
//        for (size_t y = 0; y < 8; y += 2) {
//            DrawRectangle(x * squareDimension, y * squareDimension, squareDimension, squareDimension, lightSquaresColor);
//            DrawRectangle((x + 1) * squareDimension, (y + 1) * squareDimension, squareDimension, squareDimension, lightSquaresColor);
//            DrawRectangle((x+1) * squareDimension, y * squareDimension, squareDimension, squareDimension, darkSquaresColor);
//            DrawRectangle(x * squareDimension, (y + 1) * squareDimension, squareDimension, squareDimension, darkSquaresColor);
//        }
//    }
//}
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

Vector2 findNearestSquare(Vector2 mouse, int squareDimension) {
    int x = mouse.x / squareDimension;
    int y = mouse.y / squareDimension;

    return (Vector2) {x, y};
}

int main() {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "scb");
    SetTargetFPS(60);

    Board board = {0};
    initBoardSquares(board);
    initBoardPieces(board);

    const float scaleFactor = 0.2;
    int pieceTextureHeight = screenHeight * scaleFactor;
    int pieceTextureWidth = 3 * pieceTextureHeight;
    int pieceDimension = pieceTextureWidth / 6.0;
    Image img = LoadImageSvg("assets/chess_pieces.svg", pieceTextureWidth, pieceTextureHeight);
    Texture2D texture = LoadTextureFromImage(img);

    int boardDimension = 8 * pieceDimension;
    printf("pieceDimension: %d, boardDimension: %d\n", pieceDimension, boardDimension);
    
    bool isPieceGrabbed = false;
    Vector2 pieceGrabbedSq;
    ChessPiece *pieceGrabbed;
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            UnloadImage(img);
            UnloadTexture(texture);
            pieceTextureHeight = scaleFactor * GetScreenHeight();
            int pieceTextureWidth = 3.0 * pieceTextureHeight;
            printf("RESIZE: width: %d, height: %d\n", pieceTextureWidth, pieceTextureHeight);
            img = LoadImageSvg("assets/chess_pieces.svg", pieceTextureWidth, pieceTextureHeight);
            texture = LoadTextureFromImage(img);
            pieceDimension = pieceTextureWidth / 6.0;
            boardDimension = 8 * pieceDimension;
        }

        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Vector2 sq = findNearestSquare(mouse, pieceDimension);
            board[(int)sq.y][(int)sq.x].color = SELCOLOR;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (!isPieceGrabbed) {
                isPieceGrabbed = true;
                pieceGrabbedSq = findNearestSquare(mouse, pieceDimension);
                pieceGrabbed = &board[(int)pieceGrabbedSq.y][(int)pieceGrabbedSq.x].piece;
            }
            if (pieceGrabbed->type != 0) {
                pieceGrabbed->x = mouse.x / pieceDimension - 1.0 / 2.0;
                pieceGrabbed->y = mouse.y / pieceDimension - 1.0 / 2.0;
            }
            //printf("x: %f, y: %f\n", mouse.x, mouse.y);
            //printf("sqx: %f, sqy: %f\n", pieceGrabbedSq.x, pieceGrabbedSq.y);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (isPieceGrabbed && pieceGrabbed->type != 0) {
                Vector2 pieceDroppedSq = findNearestSquare(mouse, pieceDimension);
                board[(int)pieceDroppedSq.y][(int)pieceDroppedSq.x].piece = (ChessPiece) {pieceDroppedSq.x, pieceDroppedSq.y, pieceGrabbed->type};
                board[(int)pieceGrabbedSq.y][(int)pieceGrabbedSq.x].piece = (ChessPiece) {0};
            }
            isPieceGrabbed = false;
            pieceGrabbedSq = (Vector2) {0};
            pieceGrabbed = NULL;
        }

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawBoardSquares(board, pieceDimension);
            DrawBoardPieces(board, texture, pieceDimension);
            DrawBorder(boardDimension, BLACK);


            DrawText("scb - simple chess board", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
