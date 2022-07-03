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
    bool isInCheck(Color kingColor) const;

    // This is what the user calls. We will completely check to make sure that the move is legal.
    // If the move is not legal, returns false.
    bool safeMove(int oldRow, int oldCol, int newRow, int newCol);

    // Enable the nextMove() function. This function sets things up to allow nextMove() to work for
    // the chessboard from the current chessboard position.
    // Takes the color of the player whose moves to evaluate.
    void startMoveSequence(Color color);

    

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //15 pieces of each color, and 2 kings.
    std::unique_ptr<Piece> mPieces[2][MAX_PIECE_COUNT]; // Access example: mPieces[int(Color::WHITE)][3]
    std::unique_ptr<Piece> mKings[2]; // Access example: mKings[int(Color::WHITE)]


    // Move a piece from one location to another. Assumes the move is valid, but still ensures that the
    // move did not create a self-check. If a self-check was made, the move is undone and false is returned.
    // Also takes a color argument to ensure that a player is not moving another player's pieces.
    bool movePiece(int oldRow, int oldCol, int newRow, int newCol);
    
    // Helper function: move a piece from one tile to another without checking whether it's legal.
    // Updates the pieces and the 2-d tile array. Does not care what the landing tile is; it simply overwrites.
    void unsafeMovePiece(int oldRow, int oldCol, int newRow, int newCol);

    // Related to temp moving and nextMove:
    int currentPieceIndex; // Which piece we are currently on
    bool currentPieceIsKing; // Is the current piece to evaluate the king?
    std::vector<std::pair<int,int>> currentPieceLegalMoves; // Moves the current piece can move to
    int currentPieceMoveIndex; // Which move the current piece we are evaluating is at
};
