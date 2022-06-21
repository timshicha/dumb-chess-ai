#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


#define MAX_PIECE_COUNT 15   // Max number of pieces per side (excluding king)
enum class Color {WHITE, BLACK};  //Use "class" to shut up compiler warnings

// See if a pair exists in a vector of pairs
bool pairInVector(const std::vector<std::pair<int,int>>& pairs, const std::pair<int,int>& target);
