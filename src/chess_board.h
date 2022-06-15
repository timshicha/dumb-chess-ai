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
    ~ChessBoard() = default;

    // Nice visualization tool for debugging
    std::string get_board_as_string();

    void test();

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //16 pieces of each color
    std::unique_ptr<Piece> mWhitePieces[16];
    std::unique_ptr<Piece> mBlackPieces[16];
};
