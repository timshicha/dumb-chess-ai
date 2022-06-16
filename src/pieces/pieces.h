#pragma once
#include "../util/util.h"
#include "../chess_pair.h"

#include <memory>


class Pawn : public Piece
{
  public:
    Pawn(Color color, int row, int col, tilesPtr tiles) : Piece{1, color, row, col, tiles} {}

    virtual ~Pawn() = default;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Knight : public Piece
{
  public:
    Knight(Color color, int row, int col, tilesPtr tiles) : Piece{3, color, row, col, tiles} {}

    virtual ~Knight() = default;

    // Returns a vector of coordinates where the knight can move.
    std::vector<std::pair<int, int>> getLegalMoves() const;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Bishop : public Piece
{
  public:
    Bishop(Color color, int row, int col, tilesPtr tiles) : Piece{3, color, row, col, tiles} {}

    virtual ~Bishop() = default;

    // Returns a vector of coordinates where the knight can move.
    std::vector<std::pair<int, int>> getLegalMoves() const;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;

  private:
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
    Rook(Color color, int row, int col, tilesPtr tiles) : Piece{5, color, row, col, tiles} {}

    virtual ~Rook() = default;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
    // Returns a vector of coordinates where the rook can move.
    std::vector<std::pair<int, int>> getLegalMoves() const;
};


class Queen : public Piece
{
  public:
    Queen(Color color, int row, int col, tilesPtr tiles) : Piece{9, color, row, col, tiles} {}

    virtual ~Queen() = default;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class King : public Piece
{
  public:
    King(Color color, int row, int col, tilesPtr tiles) : Piece{0, color, row, col, tiles} {}

    virtual ~King() = default;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};

