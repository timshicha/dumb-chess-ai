#pragma once
#include "util/util.h"
#include "chess_pair.h"
#include "pieces/pieces.h"

#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>
#include <tuple>




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

    // Called by user
    bool finalMove(int oldRow, int oldCol, int newRow, int newCol);
    //Called by AI
    void finalMove(std::unordered_map<Piece*, Tile*> boardSnapshot);

  private:
    //64 total tiles on the board
    Tile mTiles[8][8];

    //16 pieces of each color
    std::unique_ptr<Piece> mPieces[2][16]; // Access example: mPieces[int(Color::WHITE)][3]
    //Extra non-owning reference to the kings
    Piece* mKings[2]; // Access example: mKings[int(Color::WHITE)]

    //Cycles through moves within the current board state
    //Cannot be called successively in a single state, move must be undone before next move is done
    //Also, cannot be called if the states stack is empty
    bool tempMove();
    bool undoTempMove();

    //Pushes a state on the stack
    bool rememberState();

    //Pops off a state, doesn't care if there is an ongoing move in the current state
    bool revertState();

    //Pops off all states
    void revertToOriginalState();

    //Remember board states
    //First state is always the actual state of the board
    std::stack<std::unordered_map<Piece*, Tile*>> states;
    //Remember where the last tempMove left off for each state
    //Store the color of the temporarily moved piece, its index, its possible moves and which move is next
    std::stack<std::tuple<Color, int, std::vector<std::pair<int,int>>, int>> stateTempMovesInfo;
};
