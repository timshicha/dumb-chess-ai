#pragma once
#include "pieces.h"


void Pawn::nextMove(){}


int Pawn::getValue() const
{
    // May do some calculations to get an adjusted piece value
    return mValue;
}

std::string Pawn::getName() const
{
    return "Pawn  ";
}