#include "chess_pair.h"


void Tile::setTile(Color color)
{
    mColor = color;
}


void Tile::setContainedPiece(Piece* containedPiece)
{
    mContainedPiece = containedPiece;
}


Piece* Tile::getContainedPiece()
{
    return mContainedPiece;
}


//Initialize Piece's statics
Piece* Piece::MOVED_PIECE = nullptr;
bool Piece::HAS_MOVED = false;


Piece::Piece(Color color, int row, int col, tilesPtr tiles) : mColor{ color }, mRow{ row }, mCol{ col }, mTiles{ tiles }
{
    //Notify the tile of this piece
    (*mTiles)[mRow][mCol].setContainedPiece(this);
}


void Piece::kill()
{
    mAlive = false;
    //Remove piece from its tile
    (*mTiles)[mRow][mCol].setContainedPiece(nullptr);
}


void Piece::unKill()
{
    mAlive = true;
    //Place the piece back on its tile
    (*mTiles)[mRow][mCol].setContainedPiece(this);
}


bool Piece::isInRange(int row, int col)
{
    if (row > 7 || row < 0 || col > 7 || col < 0)
        return false;
    else
        return true;
}


//Returns true on successful move and false if provided indices are unavailable 
bool Piece::move(int newRow, int newCol)
{
    //If a piece has been moved already, throw error
    //Only 1 move can occur at a time
    if (HAS_MOVED == true)
        throw(std::runtime_error{ "Error: Attempted to move consecutively\n" });
    //Return false if the indices are out of bounds
    if (isInRange(newRow, newCol) == false)
        return false;

    Tile* currentTile = &((*mTiles)[mRow][mCol]);
    Tile* targetTile = &((*mTiles)[newRow][newCol]);

    //If the target tile is already occupied
    Piece* currentOccupier = targetTile->getContainedPiece();
    if (currentOccupier != nullptr)
    {
        //Different colored piece
        if (currentOccupier->getColor() != mColor)
        {
            //Remember the piece that is being killed
            mKilledPiece = currentOccupier;
            //Kill that piece
            mKilledPiece->kill();
        }
        //Same colored piece, unable to move there
        else
            return false;
    }

    //Record current position
    mAnchorRow = mRow;
    mAnchorCol = mCol;
    //Update indices to new position
    mRow = newRow;
    mCol = newCol;
    //Disconnect from current tile
    currentTile->setContainedPiece(nullptr);
    //Connect to new tile
    targetTile->setContainedPiece(this);

    //Indicate that a piece moved
    HAS_MOVED = true;
    //Indicate which piece moved
    MOVED_PIECE = this;

    return true;
}


void Piece::undoMove()
{
    //Make sure that there is a move to undo
    if (HAS_MOVED == false)
        return;
    //Make sure that that the same piece that moved is undoing the move
    if (MOVED_PIECE != this)
        throw(std::runtime_error{ "Error: Attempted to move back wrong piece\n" });

    Tile* currentTile = &((*mTiles)[mRow][mCol]);
    Tile* targetTile = &((*mTiles)[mAnchorRow][mAnchorCol]);

    //Disconnect from current tile
    currentTile->setContainedPiece(nullptr);

    //Connect back to the tile the piece occupied at the start of the turn
    targetTile->setContainedPiece(this);

    //Restore the piece's indices to what they were when the turn started
    mRow = mAnchorRow;
    mCol = mAnchorCol;

    //If a piece was killed during the previous move, unkill it
    if (mKilledPiece != nullptr)
    {
        mKilledPiece->unKill();
        mKilledPiece = nullptr;
    }

    //Indicate that a move has been undone
    HAS_MOVED = false;
    MOVED_PIECE = nullptr;
}


Color Piece::getColor() const { return this->mColor; }


int Piece::getRow() const { return this->mRow; }


int Piece::getCol() const { return this->mCol; }


bool Piece::isAlive() const { return this->mAlive; }

