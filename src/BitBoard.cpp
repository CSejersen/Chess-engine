#include "BitBoard.h"
#include "bit_manipulation.h"
#include "board_constants.h"
// Bitboards constructor
BitBoard::BitBoard() = default;

// returns the bitboard for the requested Piece
U64 BitBoard::getPieceSet(int pieceType) const {
    return pieceBB[pieceType];
}

// Places Piece on the given square
void BitBoard::placePiece(int pieceType, int square){
    U64 placementMask = 1ULL << square;
    pieceBB[pieceType] |= placementMask;
    if (pieceType < 7) {
        pieceBB[nWhite] |= placementMask;
    }
    else{
        pieceBB[nBlack] |= placementMask;
    }
}

void BitBoard::printBB_helper(const U64& bb, char piece) {
    U64 shiftMe = 1ULL;
    for(int file = 7; file >= 0; file--){
        for(int i = 0; i < 8; i++){
            if((shiftMe << ((file * 8) + i)) & bb){
                std::cout << piece << " ";
            }
            else{
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// prints a nice view of the given bitboard.
void BitBoard::printBB(const U64 &bb) {
    U64 shiftMe = 1ULL;
    for(int file = 7; file >= 0; file--){
        for(int i = 0; i < 8; i++){
            if((shiftMe << ((file * 8) + i)) & bb){
                std::cout << "x ";
            }
            else{
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

// clears entire board
void BitBoard::clearBoard(){
    for(U64& pieceSet : pieceBB){
        pieceSet = 0ULL;
    }
}

// conversion function, example A1 --> 0 or B1 --> 1
int BitBoard::coordinateToIndex(std::string coordinate) {
    int file = 0;
    int rank = 0;
    int squareIndex = 0;

    if(coordinate.size() != 2){
        throw std::invalid_argument("invalid coordinate size");
    }
    else{
        switch (coordinate[0]) {
            case 'a':
                file = 0;
                break;
            case 'b':
                file = 1;
                break;
            case 'c':
                file = 2;
                break;
            case 'd':
                file = 3;
                break;
            case 'e':
                file = 4;
                break;
            case 'f':
                file = 5;
                break;
            case 'g':
                file = 6;
                break;
            case 'h':
                file = 7;
                break;
            default:
                throw std::invalid_argument("invalid coordinate");
        }
    }
    rank = coordinate[1] - 1;
    squareIndex = (rank * 8) + file;
    return squareIndex;
}

// conversion function, example 0 --> a1 or 1 --> b1
std::string BitBoard::indexToCoordinate(int index){
    std::string rank;
    std::string file;
    rank += std::to_string(index/8 + 1);
    switch (index % 8) {
        case 0:
            file = "a";
            break;
        case 1:
            file = "b";
            break;
        case 2:
            file = "c";
            break;
        case 3:
            file = "d";
            break;
        case 4:
            file = "e";
            break;
        case 5:
            file = "f";
            break;
        case 6:
            file = "g";
            break;
        case 7:
            file = "h";
            break;
        default:
            throw std::invalid_argument("error in indexToCoordinate switch case");
    }
    return file+rank;
}

// return a bitboard with all current pieces, black and white.
U64 BitBoard::getAllPieces() const {
    return pieceBB[nWhite] | pieceBB[nBlack];
}

// removes piece from given square
void BitBoard::removePiece(int piece, int square) {
    U64 removalMask = ~(1ULL << square);
    pieceBB[piece] &= removalMask;
    if (piece < 7) {
        pieceBB[nWhite] &= removalMask;
    }
    else{
        pieceBB[nBlack] &= removalMask;
    }
}

U64 BitBoard::generateHash(){
  
  U64 bitboard;
  U64 key = 0ULL;

  for(int piece = nWhitePawn; piece <= nBlackKing; piece++){
    if(piece == nBlack){
      continue;
    }

    bitboard = getPieceSet(piece);

    while(bitboard){
      int sq = getLSB(bitboard);
      clearBit(bitboard, sq);
        key ^= pieceKeys[piece][sq];    
    }
  }
  return key;
}

/* unsigned int get_random_U32_number() */
/* { */
/*     // get current state */
/*     unsigned int number = random_state; */
    
/*     // XOR shift algorithm */
/*     number ^= number << 13; */
/*     number ^= number >> 17; */
/*     number ^= number << 5; */
    
/*     // update random number state */
/*     random_state = number; */
    
/*     // return random number */
/*     return number; */
/* } */

/* // generate 64-bit pseudo legal numbers */
/* U64 get_random_U64_number() */
/* { */
/*     // define 4 random numbers */
/*     U64 n1, n2, n3, n4; */
    
/*     // init random numbers slicing 16 bits from MS1B side */
/*     n1 = (U64)(get_random_U32_number()) & 0xFFFF; */
/*     n2 = (U64)(get_random_U32_number()) & 0xFFFF; */
/*     n3 = (U64)(get_random_U32_number()) & 0xFFFF; */
/*     n4 = (U64)(get_random_U32_number()) & 0xFFFF; */
    
/*     // return random number */
/*     return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48); */
/* } */






