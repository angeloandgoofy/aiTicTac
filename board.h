#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <limits>
#include <algorithm>
#include <climits> 
using namespace std;

struct Move {
    int row;
    int col;
};

class Game{
public:
Game(){
    currentPlayer = 'X';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}
void board_(){
    system("cls");
    std::cout << std::endl << std::endl;
    std::cout << "   TIC-TAC-TOE" << std::endl;
    std::cout << " " << std::string(14, '-') << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << "  |";
            std::cout << board[i][j]; 
            
        }
        std::cout << "  |";
        std::cout << std::endl;
        std::cout << " " << std::string(14, '-') << std::endl;
    }
    
}
void HumanMove() {
    int row, column;
    std::cout << "Player " << currentPlayer << " your turn" << std::endl;
    std::cout << "Row, Column you would like to play: ";
    
    while (true) {
        if (!(std::cin >> row >> column)) {
            // Invalid input, clear error flag and consume the invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter valid integers for row and column." << std::endl;
            std::cout << "Row, Column you would like to play: ";
            continue;
        }

        if (row < 0 || row >= 3 || column < 0 || column >= 3) {
            std::cout << "Invalid position. Row and column values should be between 0 and 2." << std::endl;
            std::cout << "Row, Column you would like to play: ";
            continue;
        }

        if (board[row][column] == ' ') {
            board[row][column] = currentPlayer;
            break;
        }
        else {
            std::cout << "Position already taken. Please choose an empty position." << std::endl;
            std::cout << "Row, Column you would like to play: ";
        }
    }
    currentPlayer = 'O';
}


bool horizontal() {
    for (int i = 0; i < 3; i++) {
        int count = 0;
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                count++;
            }
            else if (board[i][j] == 'O') {
                count--;
            }
        }
        
        if (count == 3) {
            std::cout << "Player X wins" << std::endl;
            return true;
        }
        else if (count == -3) {
            std::cout << "Player O wins" << std::endl;
            return true;
        }
        else {
            count = 0;
        }
    }
    
    return false;
}

bool vertical() {
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') {
                std::cout << "Player X wins" << std::endl;
                return true;
            }
            else if (board[0][i] == 'O') {
                std::cout << "Player O wins" << std::endl;
                return true;
            }
        }
    }
    return false;
}
bool draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // If there's an empty space, the game is not a draw
                return false;
            }
        }
    }

    // No empty spaces, the game is a draw
    return true;
}

bool checkWinner(){
    if(diagonal()){
        std::cout << "Player " << player << " wins";
        return true;
    }
    else if(vertical()){
        return true;
    }
    else if(horizontal()){
        return true;
    }
    else if(draw()){
        std::cout << "DRAW" << std::endl;
        return true;
    }
    return false;
}
bool diagonal() {
    char player;
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
        return true;
    }
    else if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '){
        return true;
    }
    return false;
}

bool isMovesLeft(char board[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]==' ') 
                return true; 
    return false; 
} 
  
int evaluate(char b[3][3]) 
{ 
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]==player) 
                return +10; 
            else if (b[row][0]==opponent) 
                return -10; 
        } 
    } 
  
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]==player) 
                return +10; 
  
            else if (b[0][col]==opponent) 
                return -10; 
        } 
    } 
  
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            return +10; 
        else if (b[0][0]==opponent) 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            return +10; 
        else if (b[0][2]==opponent) 
            return -10; 
    }  
    return 0; 
} 
  
int minimax(char board[3][3], int depth, bool isMax) 
{ 
    int score = evaluate(board); 
    if (score == 10) 
        return score; 
  
    if (score == -10) 
        return score; 
  
    if (isMovesLeft(board)==false) 
        return 0; 
  
    // If this maximizer's move 
    if (isMax) 
    { 
        int best = -1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]==' ') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
  
    // If this minimizer's move 
    else
    { 
        int best = 1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]==' ') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
  
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
} 

void aiMove()
{
    int bestVal = INT_MIN;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
  
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if cell is empty
            if (board[i][j]==' ')
            {
                // Make the move
                board[i][j] = 'O';
  
                int moveVal = minimax(board,0, false);
  
                // Undo the move
                board[i][j] = ' ';
  
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestMove.row][bestMove.col] = currentPlayer;
    currentPlayer ='X';
}

private:
    private:
        char board[3][3];
        char currentPlayer;
        char player = 'O'; 
        char opponent = 'X';
};

#endif