#pragma once
#include "pieces.h"


bool King::nextMove() { return false; }


int King::getValue() const
{
    // King's value is infinite (return max <int> value)
    return std::numeric_limits<int>::max();
}

std::string King::getName() const
{
    return "King  ";
}