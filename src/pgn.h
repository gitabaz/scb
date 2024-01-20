#pragma once
#include <stddef.h>

typedef struct Position {
    char* piecePlacement;
    char activeColor;
    char* castlingRights;
    char* enPassant;
    size_t halfMoveClock;
    size_t fullMoveCount;
} Position;

Position PositionFromFEN(const char *str);
void PositionFree(Position *pos);
