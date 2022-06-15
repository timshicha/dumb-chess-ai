#pragma once
#include "pieces.h"

//Returns true until a complete cycle of patterns has been complete
bool Bishop::nextMove() 
{
    int startingOrlastTriedRow;
    int startingOrlastTriedCol;

    //If a piece was killed last move, the sequence has changed
    //Undo the last move and then start from the pieces original position
    if (mKilledPiece != nullptr)
    {
        undoMove();
        startingOrlastTriedRow = mRow;
        startingOrlastTriedCol = mCol;
    }
    //Othwewise, undo previous move, but remember where it ended up to continue the sequence
    else
    {
        startingOrlastTriedRow = mRow;
        startingOrlastTriedCol = mCol;
        undoMove(); //Does nothing if this is the first move
    }
    
    //The sequences turn each other on and off in a cycle (clockwise)
    //up-left -> up-right -> down-right -> down-left
    
    //If all of the moves have been done already
    if (completedCycle == true)
        return false;

    //Up-left
    if (mUpLeftSequence == true)
    {
        //Determine next indices according to this method's pattern
        --startingOrlastTriedRow;
        --startingOrlastTriedCol;
        
        //If piece failed to move, switch patterns
        //If piece moved but killed a piece to do so, switch patterns
        if (move(startingOrlastTriedRow, startingOrlastTriedCol) == false || mKilledPiece != nullptr)
        {
            //Move on to next pattern
            mUpLeftSequence = false;
            mUpRightSequence = true;
            //Set up next pattern's starting point (the position at the start of the turn)
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
        }
        //Move on to the next pattern if no move occured
        if (HAS_MOVED == true)
            return true;
    }
    //Up-right
    if (mUpRightSequence == true)
    {
        --startingOrlastTriedRow;
        ++startingOrlastTriedCol;

        if (move(startingOrlastTriedRow, startingOrlastTriedCol) == false || mKilledPiece != nullptr)
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

        if (move(startingOrlastTriedRow, startingOrlastTriedCol) == false || mKilledPiece != nullptr)
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

        if (move(startingOrlastTriedRow, startingOrlastTriedCol) == false || mKilledPiece != nullptr)
        {
            mDownLeftSequence = false;
            mUpLeftSequence = true;
            startingOrlastTriedRow = mRow;
            startingOrlastTriedCol = mCol;
            //This is the last movement pattern, switching sequences means a finished cycle
            completedCycle = true;
        }
        if (HAS_MOVED == true)
            return true;
        //If the move failed, all posible moves have been tried
        else
        {
            completedCycle = false;
            return false;
        }
    }
    //If this point is reach, its a bug
    throw(std::runtime_error{ "Error: Undefined behavior, no move sequence active\n" });
}

int Bishop::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Bishop::getName() const
{
    return "Bishop";
}