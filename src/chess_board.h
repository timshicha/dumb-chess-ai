#pragma once
#include "util/util.h"
#include "chess_pair.h"
#include "pieces/pieces.h"

#include <memory>


class ChessBoard
{
  public:
    // Create starting chess board
    ChessBoard();
    // Create chessboard as specified by textfile (for testing)
    ChessBoard(const char * filename);
    ~ChessBoard() = default;

    // Nice visualization tool for debugging
    std::string get_board_as_string();

    void test();

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //15 pieces of each color, and 2 kings.
    std::unique_ptr<Piece> mPieces[2][15]; // Access example: mPieces[int(Color::WHITE)][3]
    std::unique_ptr<Piece> mKings[2]; // Access example: mKings[int(Color::WHITE)]
};
