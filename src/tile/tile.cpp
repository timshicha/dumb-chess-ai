#include "tile.h"


void Tile::setTile(Color color)
{
    this->mColor = color;
}

void Tile::setContainedPiece(Piece* containedPiece)
{
    this->mContainedPiece = containedPiece;
}