#pragma once
#include "pieces.h"


// Returns a vector of coordinates where the rook can move.
// Does not exclude moves where the rook puts own king in check.
std::vector<std::pair<int, int>> Pawn::getLegalMoves() const
{
    std::vector<std::pair<int,int>> legalMoves;

    // If black and last row
    if(mColor == Color::BLACK && mRow == 7)
        return legalMoves;
    // If white and last row
    if(mColor == Color::WHITE && mRow == 0)
        return legalMoves;

    int newRow, newCol;
    
    // Can we move forward?

    // If the pawn is white
    if(mColor == Color::WHITE)
        newRow = mRow - 1;
    // If the pawn is black
    else
        newRow = mRow + 1;
    newCol = mCol;

    // If the new square is empty, it's a legal move
    if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
        legalMoves.push_back({newRow, newCol});

    // Can we capture (forward and to the decreasing columns)?
    // There must be a piece of the opposite color in that square.
    newCol = mCol - 1;
    if((*mTiles)[newRow][newCol].getContainedPiece() != nullptr &&
        (*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        legalMoves.push_back({newRow, newCol});
    
    // Can we capture (forward and to the increasing columns)?
    // There must be a piece of the opposite color in that square.
    newCol = mCol + 1;
    if((*mTiles)[newRow][newCol].getContainedPiece() != nullptr &&
        (*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        legalMoves.push_back({newRow, newCol});

    return legalMoves;
}

bool Pawn::peekNextPossibleMove() { return false; }


int Pawn::getValue() const { return mValue; }

std::string Pawn::getName() const { return "Pawn  "; }