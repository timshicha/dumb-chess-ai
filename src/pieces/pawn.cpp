#pragma once
#include "pieces.h"


bool Pawn::peekNextPossibleMove() { return false; }


int Pawn::getValue() const { return mValue; }

std::string Pawn::getName() const { return "Pawn  "; }