#pragma once
#include "pieces.h"


std::vector<std::pair<int, int>> Queen::getLegalMoves() const
{
    // Holds the list of coords the Queen can play that are on the board.
    std::vector<std::pair<int, int>> legalMoves;
    std::vector<std::pair<int, int>> directions = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

    // For each direction
    for (auto& iDirection : directions)
    {
        int newRow, newCol;
        // Keep moving in that direction until can't move any farther
        for (newRow = mRow + iDirection.first, newCol = mCol + iDirection.second;
            isInRange(newRow, newCol) == true; newRow += iDirection.first, newCol += iDirection.second)
        {
            // If no piece, add move to list
            if((*mTiles)[newRow][newCol].getContainedPiece() == nullptr)
            {
                legalMoves.push_back({newRow, newCol});
            }
            // If there is a piece and it belongs to enemy, record it as a legal
            // move and stop moving farther in that direction.
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
    }
    return legalMoves;
}

bool Queen::peekNextPossibleMove() { return false; }


int Queen::getValue() const { return mValue; }

std::string Queen::getName() const { return "Queen "; }