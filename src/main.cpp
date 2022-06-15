#include <iostream>
#include "chess_board.h"

using namespace std;


int main(int argc, char* argv[])
{
    ChessBoard test;
    cout << test.get_board_as_string();

    test.test();

    return 0;
}