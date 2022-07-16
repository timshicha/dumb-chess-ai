#pragma once
#include "util/util.h"
#include <array>


// Forward declarations
class Piece;

class Tile
{
  public:
    Tile() = default;
    ~Tile() = default;

    void setTile(Color color);

    void setContainedPiece(Piece* containedPiece);

    Piece* getContainedPiece();
    
  private:
    Color mColor = Color::WHITE;
    //Reference to piece standing on the tile
    Piece* mContainedPiece = nullptr;
};

class Piece
{
  public:
    Piece(int value, Color color, int row, int col, std::array<std::array<Tile, 8>,8>* tiles);

    virtual ~Piece() = default;

    //Checks if the provided row and column are on the board
    static bool isInRange(int row, int col);

    Color getColor() const;
    int getRow() const;
    int getCol() const;
    bool isAlive() const;
    virtual int getValue() const = 0;

    // Returns a vector of the squares that the piece can move to (does not check
    // if the move puts own king in check).
    virtual std::vector<std::pair<int, int>> getLegalMoves() const = 0;

    // Get the name of the piece (for display purposes)
    virtual std::string getName() const = 0;
    void kill();
    void undoKill(int row, int col);

    void setPosition(int row, int col);

  protected: 
  
    const int mValue;
    Color mColor;  
    int mRow, mCol; //The position indices of the piece, -1 when the piece is dead
    bool mAlive = true; 

    //Reference to the ChessBoards's tiles, shared by all pieces
    static inline std::array<std::array<Tile, 8>,8>* mTiles = nullptr;
};
