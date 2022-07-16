#include "chess_board.h"
#include "chess_pair.h"
#include "pieces/pieces.h"

#include <memory>
#include <unordered_map>
#include <stack>
#include <vector>
#include <array>

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
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new King{Color::WHITE, 7, 3, &mTiles});
    mTiles[7][3].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount].get());
    mKings[int(Color::WHITE)] = mPieces[int(Color::WHITE)][whitePieceCount++].get();
    
    mPieces[int(Color::BLACK)][whitePieceCount].reset(new King{Color::BLACK, 0, 3, &mTiles});
    mTiles[7][3].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount].get());
    mKings[int(Color::BLACK)] = mPieces[int(Color::BLACK)][blackPieceCount++].get();

    //Add queens
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Queen{Color::WHITE, 7, 4, &mTiles});
    mTiles[7][4].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
    
    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Queen{Color::BLACK, 0, 4, &mTiles});
    mTiles[0][4].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());

    //Add bishops
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Bishop{Color::WHITE, 7, 2, &mTiles});
    mTiles[7][2].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Bishop{Color::WHITE, 7, 5, &mTiles});
    mTiles[7][5].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
    
    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Bishop{Color::BLACK, 0, 2, &mTiles});
    mTiles[0][2].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Bishop{Color::BLACK, 0, 5, &mTiles});
    mTiles[0][5].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());

    //Add knights
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Knight{Color::WHITE, 7, 1, &mTiles});
    mTiles[7][1].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Knight{Color::WHITE, 7, 6, &mTiles});
    mTiles[7][6].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());

    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Knight{Color::BLACK, 0, 1, &mTiles});
    mTiles[0][1].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Knight{Color::BLACK, 0, 6, &mTiles});
    mTiles[0][6].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    
    ////Add rooks
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Rook{Color::WHITE, 7, 0, &mTiles});
    mTiles[7][0].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
    mPieces[int(Color::WHITE)][whitePieceCount].reset(new Rook{Color::WHITE, 7, 7, &mTiles});
    mTiles[7][7].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());

    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Rook{Color::BLACK, 0, 0, &mTiles});
    mTiles[0][0].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    mPieces[int(Color::BLACK)][blackPieceCount].reset(new Rook{Color::BLACK, 0, 7, &mTiles});
    mTiles[7][0].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    
    //Add pawns
    for(int iCol = 0; iCol < 8; ++iCol)
    {
        mPieces[int(Color::WHITE)][whitePieceCount].reset(new Pawn{Color::WHITE, 6, iCol, &mTiles});
        mTiles[6][iCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
        mPieces[int(Color::BLACK)][blackPieceCount].reset(new Pawn{Color::BLACK, 1, iCol, &mTiles});   
        mTiles[1][iCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
    }
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

   int whitePieceCount = 0, blackPieceCount = 0;

    // Add all the pieces
    for(int iBoardRow = 0; iBoardRow < 8; ++iBoardRow)
    {
        for(int iBoardCol = 0; iBoardCol < 8; ++iBoardCol)
        {
            std::string word = board[iBoardRow][iBoardCol];

            if(word == "wKing")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new King{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mKings[int(Color::WHITE)] = mPieces[int(Color::WHITE)][whitePieceCount].get();
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            }
            if(word == "wQueen")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new Queen{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            }
            if(word == "wRook")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new Rook{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            }

            if(word == "wBishop")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new Bishop{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            }
            if(word == "wKnight")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new Knight{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            }
            if(word == "wPawn")
            {
                mPieces[int(Color::WHITE)][whitePieceCount].reset(new Pawn{Color::WHITE, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::WHITE)][whitePieceCount++].get());
            } 

            if(word == "bKing")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new King{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mKings[int(Color::BLACK)] = mPieces[int(Color::BLACK)][blackPieceCount].get();
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
            if(word == "bQueen")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new Queen{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
            if(word == "bRook")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new Rook{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
            if(word == "bBishop")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new Bishop{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
            if(word == "bKnight")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new Knight{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
            if(word == "bPawn")
            {
                mPieces[int(Color::BLACK)][blackPieceCount].reset(new Pawn{Color::BLACK, iBoardRow, iBoardCol, &mTiles});
                mTiles[iBoardRow][iBoardCol].setContainedPiece(mPieces[int(Color::BLACK)][blackPieceCount++].get());
            }
        }
    }

    mTurnColor = turnColor;
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

//Pushes on the stack
bool ChessBoard::tempMove(int oldRow, int oldCol, int newRow, int newCol)
{
    //If max amount of temp moves have been made already
        if(mStates.size() >= 4)
        return false;

    //Grab the piece to be moved
    auto targetPiece = mTiles[oldRow][oldCol].getContainedPiece();
    //If tile specified to contain the target piece is emtpy
    if(targetPiece == nullptr)
        return false;
    //If the specified piece is the wrong color
    if(targetPiece->getColor() != mTurnColor)
        return false;
    
     //Grab the piece's destination tile
    auto targetTile = &mTiles[newRow][newCol];
    //Grab the destination tile's contained piece
    auto targetTileContainedPiece = targetTile->getContainedPiece();

    //If the target tile is occupied by an ally
    if(targetTileContainedPiece != nullptr && targetTileContainedPiece->getColor() == mTurnColor)
        return false;

    //If the attempted move is not in the piece's moveset
    if(!pairInVector(targetPiece->getLegalMoves(), {newRow, newCol}))
        return false;

    //Rememeber the current state
    std::unordered_map<Piece*, std::pair<int, int>> currentState;
    for(auto& iSameColorPieces : mPieces)
    {
        for(auto& iPiece : iSameColorPieces)
        {
            //Insert every piece as a key, and every tile as the data
            //If a piece is dead, map it to {-1, -1}
            if(iPiece->isAlive() == false)
                currentState.insert({iPiece.get(), {-1, -1}});

            currentState.insert({iPiece.get(), {iPiece->getRow(), iPiece->getCol()}});
        }
    }
    //Push the state on the stack
    mStates.push(currentState);

    //If the target tile is occupied by an enemy, kill it
    if(targetTileContainedPiece != nullptr && targetTileContainedPiece->getColor() != mTurnColor)
    {
        //Take the enemy piece off the board
        targetTile->setContainedPiece(nullptr);
        //kill it
        targetTileContainedPiece->kill();
    }

    //Move the target piece onto the target tile
    mTiles[targetPiece->getRow()][targetPiece->getCol()].setContainedPiece(nullptr);
    targetPiece->setPosition(newRow, newCol);
    targetTile->setContainedPiece(targetPiece);

    //Switch the color of the turn
    this->switchTurnColor();


    //If moving the piece puts the king in check
    //Pop the stack and return false
    if(isInCheck(mTurnColor))
        {
            this->undoTempMove();
            return false;
        }
    return true;
}

//Pops off the stack
bool ChessBoard::undoTempMove()
{
    //If the stack is empty
        if(mStates.size() == 0)
        return false;

    //Restore the board
    auto& map = mStates.top();
    for (auto& [piece, tileCoordinates] : map)
		{
            //If piece wasn't mapped
			if(tileCoordinates.first == -1)
                continue;
            
            //If this piece was killed last temp move
            if(piece->isAlive() == false)
            {
                piece->undoKill(tileCoordinates.first, tileCoordinates.second);
                mTiles[tileCoordinates.first][tileCoordinates.second].setContainedPiece(piece);
            }
            ////If this piece was moved last temp move
            if(piece->getRow() != tileCoordinates.first)
            {
                piece->setPosition(tileCoordinates.first, tileCoordinates.second);
                mTiles[tileCoordinates.first][tileCoordinates.second].setContainedPiece(piece);
            }
		}

    //Pop of the now-restored frame
    mStates.pop();

    //Switch the color of the turn
    this->switchTurnColor();

    return true;
}

//Flip the color of the ongoing turn
void ChessBoard::switchTurnColor()
{
    if(mTurnColor == Color::WHITE)
        mTurnColor = Color::BLACK;
    else
        mTurnColor = Color::WHITE;
}

//Returns how many states are on the stack
int ChessBoard::countTempMoves() const
{
    return mStates.size();
}