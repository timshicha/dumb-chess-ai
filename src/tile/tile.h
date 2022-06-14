#pragma once
#include "../util/util.h"

// Forward declarations
class Piece;
class Tile;

using tilesPtr = Tile(*)[8][8];  //Pointer to 2d array of tiles
//i.e, ptr tiles ==  Tile(*tiles)[8][8]

class Tile
{
  public:
    Tile() = default;
    ~Tile() = default;

    void setTile(Color color);
    void setContainedPiece(Piece* containedPiece);
    
  private:
    Color mColor = Color::WHITE;
    //Reference to piece standing on the tile
    Piece* mContainedPiece = nullptr;
};