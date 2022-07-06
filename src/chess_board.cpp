#include "chess_board.h"


ChessBoard::ChessBoard()
{
    //Initialize all of the tiles
    int count = 0;
    for (auto& iRow : mTiles)
    {
        for (auto& iTile : iRow)
        {
            if (count % 2 == 0)
                iTile.setTile(Color::WHITE);
            else
                iTile.setTile(Color::BLACK);
            count++;
        }
    }

    //Add all of the pieces on the board
    /*
          0 1 2 3 4 5 6 7       
        0 W B W B W B W B
        1 B W B W B W B W
        2 W B W B W B W B
        3 B W B W B W B W
        4 W B W B W B W B
        5 B W B W B W B W
        6 W B W B W B W B
        7 B W B W B W B W
    */

    //Use postfix with these
    int whitePieceCount = 0;
    int blackPieceCount = 0;

    //Add kings
    mKings[int(Color::WHITE)].reset(new King{Color::WHITE, 7, 3, &mTiles});
    mKings[int(Color::BLACK)].reset(new King{Color::BLACK, 0, 3, &mTiles});

    //Add queens
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Queen{Color::WHITE, 7, 4, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Queen{Color::BLACK, 0, 4, &mTiles});

    //Add bishops
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Bishop{Color::WHITE, 7, 2, &mTiles});
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Bishop{Color::WHITE, 7, 5, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Bishop{Color::BLACK, 0, 2, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Bishop{Color::BLACK, 0, 5, &mTiles});

    //Add knights
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Knight{Color::WHITE, 7, 1, &mTiles});
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Knight{Color::WHITE, 7, 6, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Knight{Color::BLACK, 0, 1, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Knight{Color::BLACK, 0, 6, &mTiles});
    
    ////Add rooks
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Rook{Color::WHITE, 7, 0, &mTiles});
    mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Rook{Color::WHITE, 7, 7, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Rook{Color::BLACK, 0, 0, &mTiles});
    mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Rook{Color::BLACK, 0, 7, &mTiles});
    
    //Add pawns
    for(int iCol = 0; iCol < 8; ++iCol)
    {
        mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Pawn{Color::WHITE, 6, iCol, &mTiles});
        mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Pawn{Color::BLACK, 1, iCol, &mTiles});        
    }

    mTurnColor = Color::WHITE;

    // nextMove() related things...
    // if piece index is MAX_PIECE_COUNT + 1, we will return null when calling nextMove()
    mCurrentPieceIndex = MAX_PIECE_COUNT + 1;
    mCurrentPieceMoveIndex = 0;
    mCurrentPieceIsKing = false;
}

// Create a chessboard as specified in text file
ChessBoard::ChessBoard(const char* filename, Color turnColor)
{
    std::ifstream file(filename);

    std::string board [8][8];

    // Read from file
    if(file.is_open())
    {
        std::string line;
        int row = 0;
        while (std::getline(file, line))
        {
            int col = 0;
            for (int i = 0; i < line.length(); ++i)
            {
                // If we reached the end (eof)
                if(line[i] == 13) break;
                if(line[i] == ','){++col; continue;}
                board[row][col] += line[i];
            }
            ++row;
        }
    }
    file.close();

    //Initialize all of the tiles
    int count = 0;
    for (auto& iRow : mTiles)
    {
        for (auto& iTile : iRow)
        {
            if (count % 2 == 0)
                iTile.setTile(Color::WHITE);
            else
                iTile.setTile(Color::BLACK);
            ++count;
        }
    }

    //Add all of the pieces on the board
    /*
          0 1 2 3 4 5 6 7       
        0 W B W B W B W B
        1 B W B W B W B W
        2 W B W B W B W B
        3 B W B W B W B W
        4 W B W B W B W B
        5 B W B W B W B W
        6 W B W B W B W B
        7 B W B W B W B W
    */

   int whitePieceCount = 0;
   int blackPieceCount = 0;

    // Add all the pieces
    for(int iBoardRow = 0; iBoardRow < 8; ++iBoardRow)
    {
        for(int iBoardCol = 0; iBoardCol < 8; ++iBoardCol)
        {
            std::string word = board[iBoardRow][iBoardCol];

            if(word == "wKing")
                mKings[int(Color::WHITE)].reset(new King{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wQueen")
                mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Queen{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wRook")
                mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Rook{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wBishop")
                mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Bishop{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wKnight")
                mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Knight{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wPawn")
                mPieces[int(Color::WHITE)][whitePieceCount++].reset(new Pawn{Color::WHITE, iBoardRow, iBoardCol, &mTiles});

            if(word == "bKing")
                mKings[int(Color::BLACK)].reset(new King{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bQueen")
                mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Queen{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bRook")
                mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Rook{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bBishop")
                mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Bishop{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bKnight")
                mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Knight{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bPawn")
                mPieces[int(Color::BLACK)][blackPieceCount++].reset(new Pawn{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
        }
    }

    // Fill in the rest with blanks
    for (int i = whitePieceCount; i < MAX_PIECE_COUNT; ++i)
        mPieces[int(Color::WHITE)][i].reset(nullptr);

    for (int i = blackPieceCount; i < MAX_PIECE_COUNT; ++i)
        mPieces[int(Color::BLACK)][i].reset(nullptr);

    mTurnColor = turnColor;

    // nextMove() related things...
    // if piece index is MAX_PIECE_COUNT + 1, we will return null when calling nextMove()
    mCurrentPieceIndex = MAX_PIECE_COUNT + 1;
    mCurrentPieceMoveIndex = 0;
    mCurrentPieceIsKing = false;
}


// Converts the chess board into a nicely formatted string.
// The string can be displayed for a nice looking chess board visual.
std::string ChessBoard::get_board_as_string()
{
    using namespace std;

    // Display top labels
    string result = "   ";
    for (int i = 0; i < 8; ++i) // Each column gets a number
        result += "   |  " + to_string(i);
    result += "\n";

    // For nice format
    for (int i = 0; i < 8; ++i)
        result += "      |";
    result += "\n------+------+------+------+------+------+------+------+------\n";

    // Display each row
    for (int i = 0; i < 8; ++i)
    {
        // Left-most column just holds the row number
        result += "  " + to_string(i) + "   |";

        // For each column, see if there's a piece. If so, display color.
        // This is the top row of each tile
        for (int j = 0; j < 8; ++j)
        {
            // If there's a piece
            if(mTiles[i][j].getContainedPiece() != nullptr)
            {
                // Determine the color to display
                if(mTiles[i][j].getContainedPiece()->getColor() == Color::WHITE)
                    result += "White ";
                else
                    result += "Black ";
            }
            else
                result += "      ";
            if(j < 7)
                result += '|';
        }

        // Left-most column holds nothing
        result += "\n      |";
        // For each column, see if there's a piece. If so, display piece type.
        // This is the bottom row of each tile
        for (int j = 0; j < 8; ++j)
        {
            // If there's a piece, display the piece
            if(mTiles[i][j].getContainedPiece() != nullptr)
                result += mTiles[i][j].getContainedPiece()->getName();
            else
                result += "      ";
            if(j < 7)
                result += '|';
        }
        result += '\n';
        if(i < 7)
        {
                result += "------+------+------+------+------+------+------+------+------\n";
        }
    }
    // Return the table as a string
    return result;
}

void ChessBoard::test()
{
    for (int i = 0; i < 8; ++i)
    {
        Piece* temp = mPieces[int(Color::BLACK)][i].get();
        while (temp->peekNextPossibleMove() == true) 
        {
            std::cout << this->get_board_as_string() << "\n\n";
        }
    }
    
}

bool ChessBoard::isInCheck(Color kingColor) const
{
    // Get the king's position
    std::pair<int,int> kingPosition = {mKings[int(kingColor)]->getRow(), mKings[int(kingColor)]->getCol()};

    // May be more efficient to use an int instead of type-casting every time,
    // but for clarity, we will leave that decision until later.
    Color enemyColor;
    if(kingColor == Color::WHITE)
        enemyColor = Color::BLACK;
    else
        enemyColor = Color::WHITE;

    // Iterate through each enemy piece and see if it attacks the king
    for (int i = 0; i < MAX_PIECE_COUNT; ++i)
    {
        Piece* currentPiece = mPieces[int(enemyColor)][i].get();

        // If the piece is alive, it's a potential attacker
        if(currentPiece != nullptr && currentPiece->isAlive())
        {
            // If the piece attacks the king, the king is in check
            if(pairInVector(currentPiece->getLegalMoves(), kingPosition))
                return true;
        }
    }
    // If none of the pieces attack the king, he is not in check
    return false;
}

// Enable the nextMove() function. This function sets things up to allow nextMove() to work for
// the chessboard from the current chessboard position.
void ChessBoard::startMoveSequence(Color color)
{
    mCurrentPieceMoveIndex = 0;
    mCurrentPieceIsKing = false;
    
    // Keep searching for the first piece with a legal move. When one is found, stop searching.
    for (mCurrentPieceIndex = 0; mCurrentPieceIndex < MAX_PIECE_COUNT; ++mCurrentPieceIndex)
    {
        // Get legal moves for this piece
        mCurrentPieceLegalMoves = mPieces[int(color)][mCurrentPieceIndex]->getLegalMoves();

        // If there's at least one legal move, this is the piece we're starting with.
        // We don't need to do anything else.
        if(mCurrentPieceLegalMoves.size() > 0)
            return;
    }

    // If no piece had legal moves, see if a king has legal moves.
    mCurrentPieceLegalMoves = mKings[int(color)]->getLegalMoves();

    // If the king has moves
    if(mCurrentPieceLegalMoves.size() > 0)
    {
        mCurrentPieceIsKing = true;
    }
}