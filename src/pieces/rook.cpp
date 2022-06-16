#pragma once
#include "pieces.h"


// Returns a vector of coordinates where the rook can move.
// Does not exclude moves where the rook puts own king in check.
std::vector<std::pair<int, int>> Rook::getLegalMoves() const
{
    // Holds the list of coords the Rook can play that are on the board.
    std::vector<std::pair<int, int>> legalMoves;

    int newRow, newCol;

    // Record legal moves up (until off the board)
    newCol = mCol;
    for (newRow = mRow - 1; isInRange(newRow, newCol) == true; ++newRow)
    {
        // If no piece, add move to list
        if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({newRow, newCol});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther up.
        else if((*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({newRow, newCol});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves down (until off the board)
    newCol = mCol;
    for (newRow = mRow + 1; isInRange(newRow, newCol) == true; ++newRow)
    {
        // If no piece, add move to list
        if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({newRow, newCol});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther up.
        else if((*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({newRow, newCol});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves right (until off the board)
    newRow = mRow;
    for (newCol = mCol + 1; isInRange(newRow, newCol) == true; ++newCol)
    {
        // If no piece, add move to list
        if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({newRow, newCol});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther up.
        else if((*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({newRow, newCol});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves left (until off the board)
    newRow = mRow;
    for (newCol = mCol - 1; isInRange(newRow, newCol) == true; --newCol)
   {
        // If no piece, add move to list
        if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({newRow, newCol});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther up.
        else if((*mTiles)[newRow][newCol].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({newRow, newCol});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }
    return legalMoves;
}


bool Rook::peekNextPossibleMove() { return false; }


int Rook::getValue() const { return mValue; }

std::string Rook::getName() const { return "Rook  "; }