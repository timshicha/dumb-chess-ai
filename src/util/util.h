#pragma once
#include "../tile/tile.h"

enum class Color { WHITE, BLACK };  //Use "class" to shut up compiler warnings

using tilesPtr = Tile(*)[8][8];  //Pointer to 2d array of tiles
//i.e, ptr tiles ==  Tile(*tiles)[8][8]