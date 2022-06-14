#pragma once
#include "util/util.h"


// Forward declarations
class Piece;

class Tile
{
  public:
    Tile() = default;
    ~Tile() = default;

    void setTile(Color color)
    {
        this->mColor = color;
    }

    void setContainedPiece(Piece* containedPiece)
    {
        this->mContainedPiece = containedPiece;
    }

    Piece* getContainedPiece()
    {
        return this->mContainedPiece;
    }
    
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
    Piece(Color color, int row, int col, tilesPtr tiles) : mColor{ color }, mRow{ row }, mCol{ col }, mTiles{ tiles }{}

    virtual ~Piece() = default;

    //Advance to the next permutation
    virtual void nextMove() = 0;

    Color getColor() const
    {
        return this->mColor;
    }

    bool isAlive()
    {
        return this->mAlive;
    }

    int getRow()
    {
        return this->mRow;
    }

    int getCol()
    {
        return this->mCol;
    }

    // Get the name of the piece (for display purposes)
    virtual std::string getName() const = 0;


protected:
    Color mColor;
    //The position indices of the piece
    int mRow, mCol;
    bool mAlive = true;

    //Reference to the ChessBoards's tiles
    tilesPtr mTiles;
};