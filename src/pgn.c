#include "pgn.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//"rnbqkb1r/ppp1pppp/5n2/8/2pP4/4PN2/PP3PPP/RNBQKB1R b KQkq - 0 4"
//"rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

Position PositionFromFEN(const char *str) {

    Position pos;
    size_t currentField = 0;
    size_t fieldStart = 0;
    size_t fieldSize = 0;
    for(size_t i = 0; i < strlen(str); i++) {
        if (isspace(str[i])) {
            switch(currentField) {
                case 0:
                    fieldSize = i - fieldStart + 1; // includes terminator
                    pos.piecePlacement = malloc(fieldSize * sizeof(*pos.piecePlacement));
                    memcpy(&pos.piecePlacement[0], &str[fieldStart], fieldSize - 1);
                    pos.piecePlacement[i] = '\0';
                    fieldStart = i + 1;
                    break;
                case 1:
                    pos.activeColor = str[i-1];
                    fieldStart = i + 1;
                    break;
                case 2:
                    fieldSize = i - fieldStart + 1; // includes terminator
                    pos.castlingRights = malloc(fieldSize * sizeof(*pos.castlingRights));
                    memcpy(&pos.castlingRights[0], &str[fieldStart], fieldSize - 1);
                    pos.castlingRights[i] = '\0';
                    fieldStart = i + 1;
                    break;
                case 3:
                    fieldSize = i - fieldStart + 1; // includes terminator
                    pos.enPassant = malloc(fieldSize * sizeof(*pos.enPassant));
                    memcpy(&pos.enPassant[0], &str[fieldStart], fieldSize - 1);
                    pos.enPassant[i] = '\0';
                    fieldStart = i + 1;
                    break;
                case 4:
                    pos.halfMoveClock = strtoul(&str[fieldStart], NULL, 10);
                    fieldStart = i + 1;
                    break;
            }
            currentField += 1;
        }
    }
    if (currentField == 5) pos.fullMoveCount = strtoul(&str[fieldStart], NULL, 10);

    return pos;
}

void PositionFree(Position *pos) {
    free(pos->piecePlacement);
    free(pos->castlingRights);
    free(pos->enPassant);
}
