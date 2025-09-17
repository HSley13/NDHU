#include <stdio.h>

char checkWinner(char board[19][20]) 
{
    for (int i = 0; i < 19; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {
            // Check horizontally
            if (board[i][j] == 'O' && board[i][j + 1] == 'O' && board[i][j + 2] == 'O' && board[i][j + 3] == 'O' && board[i][j + 4] == 'O') return 'O';

            if (board[i][j] == 'X' && board[i][j + 1] == 'X' && board[i][j + 2] == 'X' && board[i][j + 3] == 'X' && board[i][j + 4] == 'X') return 'X';

            // Check vertically
            if (board[j][i] == 'O' && board[j + 1][i] == 'O' && board[j + 2][i] == 'O' && board[j + 3][i] == 'O' && board[j + 4][i] == 'O') return 'O';
            
            if (board[j][i] == 'X' && board[j + 1][i] == 'X' && board[j + 2][i] == 'X' && board[j + 3][i] == 'X' && board[j + 4][i] == 'X') return 'X';
        }
    }

    // Check diagonally (from top-left to bottom-right)
    for (int i = 0; i < 15; i++) 
    {
        for (int j = 0; j < 15; j++) 
        {
            if (board[i][j] == 'O' && board[i + 1][j + 1] == 'O' && board[i + 2][j + 2] == 'O' && board[i + 3][j + 3] == 'O' && board[i + 4][j + 4] == 'O') return 'O';

            if (board[i][j] == 'X' && board[i + 1][j + 1] == 'X' && board[i + 2][j + 2] == 'X' && board[i + 3][j + 3] == 'X' && board[i + 4][j + 4] == 'X') return 'X';
        }
    }

    // Check diagonally (from top-right to bottom-left)
    for (int i = 0; i < 15; i++) 
    {
        for (int j = 4; j < 19; j++) 
        {
            if (board[i][j] == 'O' && board[i + 1][j - 1] == 'O' && board[i + 2][j - 2] == 'O' && board[i + 3][j - 3] == 'O' && board[i + 4][j - 4] == 'O') return 'O';

            if (board[i][j] == 'X' && board[i + 1][j - 1] == 'X' && board[i + 2][j - 2] == 'X' && board[i + 3][j - 3] == 'X' && board[i + 4][j - 4] == 'X') return 'X';
        }
    }

    return 'N';
}

int main(void) 
{
    char board[19][20];

    for (int i = 0; i < 19; i++)  scanf("%s", board[i]);
    
    char winner = checkWinner(board);

    if (winner == 'O') printf("White\n");
    
    else if (winner == 'X') printf("Black\n");

    else printf("No winner\n");
}