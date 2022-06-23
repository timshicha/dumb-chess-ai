#pragma once
#include "../util/util.h"
#include "../chess_pair.h"

#include <memory>


class Pawn : public Piece
{
  public:
    Pawn(Color color, int row, int col, tilesPtr tiles) : Piece{1, color, row, col, tiles} {}

    virtual ~Pawn() = default;

    // Vector of tiles the pawn is attacking (plus forward).
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Knight : public Piece
{
  public:
    Knight(Color color, int row, int col, tilesPtr tiles) : Piece{3, color, row, col, tiles} {}

    virtual ~Knight() = default;

    // Vector of tiles the knight is attacking.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Bishop : public Piece
{
  public:
    Bishop(Color color, int row, int col, tilesPtr tiles) : Piece{3, color, row, col, tiles} {}

    virtual ~Bishop() = default;

    // Vector of tiles the bishop is attacking.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Rook : public Piece
{
  public:
    Rook(Color color, int row, int col, tilesPtr tiles) : Piece{5, color, row, col, tiles} {}

    virtual ~Rook() = default;

    // Vector of tiles the rook is attacking.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class Queen : public Piece
{
  public:
    Queen(Color color, int row, int col, tilesPtr tiles) : Piece{9, color, row, col, tiles} {}

    virtual ~Queen() = default;

    // Vector of tiles the queen is attacking.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};


class King : public Piece
{
  public:
    King(Color color, int row, int col, tilesPtr tiles) : Piece{0, color, row, col, tiles} {}

    virtual ~King() = default;

    // Vector of tiles the king is attacking.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};

