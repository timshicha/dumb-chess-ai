#pragma once
#include "pieces.h"


void Queen::nextMove() {}


int Queen::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Queen::getName() const
{
    return "Queen ";
}