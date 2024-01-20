#include <stdio.h>
#include "raylib.h"

#include "piece.h"
#include "draw.h"

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
    //printf("pieceDimension: %d, boardDimension: %d\n", pieceDimension, boardDimension);
    
    bool isPieceGrabbed = false;
    Vector2 pieceGrabbedSq;
    ChessPiece *pieceGrabbed;
    bool isArrowStarted = false;
    Vector2 arrowStartSq;

    ArrowList arrowList = {0};
    ArrowListInit(&arrowList);

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            UnloadImage(img);
            UnloadTexture(texture);
            pieceTextureHeight = scaleFactor * GetScreenHeight();
            int pieceTextureWidth = 3.0 * pieceTextureHeight;
            //printf("RESIZE: width: %d, height: %d\n", pieceTextureWidth, pieceTextureHeight);
            img = LoadImageSvg("assets/chess_pieces.svg", pieceTextureWidth, pieceTextureHeight);
            texture = LoadTextureFromImage(img);
            pieceDimension = pieceTextureWidth / 6.0;
            boardDimension = 8 * pieceDimension;
        }

        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            if (!isArrowStarted) {
                arrowStartSq = findNearestSquare(mouse, pieceDimension);
                isArrowStarted = inBoardBounds((int) arrowStartSq.x, (int) arrowStartSq.y);
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ClearSelectSquare(board);
            arrowList.len = 0;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (!isPieceGrabbed) {
                pieceGrabbedSq = findNearestSquare(mouse, pieceDimension);
                if (inBoardBounds((int) pieceGrabbedSq.x, (int) pieceGrabbedSq.y)) {
                    isPieceGrabbed = true;
                    pieceGrabbed = &board[(int) pieceGrabbedSq.y][(int) pieceGrabbedSq.x].piece;
                }
            } else if (pieceGrabbed->type != 0) {
                pieceGrabbed->x = mouse.x / pieceDimension - 1.0 / 2.0;
                pieceGrabbed->y = mouse.y / pieceDimension - 1.0 / 2.0;
            }
            //printf("x: %f, y: %f\n", mouse.x, mouse.y);
            //printf("sqx: %f, sqy: %f\n", pieceGrabbedSq.x, pieceGrabbedSq.y);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            if (isArrowStarted) {
                Vector2 arrowEndSq = findNearestSquare(mouse, pieceDimension);
                if ((int) arrowStartSq.y != (int) arrowEndSq.y || (int) arrowStartSq.x != (int) arrowEndSq.x) {
                    Color selColor = SELCOLOR;
                    if (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) {
                        selColor = SELCOLOR2;
                    } else if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
                        selColor = SELCOLOR3;
                    }
                    if (inBoardBounds((int) arrowEndSq.x, (int) arrowEndSq.y)) {
                        ArrowListAdd(&arrowList, arrowStartSq, arrowEndSq, selColor);
                    }
                } else {
                    DrawSelectSquare(board, mouse, pieceDimension);
                }
            }
            isArrowStarted = false;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (isPieceGrabbed && pieceGrabbed->type != 0) {
                Vector2 pieceDroppedSq = findNearestSquare(mouse, pieceDimension);
                if (inBoardBounds((int) pieceDroppedSq.x, (int) pieceDroppedSq.y)) {
                    board[(int) pieceDroppedSq.y][(int) pieceDroppedSq.x].piece = (ChessPiece) {pieceDroppedSq.x, pieceDroppedSq.y, pieceGrabbed->type};
                    if ((int) pieceDroppedSq.y != (int) pieceGrabbedSq.y || (int) pieceDroppedSq.x != (int) pieceGrabbedSq.x) {
                        board[(int) pieceGrabbedSq.y][(int) pieceGrabbedSq.x].piece = (ChessPiece) {0};
                    }
                } else {
                    board[(int) pieceGrabbedSq.y][(int) pieceGrabbedSq.x].piece = (ChessPiece) {pieceGrabbedSq.x, pieceGrabbedSq.y, pieceGrabbed->type};
                }
            }
            isPieceGrabbed = false;
            pieceGrabbedSq = (Vector2) {0};
            pieceGrabbed = NULL;
        }

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawBoardSquares(board, pieceDimension);
            DrawBorder(boardDimension, BLACK);
            DrawBoardPieces(board, texture, pieceDimension);

            DrawArrows(&arrowList, pieceDimension);

            DrawText("scb - simple chess board", 190, 200, 20, BLACK);
        EndDrawing();
    }

    ArrowListFree(&arrowList);
    CloseWindow();

    return 0;
}
