#pragma once
#include "pieces.h"


std::vector<std::pair<int, int>> Queen::getLegalMoves() const
{
    std::vector<std::pair<int,int>> legalMoves;

    // ----- ROOK'S MOVES -----
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

    // ----- BISHOP'S MOVES -----

    // Record legal moves up-left (until off the board)
    for (newRow = mRow - 1, newCol = mCol - 1; isInRange(newRow, newCol) == true; --newRow, --newCol)
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

    // Record legal up-right (until off the board)
    for (newRow = mRow - 1, newCol = mCol + 1; isInRange(newRow, newCol) == true; --newRow, ++newCol)
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

    // Record legal moves down-right (until off the board)
    for (newRow = mRow + 1, newCol = mCol + 1; isInRange(newRow, newCol) == true; ++newRow, ++newCol)
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

    // Record legal moves down-left (until off the board)
    for (newRow = mRow + 1, newCol = mCol - 1; isInRange(newRow, newCol) == true; ++newRow, --newCol)
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

bool Queen::peekNextPossibleMove() { return false; }


int Queen::getValue() const { return mValue; }

std::string Queen::getName() const { return "Queen "; }