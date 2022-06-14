#pragma once
#include "piece.h"


int King::getValue() const
{
    // King's value is infinite (return max <int> value)
    return std::numeric_limits<int>::max();
}