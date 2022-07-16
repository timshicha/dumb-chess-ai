#pragma once
#include "util/util.h"
#include "chess_pair.h"
#include "pieces/pieces.h"

#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>
#include <array>


class ChessBoard
{
  public:
    // Create starting chess board
    ChessBoard();
    // Create chessboard as specified by textfile (for testing).
    ChessBoard(const char * filename,  Color turnColor);
    ~ChessBoard() = default;

    //Returns an array of pieces of the specified color
     const std::array<Piece, 16>& operator[](Color);

    // Nice visualization tool for debugging
    std::string get_board_as_string();

    void test();
    bool isInCheck(Color kingColor) const;

    //Can only be used when the states stack is empty
    bool finalMove(int oldRow, int oldCol, int newRow, int newCol);

    //Pushes on the stack and make a move
    bool tempMove(int oldRow, int oldCol, int newRow, int newCol);

    //Pops off the stack and restore the board
    bool undoTempMove();

    //Returns how many states are on the stack
    int countTempMoves() const;

    //Throws error if the wrong color is passed in
    std::vector<std::pair<int,int>> getLegalMoves(Color pieceColor, int pieceIndex) const;
  
  private:
    //Flip the color of the ongoing turn
    void switchTurnColor();
  
  private:
    //64 total tiles on the board
    std::array<std::array<Tile, 8>,8> mTiles;

    //16 pieces of each color
    std::array<std::array<std::unique_ptr<Piece>, 16>,2> mPieces; // Access example: mPieces[int(Color::WHITE)][3]

    //Extra non-owning reference to the kings
    Piece* mKings[2]; // Access example: mKings[int(Color::WHITE)]
    
    //Keeps track of the color, affected by temp and final moves
    Color mTurnColor = Color::WHITE;
    
    //Remember board states
    //First state is always the actual state of the board
    std::stack<std::unordered_map<Piece*, std::pair<int,int>>> mStates;
};
