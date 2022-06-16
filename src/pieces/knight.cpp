#pragma once
#include "pieces.h"

// Returns a vector of coordinates where the knight can land.
// Does not check if it's a legal move. Only checks if the move is
// out of the board.
std::vector<std::vector<int>> Knight::getLegalMoves()
{
    // All the possible places the knight can land.
    // Next step is checking which moves are on the board.
    std::vector<std::vector<int>> possibleMoves
    {
        {this->mRow - 2, this->mCol + 1},
        {this->mRow - 1, this->mCol + 2},
        {this->mRow + 1, this->mCol + 2},
        {this->mRow + 2, this->mCol + 1},
        {this->mRow + 2, this->mCol - 1},
        {this->mRow + 1, this->mCol - 2},
        {this->mRow - 1, this->mCol - 2},
        {this->mRow - 2, this->mCol - 1}
    };


    // Holds the list of coords the knight can play that are on the board.
    std::vector<std::vector<int>> legalMoves;

    int col = 0;
    int row = 0;
    // For each knight move
    for (int iMoveType = 0; iMoveType < 8; iMoveType++)
    {
        // Store the row and column so we don't have to keep accessing the vector
        // (and for clarity's sake)
        row = possibleMoves[iMoveType][0];
        col = possibleMoves[iMoveType][1];
        // If the landing is on the board
        if(isInRange(row, col))
        {
            // Make sure that there is either no piece, or that the piece is opponent's
            if((*mTiles)[row][col].getContainedPiece() == nullptr || (*mTiles)[row][col].getContainedPiece()->getColor() != this->mColor)
            {
                legalMoves.push_back(possibleMoves[iMoveType]);
            }
        }
    }
    return legalMoves;
}

bool Knight::nextMove() { return false; }


int Knight::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Knight::getName() const
{
    return "Knight";
}