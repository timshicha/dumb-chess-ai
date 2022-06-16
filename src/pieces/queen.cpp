#pragma once
#include "pieces.h"


bool Queen::peekNextPossibleMove() { return false; }


int Queen::getValue() const { return mValue; }

std::string Queen::getName() const { return "Queen "; }