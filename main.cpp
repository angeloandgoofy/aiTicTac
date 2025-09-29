#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    Game game;
    
    
    while(!game.checkWinner()){
        game.board_();
        game.HumanMove();
        game.aiMove();
    }
    game.board_();
}
