#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>


enum class Color {WHITE, BLACK};  //Use "class" to shut up compiler warnings

// See if a pair exists in a vector of pairs
bool pairInVector(std::vector<std::pair<int,int>> pairs, std::pair<int,int> target);