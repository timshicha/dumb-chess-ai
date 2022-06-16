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
    mWhitePieces[whitePieceCount++].reset(new King{Color::WHITE, 0, 3, &mTiles});
    mBlackPieces[blackPieceCount++].reset(new King{Color::BLACK, 7, 3, &mTiles});

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


// Converts the chess board into a nicely formatted string.
// The string can be displayed for a nice looking chess board visual.
std::string ChessBoard::get_board_as_string()
{
    using namespace std;

    // Display top labels
    string result = "   ";
    for (int i = 0; i < 8; i++) // Each column gets a number
        result += "   |  " + to_string(i);
    result += "\n";

    // For nice format
    for (int i = 0; i < 8; i++)
        result += "      |";
    result += "\n------+------+------+------+------+------+------+------+------\n";

    // Display each row
    for (int i = 0; i < 8; i++)
    {
        // Left-most column just holds the row number
        result += "  " + to_string(i) + "   |";

        // For each column, see if there's a piece. If so, display color.
        // This is the top row of each tile
        for (int j = 0; j < 8; j++)
        {
            // If there's a piece
            if(this->mTiles[i][j].getContainedPiece() != nullptr)
            {
                // Determine the color to display
                if(this->mTiles[i][j].getContainedPiece()->getColor() == Color::WHITE)
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
        for (int j = 0; j < 8; j++)
        {
            // If there's a piece, display the piece
            if(this->mTiles[i][j].getContainedPiece() != nullptr)
                result += this->mTiles[i][j].getContainedPiece()->getName();
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
    mTiles[4][0].setContainedPiece(mTiles[0][4].getContainedPiece());
    Rook* a = static_cast<Rook*> ((mTiles[0][0]).getContainedPiece());
    std::vector<std::vector<int>> b = a->getLegalMoves();
    std::cerr << "The piece at row 7 column 1 can move to the following positions:" << std::endl;
    for (int i = 0; i < b.size(); i++)
    {
        std::cerr << b[i][0] << " " << b[i][1] << std::endl;
    }
    */
}
