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
    Piece(Color color, int row, int col, tilesPtr tiles);

    virtual ~Piece() = default;

    //Advance to the next permutation
    virtual bool nextMove() = 0;

    //Temporary location for thing, not sure where to put it
    //Checks if the provided row and column are on the board
    bool isInRange(int row, int col);

    Color getColor() const;
    int getRow() const;
    int getCol() const;
    bool isAlive() const;

    // Get the name of the piece (for display purposes)
    virtual std::string getName() const = 0;

protected:
    //Methods below work together to simulate a moving piece
    void kill();
    void unKill();
    //Returns true on successful move and false if provided indices are unavailable
    //Throws exception is moves are attempted in succession
    bool move(int newRow, int newCol);
    //Unmakes a move, does noting if no move was made
    void undoMove();

    //Reference the piece that this object killed
    Piece* mKilledPiece = nullptr;
    //Remember this object's position when the turn started (before first move)
    //Should only be used by move() and unMove()
    int mAnchorRow = -1;
    int mAnchorCol = -1;
    
    //Indicate to all class objects whether a move has occured
    static bool HAS_MOVED;
    //Notify all class objects about which piece was moved
    static Piece* MOVED_PIECE;
    
    int mRow, mCol; //The position indices of the piece
    bool mAlive = true; //(always vaild, even if piece is not alive)
    Color mColor;   

    //Reference to the ChessBoards's tiles
    tilesPtr mTiles;
};
