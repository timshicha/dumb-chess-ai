#pragma once
#include "pieces.h"

// Returns a vector of coordinates where the knight can move.
// Does not exclude moves where the knight puts own king in check.
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

    int col = 0;
    int row = 0;
    // For each knight move
    for (auto& iMovePattern : allMovePatterns)
    {
        // Store the row and column so we don't have to keep accessing the vector
        // (and for clarity's sake)
        row = iMovePattern.first;
        col = iMovePattern.second;
        // If the landing is on the board
        if(isInRange(row, col))
        {
            // Make sure that there is either no piece, or that the piece is opponent's
            if((*mTiles)[row][col].getContainedPiece() == nullptr || (*mTiles)[row][col].getContainedPiece()->getColor() != mColor)
            {
                legalMoves.push_back(iMovePattern);
            }
        }
    }
    return legalMoves;
}


bool Knight::peekNextPossibleMove() { return false; }


int Knight::getValue() const { return mValue; }

std::string Knight::getName() const { return "Knight"; }