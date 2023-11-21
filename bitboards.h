#pragma once
#include "move.h"
#include "board_constants.h"
#include "game_state.h"
#include <string>
#include <iostream>
#include "bit_manipulation.h"

class BitBoard{
public:
    explicit BitBoard(GameState*);
    GameState* _state;
    void makeMove(const Move&);
    void undoMove();
    void placePiece(int piece, int square);
    U64 getPieceSet(enumPieceBB) const;
    void clearBoard();

    // Board indexing util functions
    int coordinateToIndex(std::string coordinate);
    std::string indexToCoordinate(int);

    // debug functions
    static void printBB(const U64& bb) ;

private:
    // bitboards containing current position
    U64 pieceBB[14];
};
