#pragma once
#include "pieces.h"


std::vector<std::pair<int, int>> Bishop::getLegalMoves() const
{
    // Holds the list of coords the Bishop can play that are on the board.
    std::vector<std::pair<int, int>> legalMoves;
    std::vector<std::pair<int, int>> directions = {{-1,1},{1,1},{1,-1},{-1,-1}};

    // For each direction
    for (auto& iDirection : directions)
    {
        int newRow, newCol;
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

//Returns true until a complete cycle of patterns has been complete
bool Bishop::peekNextPossibleMove() 
{
    int startingOrlastTriedRow;
    int startingOrlastTriedCol;

    //If a piece was killed last move, the sequence has changed
    //Undo the last move and then start from the pieces original position
    if (mTempKilledPiece != nullptr)
    {
        undoTempMove();
        startingOrlastTriedRow = mRow;
        startingOrlastTriedCol = mCol;
    }
    //Othwewise, undo previous move, but remember where it ended up to continue the sequence
    else
    {
        startingOrlastTriedRow = mRow;
        startingOrlastTriedCol = mCol;
        undoTempMove(); //Does nothing if this is the first move
    }
    
    //The sequences turn each other on and off in a cycle (clockwise)
    //up-left -> up-right -> down-right -> down-left
    
    //If all of the moves have been done already
    if (mCompletedCycle == true)
        return false;

    //Up-left
    if (mUpLeftSequence == true)
    {
        //Determine next indices according to this method's pattern
        --startingOrlastTriedRow;
        --startingOrlastTriedCol;
        
        //If piece failed to move, switch patterns
        //If piece moved but killed a piece to do so, switch patterns
        if (tempMove(startingOrlastTriedRow, startingOrlastTriedCol) == false || mTempKilledPiece != nullptr)
        {
            //Move on to next pattern
            mUpLeftSequence = false;
            mUpRightSequence = true;
            //Set up next pattern's starting point (the position at the start of the turn)
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
        }
        //If a move occured, return true
        //Otherwise, switch to the next pattern
        if (HAS_MOVED == true)
            return true;
    }
    //Up-right
    if (mUpRightSequence == true)
    {
        --startingOrlastTriedRow;
        ++startingOrlastTriedCol;

        if (tempMove(startingOrlastTriedRow, startingOrlastTriedCol) == false || mTempKilledPiece != nullptr)
        {
            mUpRightSequence = false;
            mDownRightSequence = true;
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
        }
        if (HAS_MOVED == true)
            return true;
    }
    //down-right
    if (mDownRightSequence == true)
    {
        ++startingOrlastTriedRow;
        ++startingOrlastTriedCol;

        if (tempMove(startingOrlastTriedRow, startingOrlastTriedCol) == false || mTempKilledPiece != nullptr)
        {
            mDownRightSequence = false;
            mDownLeftSequence = true;
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
        }
        if (HAS_MOVED == true)
            return true;
    }
    //down-left
    if (mDownLeftSequence == true)
    {
        ++startingOrlastTriedRow;
        --startingOrlastTriedCol;

        if (tempMove(startingOrlastTriedRow, startingOrlastTriedCol) == false || mTempKilledPiece != nullptr)
        {
            mDownLeftSequence = false;
            mUpLeftSequence = true;
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
            //This is the last movement pattern, switching sequences means a finished cycle
            mCompletedCycle = true;
        }
        if (HAS_MOVED == true)
            return true;
        //If the move failed, all posible moves have been tried
        else
        {
            mCompletedCycle = false;
            return false;
        }
    }
    //If this point is reach, its a bug
    throw(std::runtime_error{ "Error: Undefined behavior, no move sequence active\n" });
}

int Bishop::getValue() const { return mValue; }

std::string Bishop::getName() const { return "Bishop"; }