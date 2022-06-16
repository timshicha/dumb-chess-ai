#pragma once
#include "pieces.h"


bool King::peekNextPossibleMove() { return false; }


int King::getValue() const
{
    // King does not have an exchangeable value
    return 0;
}

std::string King::getName() const { return "King  "; }