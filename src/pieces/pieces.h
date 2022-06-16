#pragma once
#include "../util/util.h"
#include "../chess_pair.h"

#include <memory>
#include <limits>

class Pawn : public Piece
{
  public:
    Pawn(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Pawn() = default;

    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;

  private:
    int mValue = 1;
};


class Knight : public Piece
{
  public:
    Knight(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Knight() = default;

    // Returns a vector of coordinates where the knight can move.
    std::vector<std::vector<int>> getLegalMoves();
    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;

  private:
    int mValue = 3;
};


class Bishop : public Piece
{
  public:
    Bishop(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Bishop() = default;

    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;

  private:
    int mValue = 3;
    //Movement patterns
    bool mUpLeftSequence = true;
    bool mUpRightSequence = false;
    bool mDownRightSequence = false;
    bool mDownLeftSequence = false;
    //Indicates whether all moves have been tried
    bool mCompletedCycle = false;
};


class Rook : public Piece
{
  public:
    Rook(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Rook() = default;

    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;
    // Returns a vector of coordinates where the rook can move.
    std::vector<std::vector<int>> getLegalMoves();

  private:
    int mValue = 5;
};


class Queen : public Piece
{
  public:
    Queen(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~Queen() = default;

    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;

  private:
    int mValue = 9;
};


class King : public Piece
{
  public:
    King(Color color, int row, int col, tilesPtr tiles) : Piece{color, row, col, tiles} {}

    virtual ~King() = default;

    bool peekNextPossibleMove() override;
    int getValue() const;
    std::string getName() const override;
};

