#pragma once
#include "util/util.h"
#include "tile/tile.h"
#include "piece/piece.h"

#include <memory>


class ChessBoard
{
  public:
    ChessBoard()
    {
        //Initlize all of the tiles
        int count = 0;
        for (auto iRow : mTiles)
        {
            for (auto iTile : mTiles[0])
            {
                if (count % 2 == 0)
                    iTile.setTile(Color::WHITE);
                else
                    iTile.setTile(Color::BLACK);
            }
        }

        Color color = Color::WHITE;
        int row = 0;
        int col = 0;

        //Add all of the pieces on the board
        mWhitePieces[0].reset(new Rook{color, row, col, &mTiles});
        //... lotta pieces to add manually
        //Could read out of a file or something
    }
    ~ChessBoard() = default;

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //16 pieces of each color
    std::unique_ptr<Piece> mWhitePieces[16];
    std::unique_ptr<Piece> mBlackPieces[16];
};
