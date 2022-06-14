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

        //Add all of the pieces on the board
        /*
              0 1 2 3 4 5 6 7       
            0 W B W B W B W B
            1 B W B W B W B W
            2 W B W B W B W B
            3 B W B W B W B W
            4 W B W B W B W B
            5 B W B W B W B W
            6 W B W B W B W B
            7 B W B W B W B W
        */

        //Use postfix with these
        int whitePieceCount = 0;
        int blackPieceCount = 0;

        //Add kings
        mWhitePieces[whitePieceCount++].reset(new King{Color::WHITE, 0, 3, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new King{Color::BLACK, 7, 3, &mTiles});

        //Add queens
        mWhitePieces[whitePieceCount++].reset(new Queen{Color::WHITE, 0, 4, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Queen{Color::BLACK, 7, 4, &mTiles});

        //Add bishops
        mWhitePieces[whitePieceCount++].reset(new Bishop{Color::WHITE, 0, 2, &mTiles});
        mWhitePieces[whitePieceCount++].reset(new Bishop{Color::WHITE, 0, 5, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Bishop{Color::BLACK, 7, 2, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Bishop{Color::BLACK, 7, 5, &mTiles});

        //Add knights
        mWhitePieces[whitePieceCount++].reset(new Knight{Color::WHITE, 0, 1, &mTiles});
        mWhitePieces[whitePieceCount++].reset(new Knight{Color::WHITE, 0, 6, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Knight{Color::BLACK, 7, 1, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Knight{Color::BLACK, 7, 6, &mTiles});
        
        //Add rooks
        mWhitePieces[whitePieceCount++].reset(new Rook{Color::WHITE, 0, 0, &mTiles});
        mWhitePieces[whitePieceCount++].reset(new Rook{Color::WHITE, 0, 7, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Rook{Color::BLACK, 7, 0, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Rook{Color::BLACK, 7, 7, &mTiles});
        
        //Add pawns
        for(int iCol = 0; iCol < 8; ++iCol)
        {
            mWhitePieces[whitePieceCount++].reset(new Pawn{Color::WHITE, 1, iCol, &mTiles});
            mBlackPieces[blackPieceCount++].reset(new Pawn{Color::BLACK, 6, iCol, &mTiles});        
        }
    }
    ~ChessBoard() = default;

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //16 pieces of each color
    std::unique_ptr<Piece> mWhitePieces[16];
    std::unique_ptr<Piece> mBlackPieces[16];
};
