#include <iostream>
#include "chess_board.h"

using namespace std;

// temp function
bool askMove(ChessBoard &board)
{
    int oldRow, oldCol, newRow, newCol;
    cout << "Old row: ";
    cin >> oldRow; cin.ignore(100, '\n');
    cout << "Old column: ";
    cin >> oldCol; cin.ignore(100, '\n');
    cout << "New row: ";
    cin >> newRow; cin.ignore(100, '\n');
    cout << "New column: ";
    cin >> newCol; cin.ignore(100, '\n');

    // Try moving
    return board.safeMove(oldRow, oldCol, newRow, newCol);
}

int main(int argc, char* argv[])
{
    ChessBoard test ("default.txt");
    cout << test.get_board_as_string();

    //test.test();

    int turn = 0;

    while(true)
    {
        cout << "It's " << turn << "'s turn:\n";
        while(askMove(test) == false)
        {
            cout << "Illegal move. Try again:\n";
        }
        cout << test.get_board_as_string();

        turn = !turn;
    }
    
    return 0;
}