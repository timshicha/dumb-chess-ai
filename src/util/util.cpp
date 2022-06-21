#pragma once
#include "util.h"

// See if a pair exists in a vector of pairs
bool pairInVector(const std::vector<std::pair<int,int>>& pairs, const std::pair<int,int>& target)
{
    int vecSize = pairs.size();

    // Go through each pair
    for ( auto& iPair: pairs )
    {
        // If a match is found
        if(target == iPair)
            return true;
    }
    return false;
}