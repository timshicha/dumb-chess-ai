#pragma once
#include "../util/util.h"
#include "../chess_pair.h"

#include <memory>


class Pawn : public Piece
{
  public:
    Pawn(Color color, int row, int col, tilesPtr tiles) : Piece{1, color, row, col, tiles} {}

    virtual ~Pawn() = default;

    // Returns a vector of coordinates where the knight can move.
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

    // Returns a vector of coordinates where the knight can move.
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

    // Returns a vector of coordinates where the knight can move.
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

    // Returns a vector of coordinates where the knight can move.
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

    // Returns a vector of coordinates where the knight can move.
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

        // Returns a vector of coordinates where the knight can move.
    std::vector<std::pair<int, int>> getLegalMoves() const override;

    bool peekNextPossibleMove() override;
    int getValue() const override;
    std::string getName() const override;
};

