#include "chess_pair.h"


void Tile::setTile(Color color)
{
    mColor = color;
}


void Tile::setContainedPiece(Piece* containedPiece)
{
    //If placing a new piece, make sure that the tile is empty
    if (containedPiece != nullptr && mContainedPiece != nullptr)
        throw(std::runtime_error{ "Error: Attempted to place piece on an occupied tile\n" });

    //Place the peice on the tile
    mContainedPiece = containedPiece;
}


Piece* Tile::getContainedPiece(){return mContainedPiece;}


Piece::Piece(int value, Color color, int row, int col, std::array<std::array<Tile, 8>,8>* tiles) : mValue{value}, mColor { color }, mRow{ row }, mCol{ col }
{
    //If the already set ptr isn't equal to the passed in one, throw an error
    if (mTiles != nullptr && mTiles != tiles)
        throw(std::runtime_error{ "Error: Attempted to create a piece on non-existent or different chess tiles\n" });

    mTiles = tiles;
}

void Piece::kill()
{
    mAlive = false;
    mRow = -1;
    mCol = -1;
}

void Piece::undoKill(int row, int col)
{
    mAlive = true;
    mRow = row;
    mCol = col;
}

bool Piece::isInRange(int row, int col)
{
    if (row > 7 || row < 0 || col > 7 || col < 0)
        return false;
    else
        return true;
}

void Piece::setPosition(int row, int col)
{
    mRow = row;
    mCol = col;
}

Color Piece::getColor() const { return mColor; }


int Piece::getRow() const 
{ 
    throw(std::runtime_error{ "Error: Attempted to get the position of killed piece\n" });
    return mRow; 
}


int Piece::getCol() const
{ 
    throw(std::runtime_error{ "Error: Attempted to get the position of killed piece\n" });
    return mCol; 
}


bool Piece::isAlive() const { return mAlive; }

