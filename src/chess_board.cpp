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
    mWhiteKing = new King{Color::WHITE, 0, 3, &mTiles};
    mBlackKing = new King{Color::BLACK, 7, 3, &mTiles};

    //Add queens
    mWhitePieces[whitePieceCount++].reset(new Queen{Color::WHITE, 0, 4, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Queen{Color::BLACK, 7, 4, &mTiles});

    //Add bishops
    mWhitePieces[whitePieceCount++].reset(new Bishop{Color::WHITE, 0, 2, &mTiles});
    mWhitePieces[whitePieceCount++].reset(new Bishop{Color::WHITE, 0, 5, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Bishop{Color::BLACK, 7, 2, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Bishop{Color::BLACK, 7, 5, &mTiles});

    //Add knights
    mWhitePieces[whitePieceCount++].reset(new Knight{Color::WHITE, 0, 1, &mTiles});
    mWhitePieces[whitePieceCount++].reset(new Knight{Color::WHITE, 0, 6, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Knight{Color::BLACK, 7, 1, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Knight{Color::BLACK, 7, 6, &mTiles});
    
    ////Add rooks
    mWhitePieces[whitePieceCount++].reset(new Rook{Color::WHITE, 0, 0, &mTiles});
    mWhitePieces[whitePieceCount++].reset(new Rook{Color::WHITE, 0, 7, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Rook{Color::BLACK, 7, 0, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new Rook{Color::BLACK, 7, 7, &mTiles});
    
    /*Don't add pawns to test bishop moves*/
    //Add pawns
   /* for(int iCol = 0; iCol < 8; ++iCol)
    {
        mWhitePieces[whitePieceCount++].reset(new Pawn{Color::WHITE, 1, iCol, &mTiles});
        mBlackPieces[blackPieceCount++].reset(new Pawn{Color::BLACK, 6, iCol, &mTiles});        
    }*/
}

// Create a chessboard as specified in text file
ChessBoard::ChessBoard(const char* filename)
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
                mWhiteKing = new King{Color::WHITE, iBoardRow, iBoardCol, &mTiles};
            if(word == "wQueen")
                mWhitePieces[whitePieceCount++].reset(new Queen{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wRook")
                mWhitePieces[whitePieceCount++].reset(new Rook{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wBishop")
                mWhitePieces[whitePieceCount++].reset(new Bishop{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wKnight")
                mWhitePieces[whitePieceCount++].reset(new Knight{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
            if(word == "wPawn")
                mWhitePieces[whitePieceCount++].reset(new Pawn{Color::WHITE, iBoardRow, iBoardCol, &mTiles});

            if(word == "bKing")
                mBlackKing = new King{Color::BLACK, iBoardRow, iBoardCol, &mTiles};
            if(word == "bQueen")
                mBlackPieces[blackPieceCount++].reset(new Queen{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bRook")
                mBlackPieces[blackPieceCount++].reset(new Rook{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bBishop")
                mBlackPieces[blackPieceCount++].reset(new Bishop{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bKnight")
                mBlackPieces[blackPieceCount++].reset(new Knight{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
            if(word == "bPawn")
                mBlackPieces[blackPieceCount++].reset(new Pawn{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
        }
    }

    // Fill in the rest with blanks
    for (int i = whitePieceCount; i < 15; ++i)
        mWhitePieces[i].reset(nullptr);

    for (int i = blackPieceCount; i < 15; ++i)
        mBlackPieces[i].reset(nullptr);
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
        Piece* temp = mBlackPieces[i].get();
        while (temp->peekNextPossibleMove() == true) 
        {
            std::cout << this->get_board_as_string() << "\n\n";
        }
    }
    
    // Testing a piece's possibleLandings() function...
    /*
    Piece* a = ((mTiles[7][4]).getContainedPiece());
    std::cout << this->get_board_as_string() << "\n\n";

    std::vector<std::pair<int, int>> possibleMoves = a->getLegalMoves();
    for (int i = 0; i < possibleMoves.size(); i++)
    {
        std::cerr << possibleMoves[i].first << " " << possibleMoves[i].second << std::endl;
    }
    */
}
