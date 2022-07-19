#pragma once
#include "pieces.h"

// Gets all the tiles that the knight is attacking.
// Note that a knight may be attacking a tile even if it can't capture it, i.e.,
// moving the knight will put own king into check.
std::vector<std::pair<int, int>> Knight::getLegalMoves() const
{
    // All the possible places the knight can land.
    // Next step is checking which moves are on the board.
    std::vector<std::pair<int, int>> allMovePatterns
    {
        {mRow - 2, mCol + 1},
        {mRow - 1, mCol + 2},
        {mRow + 1, mCol + 2},
        {mRow + 2, mCol + 1},
        {mRow + 2, mCol - 1},
        {mRow + 1, mCol - 2},
        {mRow - 1, mCol - 2},
        {mRow - 2, mCol - 1}
    };


    // Holds the list of coords the knight can play that are on the board.
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

std::string Knight::getName() const { return "Knight"; }