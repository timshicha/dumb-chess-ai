#pragma once
#include "pieces.h"


void Bishop::nextMove() {}


int Bishop::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}