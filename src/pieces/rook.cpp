#pragma once
#include "pieces.h"


bool Rook::peekNextPossibleMove() { return false; }


int Rook::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Rook::getName() const
{
    return "Rook  ";
}