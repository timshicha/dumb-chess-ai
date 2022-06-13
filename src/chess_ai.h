#pragma once
#include "util.h"
#include "tile.h"
#include "piece.h"

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
        mWhitePieces[0].reset(new Rook{ color, row, col, &mTiles });
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



// User color
//const int WHITE = 0;
//const int BLACK = 1;

// Represent pieces on the chessboard with integers
const int USER_KING = 11;
const int USER_QUEEN = 12;
const int USER_ROOK = 13;
const int USER_BISHOP = 14;
const int USER_KNIGHT = 15;
const int USER_PAWN = 16;

const int AI_KING = 21;
const int AI_QUEEN = 22;
const int AI_ROOK = 23;
const int AI_BISHOP = 24;
const int AI_KNIGHT = 25;
const int AI_PAWN = 26;


/* The class holds a chessboard position.

   Functions can be called to determine if there's a checkmate, for the
   AI to return its best move, etc.

   The user starts in the top rows (0 and 1) and the AI starts in the bottom
   rows (6 and 7). (Color not important except for initializing board).
*/
class Chess_AI
{
  public:
    Chess_AI(int user_color); // Generates start-of-game board
    Chess_AI(const int ** chessboard); // Copies position of given chessboard
  private:
    int ** chessboard;
};

