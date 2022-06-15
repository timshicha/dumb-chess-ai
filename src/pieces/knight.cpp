#pragma once
#include "pieces.h"


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