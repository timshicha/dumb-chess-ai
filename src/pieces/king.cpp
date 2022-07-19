#pragma once
#include "pieces.h"


std::vector<std::pair<int, int>> King::getLegalMoves() const
{
    // All the possible places the knight can land.
    // Next step is checking which moves are on the board.
    std::vector<std::pair<int, int>> allMovePatterns
    {
        {mRow - 1, mCol    },
        {mRow - 1, mCol + 1},
        {mRow    , mCol + 1},
        {mRow + 1, mCol + 1},
        {mRow + 1, mCol    },
        {mRow + 1, mCol - 1},
        {mRow    , mCol - 1},
        {mRow - 1, mCol - 1}
    };

    std::vector<std::pair<int, int>> legalMoves;

    int newRow = 0;
    int newCol = 0;

    // For each knight move
    for (auto& iMovePattern : allMovePatterns)
    {
        // Store the row and column so we don't have to keep accessing the vector
        // (and for clarity's sake)
        newRow = iMovePattern.first;
        newCol = iMovePattern.second;
        // If the landing is on the board
        if(isInRange(newRow, newCol))
        {
            // Make sure that there is either no piece, or that the piece is opponent's
            Tile* targetTile = &((*mTiles)[newRow][newCol]);
            if(targetTile->getContainedPiece() == nullptr || targetTile->getContainedPiece()->getColor() != mColor)
            {
                legalMoves.push_back(iMovePattern);
            }
        }
    }
    return legalMoves;
}

std::string King::getName() const { return "King  "; }