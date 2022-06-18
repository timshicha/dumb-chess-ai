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
    
    // ----- Can we capture to either side? -----

    // Increase/decrease row depending on color.
    if(mColor == Color::WHITE)
        newRow = mRow - 1;
    if(mColor == Color::BLACK)
        newRow = mRow + 1;

    newCol = mCol - 1; // Try capturing to the left
    Tile focusedTile = (*mTiles)[newRow][newCol];
    // If it's an opponent's piece, we can capture
    if(focusedTile.getContainedPiece() != nullptr && focusedTile.getContainedPiece()->getColor() != mColor)
        legalMoves.push_back({newRow, newCol});

    newCol = mCol + 1; // Try capturing to the right
    focusedTile = (*mTiles)[newRow][newCol];
    // If it's an opponent's piece, we can capture
    if(focusedTile.getContainedPiece() != nullptr && focusedTile.getContainedPiece()->getColor() != mColor)
        legalMoves.push_back({newRow, newCol});

    // ----- Can we move forward? -----

    newCol = mCol;
    // If the new square is empty, it's a legal move
    if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
    {
        legalMoves.push_back({newRow, newCol});

        // If that was a legal move, see if we can move twice.
        // We can move twice if the pawn is at its starting position
        // and both tiles in front of it are free.
        if(mColor == Color::WHITE && mRow == 6) // If white and in original row
        {
            newRow = mRow - 2; //Move twice
            if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr) // If still empty, we can move
                legalMoves.push_back({newRow, newCol});
        }
        else if(mColor == Color::BLACK && mCol == 1) // If black and in original row
        {
            newRow = mRow + 2;
            if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr) // If still empty, we can move
                legalMoves.push_back({newRow, newCol});
        }
    }
    return legalMoves;
}

bool Pawn::peekNextPossibleMove() { return false; }


int Pawn::getValue() const { return mValue; }

std::string Pawn::getName() const { return "Pawn  "; }