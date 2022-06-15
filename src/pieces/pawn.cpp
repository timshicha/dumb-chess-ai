#pragma once
#include "pieces.h"


bool Pawn::nextMove() { return false; }

int Pawn::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Pawn::getName() const
{
    return "Pawn  ";
}