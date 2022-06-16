#pragma once
#include "pieces.h"

// Returns a vector of coordinates where the knight can land.
// Does not check if it's a legal move. Only checks if the move is
// out of the board.
std::vector<std::vector<int>> Knight::possibleLandings()
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
    std::vector<std::vector<int>> landingSpots;

    // For each knight move that's on the board, add to the landing spots.
    for (int iMoveType = 0; iMoveType < 8; iMoveType++)
    {
        if(isInRange(possibleMoves[iMoveType][0], possibleMoves[iMoveType][1]))
            landingSpots.push_back(possibleMoves[iMoveType]);
    }
    return landingSpots;
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