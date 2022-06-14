#pragma once
#include "../util/util.h"
#include <memory>

class Piece
{
  public:
    Piece(Color color, int row, int col, tilesPtr tiles);
    virtual ~Piece() = default;

    //Advance to the next permutation
    virtual void nextMove();

    Color getColor() const;

  protected:
    Color mColor;
    //The position indices of the piece
    int mRow, mCol;

    //Reference to the ChessBoards's tiles
    tilesPtr mTiles;
};

class Pawn : public Piece
{
  public:
    Pawn(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Pawn() = default;

    void nextMove() override;
    int getValue() const;

  private:
    int mValue = 1;
};

class Knight : public Piece
{
  public:
    Knight(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Knight() = default;

    void nextMove() override;
    int getValue() const;

  private:
    int mValue = 3;
};

class Bishop : public Piece
{
  public:
    Bishop(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Bishop() = default;

    void nextMove() override;
    int getValue() const;

  private:
    int mValue = 3;
};

class Rook : public Piece
{
  public:
    Rook(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Rook() = default;

    void nextMove() override;
    int getValue() const;

  private:
    int mValue = 5;
};

class Queen : public Piece
{
  public:
    Queen(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Queen() = default;

    void nextMove() override;
    int getValue() const;

  private:
    int mValue = 9;
};

class King : public Piece
{
  public:
    King(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~King() = default;

    void nextMove() override;
};