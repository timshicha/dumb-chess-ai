#include "chess_pair.h"

//Init Piece's static
tilesPtr Piece::mTiles = nullptr;

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


//Initialize Piece's statics
Piece* Piece::MOVED_PIECE = nullptr;
bool Piece::HAS_MOVED = false;


Piece::Piece(int value, Color color, int row, int col, tilesPtr tiles) : mValue{value}, mColor { color }, mRow{ row }, mCol{ col }
{
    //If the already set ptr isn't equal to the passed in one, throw an error
    if (mTiles != nullptr && mTiles != tiles)
        throw(std::runtime_error{ "Error: Attempted to create a piece on non-existent or different chess tiles\n" });

    mTiles = tiles;

    //Notify the tile of this piece
    (*mTiles)[mRow][mCol].setContainedPiece(this);
}

void Piece::kill()
{
    mAlive = false;
    // Remove piece from its tile
    (*mTiles)[mRow][mCol].setContainedPiece(nullptr);
}

void Piece::undoKill()
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

void Piece::setPosition(int row, int col)
{
    mRow = row;
    mCol = col;
}

void Piece::setMoved(bool moved)
{
    this->moved = moved;
}

//Returns true on successful move and false if provided indices are unavailable 
bool Piece::tempMove(int newRow, int newCol)
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
            //Remember the piece that is being killed (by this piece)
            mTempKilledPiece = currentOccupier;
            //Kill the piece
            mTempKilledPiece->kill();
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


void Piece::undoTempMove()
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

    //If a piece was killed during this objects previous move, unkill it
    if (mTempKilledPiece != nullptr)
    {
        mTempKilledPiece->undoKill();
        mTempKilledPiece = nullptr;
    }

    //Indicate (to all pieces) that a move has been undone
    HAS_MOVED = false;
    MOVED_PIECE = nullptr;
}


Color Piece::getColor() const { return mColor; }


int Piece::getRow() const { return mRow; }


int Piece::getCol() const { return mCol; }


bool Piece::isAlive() const { return mAlive; }

