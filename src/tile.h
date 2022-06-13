#pragma once
#include "util.h"

class Piece;    //Forward declaration

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