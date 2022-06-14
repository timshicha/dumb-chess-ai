#pragma once
#include "pieces.h"


void Rook::nextMove() {}


int Rook::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Rook::getName() const
{
    return "Rook  ";
}