

// User color
const int WHITE = 0;
const int BLACK = 1;

// Represent pieces on the chessboard with integers
const int USER_KING = 11;
const int USER_QUEEN = 12;
const int USER_ROOK = 13;
const int USER_BISHOP = 14;
const int USER_KNIGHT = 15;
const int USER_PAWN = 16;

const int AI_KING = 21;
const int AI_QUEEN = 22;
const int AI_ROOK = 23;
const int AI_BISHOP = 24;
const int AI_KNIGHT = 25;
const int AI_PAWN = 26;


/* The class holds a chessboard position.

   Functions can be called to determine if there's a checkmate, for the
   AI to return its best move, etc.

   The user starts in the top rows (0 and 1) and the AI starts in the bottom
   rows (6 and 7). (Color not important except for initializing board).
*/
class Chess_AI
{
  public:
    Chess_AI(int user_color); // Generates start-of-game board
    Chess_AI(const int ** chessboard); // Copies position of given chessboard
  private:
    int ** chessboard;
};