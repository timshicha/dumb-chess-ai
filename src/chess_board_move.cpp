// This file holds the functionality related to moving pieces
// of the class ChessBoard.

#pragma once
#include "chess_board.h"


// Helper function: move a piece from one tile to another without checking whether it's legal.
// Updates the pieces and the 2-d tile array. Does not care what the landing tile is; it simply overwrites.
// No error checking is done.
void ChessBoard::unsafeMovePiece(int oldRow, int oldCol, int newRow, int newCol)
{
    Tile* oldTile = &(mTiles[oldRow][oldCol]);
    Tile* newTile = &(mTiles[newRow][newCol]);

    // Make the move and update the tiles.
    newTile->setContainedPiece(oldTile->getContainedPiece());
    newTile->getContainedPiece()->setPosition(newRow, newCol);

    // Reset old tile.
    oldTile->setContainedPiece(nullptr);
}


// Move a piece from one location to another. Assumes the move is valid, but still ensures that the
// move did not create a self-check. If a self-check was made, the move is undone and false is returned.
// Also takes a color argument to ensure that a player is not moving another player's pieces.
bool ChessBoard::movePiece(int oldRow, int oldCol, int newRow, int newCol)
{
    Tile oldTile = mTiles[oldRow][oldCol];
    Tile newTile = mTiles[newRow][newCol];

    Piece* movingPiece = oldTile.getContainedPiece();
    Piece* killedPiece = newTile.getContainedPiece();

    // Note: log old details in case we have to undo move.
    // We will have to undo if the move is illegal because it puts the mover's king into check.

    if(killedPiece != nullptr) // If there's a piece, temporarily kill it
        killedPiece->kill();

    // Make the move
    unsafeMovePiece(oldRow, oldCol, newRow, newCol);

    // If the player put themself into check, undo the move sequence and return illegal move
    if(isInCheck(movingPiece->getColor()))
    {
        unsafeMovePiece(newRow, newCol, oldRow, oldCol);
        if(killedPiece != nullptr)
            killedPiece->undoKill();
        newTile.setContainedPiece(killedPiece);
        return false;
    }
    movingPiece->setMoved(true);

    // Otherwise, it's a legal move, so keep the change.
    return true;
}


// This is what the user calls. We will completely check to make sure that the move is legal.
// If the move is not legal, return false.
bool ChessBoard::safeMove(int oldRow, int oldCol, int newRow, int newCol)
{
    // A few checks to make sure the move is legal
    
    // Both tiles need to be in range
    if(Piece::isInRange(oldRow, oldCol) == false || Piece::isInRange(newRow, newCol) == false)
        return false;

    // If trying to move from a tile with no piece
    if(mTiles[oldRow][oldCol].getContainedPiece() == nullptr)
        return false;
    
    // If trying to move to a place where the piece can't move
    if(pairInVector(mTiles[oldRow][oldCol].getContainedPiece()->getLegalMoves(), {newRow, newCol}) == false)
        return false;

    // Otherwise, try moving
    return movePiece(oldRow, oldCol, newRow, newCol);
}

