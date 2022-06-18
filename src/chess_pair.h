#pragma once
#include "util/util.h"

// Forward declarations
class Piece;

class Tile
{
  public:
    Tile() = default;
    ~Tile() = default;

    void setTile(Color color);

    void setContainedPiece(Piece* containedPiece);

    Piece* getContainedPiece();
    
  private:
    Color mColor = Color::WHITE;
    //Reference to piece standing on the tile
    Piece* mContainedPiece = nullptr;
};

//Pointer to 2d array of tiles
using tilesPtr = Tile(*)[8][8];  


class Piece
{
public:
    Piece(int value, Color color, int row, int col, tilesPtr tiles);

    virtual ~Piece() = default;

    //Cycle through possible moves the piece could make
    //Must cycle through all moves
    virtual bool peekNextPossibleMove() = 0;

    //Checks if the provided row and column are on the board
    bool isInRange(int row, int col) const;

    Color getColor() const;
    int getRow() const;
    int getCol() const;
    bool isAlive() const;
    virtual int getValue() const = 0;
    virtual std::vector<std::pair<int, int>> getLegalMoves() const = 0;

    // Get the name of the piece (for display purposes)
    virtual std::string getName() const = 0;

protected:
    //Methods below work together to temporarily move one piece
    void tempKill();
    void undoTempKill();
    //Returns true on successful move and false if provided indices are unavailable
    //Throws exception if moves are attempted in succession
    bool tempMove(int newRow, int newCol);
    //Unmakes a move, does noting if no move was made
    void undoTempMove();
    //Reference the piece that this object killed
    Piece* mTempKilledPiece = nullptr;
    //Remember this object's position when the turn started (before first move)
    //Should only be used by tempMove() and undoTempMove()
    int mAnchorRow = -1;
    int mAnchorCol = -1;
    
    //Indicate to all class objects whether a move has occured
    static bool HAS_MOVED;
    //Notify all class objects about which piece was moved
    static Piece* MOVED_PIECE;
    
    const int mValue;
    Color mColor;  
    int mRow, mCol; //The position indices of the piece
    bool mAlive = true; //(always vaild, even if piece is not alive)

    //Reference to the ChessBoards's tiles
    tilesPtr mTiles;
};
