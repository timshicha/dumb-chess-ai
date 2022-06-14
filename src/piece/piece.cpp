#pragma once
#include "piece.h"


Piece::Piece(Color color, int row, int col, tilesPtr tiles) : mColor{color}, mRow{row}, mCol{col}, mTiles{tiles}
{
    (*mTiles)[row][col].setContainedPiece(this);
}


Color Piece::getColor() const
{
    return this->mColor;
}

