#pragma once
#include "pieces.h"


// Returns a vector of coordinates where the rook can move.
// Does not exclude moves where the rook puts own king in check.
std::vector<std::vector<int>> Rook::getLegalMoves()
{
    // Holds the list of coords the knight can play that are on the board.
    std::vector<std::vector<int>> legalMoves;

    int row, col;

    // Record legal moves up (until off the board)
    col = mCol;
    for (row = mRow - 1; row >= 0; row--)
    {
        // If no piece, add move to list
        if((*mTiles)[row][col].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({row, col});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther up.
        else if((*mTiles)[row][col].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({row, col});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves down (until off the board)
    col = mCol;
    for (row = mRow + 1; row < 8; row++)
    {
        // If no piece, add move to list
        if((*mTiles)[row][col].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({row, col});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther down.
        else if((*mTiles)[row][col].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({row, col});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves right (until off the board)
    row = mRow;
    for (col = mCol + 1; col < 8; col++)
    {
        // If no piece, add move to list
        if((*mTiles)[row][col].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({row, col});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther right.
        else if((*mTiles)[row][col].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({row, col});
            break;
        }
        // Otherwise it's our own piece. Stop moving.
        else
        {
            break;
        }
    }

    // Record legal moves left (until off the board)
    row = mRow;
    for (col = mCol - 1; col >= 0; col--)
    {
        // If no piece, add move to list
        if((*mTiles)[row][col].getContainedPiece() == nullptr)
        {
            legalMoves.push_back({row, col});
        }
        // If there is a piece and it belongs to enemy, record it as a legal
        // move and stop moving farther left.
        else if((*mTiles)[row][col].getContainedPiece()->getColor() != mColor)
        {
            legalMoves.push_back({row, col});
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

bool Rook::nextMove() { return false; }


int Rook::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Rook::getName() const
{
    return "Rook  ";
}