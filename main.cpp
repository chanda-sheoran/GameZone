// GAME ZONE CONSIST OF 4 GAMES

// TIC-TAC-TOE
// ROCK PAPER SCISSOR
// SUDOKU
// HANGMAN

#include <iostream>
#include <string.h>
#include <time.h>
#include <cstdlib>

using namespace std;

// GAME 1 - HANGMAN
// In this game, you'll have to guess the month name you will be provided with hints

class game1
{
public:
    int chance;
    string message;

    game1()
    {
        chance=3;
        message = "Play! Best Wishes :)";
    }

    void menu()
    {

        system("CLS");
        cout << "\t\t\t\t\t";

        cout << "\n------------------------------------------------------------------------------------------\n";

        cout << "\n\t\t\t\tHangman Game!\n";

        cout << "\n\t\tYou have " << chance << " chances to try and guess the correct month.";

        cout << "\n\n\t\t\t\t" + message;

        cout << "\n------------------------------------------------------------------------------------------\n";
    }

    // FUNCTION TO CHECK WHETHER YOUR CHOICE IS CORRECT OR INCORRECT
    int check(char guess, string secretmonth, string &guessmonth)
    {
        int matches = 0;
        int len = secretmonth.length();

        for (int i = 0; i < len; i++)
        {
            if (guess == secretmonth[i])
            {
                guessmonth[i] = guess;
                matches++;
            }
        }
        return matches;
    }

    // FUNCTION DOING ALL THE WORKING AND DISPLAYING THE ANSWER AND PROVIDING HINTS
    void work()
    {
        string name;
        char letter;
        string month;

        string months[] =
            {
                "january",
                "february",
                "march",
                "april",
                "may",
                "june",
                "july",
                "august",
                "september",
                "october",
                "november",
                "december"};

        srand(time(NULL));

        int n = rand() % 12;
        month = months[n];
        string hidden(month.length(), 'X');

        while (chance != 0)
        {
            menu();

            cout << "\n\n\t\t\t\t" << hidden;
            cout << "\n\n\t\t\t\tGuess a letter : ";
            cin >> letter;

            if (check(letter, month, hidden) == 0)
            {
                message = "Incorrect letter. Try Again!";
                chance -= 1;
            }

            else
            {
                message = "Great! You guessed a right letter";
            }

            if (month == hidden)
            {
                message = "Congratulations! You got the correct month!";
                menu();
                cout << "\n\t\t\t\tThe month is : " << month << endl;
                break;
            }
        }

        if (chance == 0)
        {
            message = "Sorry!!!...you lost.\n\n\t\t\t\tBETTER LUCK NEXT TIME";
            menu();
            cout << "\n\t\t\t\tThe month was : " << month << endl;
        }
    }
};

// GAME 2 - SUDOKU GAME

class game2
{
    const static int c = 9;

public:
    bool isSafe(int board[c][c], int row, int col, int num)
    {

        for (int i = 0; i < c; i++)
        {
            if (board[row][i] == num)
            {
                return false;
            }
        }

        for (int i = 0; i < c; i++)
        {
            if (board[i][col] == num)
            {
                return false;
            }
        }

        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i + boxRowStart][j + boxColStart] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }

    // FUNCTION TO PRINT THE SUDOKU BOARD
    void printBoard(int grid[c][c])

    {

        system("cls");
        cout << "\n\t\t\tSUDOKU" << endl;
        cout <<  "\t\t\t-----------------------------------------------------------------------------------" << endl;

        for (int row = 0; row < c; row++)
        {
            for (int col = 0; col < c; col++)
            {
                if (col == 3 || col == 6)
                {
                    cout << " | ";
                }
                cout << grid[row][col] << " ";
            }
            if (row == 2 || row == 5)
            {
                cout << endl;
                for (int i = 0; i < c; i++)
                {
                    cout << "---";
                }
            }
            cout << endl;
        }
    }

    // FUNCTION DOING ALL THE WORKING AND PLAYING SUDOKU

    bool solveSudoku(int board[c][c], int row, int col)
    {
        if (row == c - 1 && col == c)
            return true;

        if (col == c)
        {
            row++;
            col = 0;
        }

        if (board[row][col] != 0)
            return solveSudoku(board, row, col + 1);

        for (int num = 1; num <= 9; num++)
        {
            if (isSafe(board, row, col, num))
            {
                board[row][col] = num;

                if (solveSudoku(board, row, col + 1))
                    return true;

                board[row][col] = 0;
            }
        }
        return false;
    }

    // FUNCTION CHECKING WHETHER THE GAME IS FINISHED OR NOT

    bool isSolvedCompletely(int grid[c][c])
    {
        for (int row = 0; row < c; row++)
        {
            for (int col = 0; col < c; col++)
            {
                if (grid[row][col] == 0)
                    return false;
            }
        }
        return true;
    }

    // FUNCTION TO TAKE USER CHOICE AND CALL THE WORKING FUNCTION

    void playGame(int board[c][c])
    {
        int ch;
        int row, col, num;

        while (true)
        {
            printBoard(board);
            cout << endl
                 << endl;
            cout << "Enter row : ";

            cin >> row;

            cout << "Enter column : ";

            cin >> col;

            cout << "Enter number : ";

            cin >> num;

            if (row == -1 || col == -1 || num == -1)
            {
                solveSudoku(board, 0, 0);

                printBoard(board);

                cout << endl;

                cout << "Better luck next time !!!" << endl;

                return;
            }

            if (isSolvedCompletely(board)) break;

            row--;
            col--;

            if (!isSafe(board, row, col, num))
            {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            board[row][col] = num;
        }

        bool solved = true;

        for (int i = 0; i < c; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (board[i][j] == 0)
                {
                    solved = false;
                    break;
                }
            }
        }
        if (solved)
        {
            cout << "Congratulations! You have solved the puzzle." << endl;
            printBoard(board);
        }
        else
        {
            cout << "Puzzle not solved. Better luck next time." << endl;
        }
    }
    void work()
    {

        int board[c][c] = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        };

        system("cls");

        cout << "\t\t\t                                        SUDOKU                                 " << endl;
        cout << "\t\t\t-----------------------------------------------------------------------------------" << endl;

        playGame(board);
    }
};

// GAME 3 - ROCK PAPER SCISSOR
// In this game, you'll play rock paper and scissors with bot

class game3
{
public:

    // USING RANDOM FUNCTION TO GENERATE BOT CHOICE
    int botChoice()
    {
        srand(time(NULL)); // randomly generates a choice between 1-3;

        return rand() % 3 + 1;
    }

    // FUNCTION TO TAKE USER CHOICE
    int userChoice()
    {
        int userChoice; // user gives the input between 1-3;

        while (true)
        {
            cout << "Enter your choice" << endl;
            cout << "1. Rock" << endl;
            cout << "2. Paper" << endl;
            cout << "3. Scissors" << endl;
            cin >> userChoice;

            if (userChoice > 3 || userChoice < 1)
            {
                cout << "Please enter a valid input" << endl;
                continue;
            }
            else
            {
                break;
            }
        }
        return userChoice;
    }

    // FUNCTION TO PRINT THE RESULT
    // WHETHER USER IS WINNER OR THE BOT

    int result(int userChoice, int botChoice)
    {
        if (userChoice == botChoice)
        return 0;

        else if (botChoice == 3 && userChoice == 1)
        return 1;

        else if (botChoice == 3 && userChoice == 2)
        return 2;
        
        else if (userChoice == 3 && botChoice == 2)
        return 1;
        
        else if (userChoice == 3 && botChoice == 1)
        return 2;

        else if (userChoice == 2 && botChoice == 1)
        return 1;

        else if (userChoice == 1 && botChoice == 2)
        return 2;

        return 0;
    }

    string choiceName(int choice)
    {
        if (choice == 1)
        {
            return "Rock";
        }
        else if (choice == 2)
        {
            return "Paper";
        }
        else
        {
            return "Scissors";
        }
    }

    // FUNCTION TO COMPARE USER CHOICE WITH BOT CHOICE
    void work()
    {
        int user, computer, winner;
        system("cls");
        do
        {
            user = userChoice();
            computer = botChoice();
            winner = result(user, computer);

            cout << "User choice : " << choiceName(user) << "\tbot Choice : " << choiceName(computer) << endl;
            if (winner == 1)
            {
                cout << "User wins" << endl;
            }
            else if (winner == 2)
            {
                cout << "bot wins" << endl;
            }
            else
            {
                cout << "Tie" << endl; // game continues if its a tie
            }
        }
        while (winner == 0); // exit
    }
};


// GAME 4 - TIC TAC TOE
// This code enables you to play the famous 2 player tic-tac-toe game

class game4
{
public:

    // Globally declared 2D-array
    char board[3][3];

    // Function to initialize the game board
    void initializeBoard()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = ' ';
            }
        }
        int count = 1;
        cout << "\n\n\t  ";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << count++;
                if (j < 2)
                {
                    cout << "  |  ";
                }
            }
            if (i < 2)
                cout << "\n\t----------------\n\t  ";
        }
        cout << "\n\n\n";
    }

    // Function shows the game board
    void showBoard(int x, int y)
    {
        cout << "\n\n\t  ";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << board[i][j];
                if (j < 2)
                {
                    cout << "  |  ";
                }
            }
            if (i < 2)
                cout << "\n\t----------------\n\t  ";
        }
        cout << "\n\n\n";
    }

    // Function to update the game board
    int updateBoard(int cell, char playerSign)
    {
        int row = (cell - 1) / 3;

        int col = (cell - 1) % 3;

        int isValid = 1;

        // accessing already played cell number

        if (board[row][col] != ' ')
        {
            cout << "\nInvalid: Cell is already Filled!\n";
            isValid = 0;
        }

        // valid cell position
        else
        {
            board[row][col] = playerSign;
        }
        showBoard(row, col);

        return isValid;
    }

    // Function to check the winner of the game
    int checkWinner(char sg)
    {
        // check all rows
        if (board[0][0] == sg && board[0][1] == sg && board[0][2] == sg ||
            board[1][0] == sg && board[1][1] == sg && board[1][2] == sg ||
            board[2][0] == sg && board[2][1] == sg && board[2][2] == sg)

        {
            return 1;
        }

        // check all columns
        else if (board[0][0] == sg && board[1][0] == sg && board[2][0] == sg ||
                 board[0][1] == sg && board[1][1] == sg && board[2][1] == sg ||
                 board[0][2] == sg && board[1][2] == sg && board[2][2] == sg)

        {
            return 1;
        }

        // check both diagonals
        else if (board[0][0] == sg && board[1][1] == sg && board[2][2] == sg ||
                 board[0][2] == sg && board[1][1] == sg && board[2][0] == sg)

        {
            return 1;
        }

        // There is no winner
        return 0;
    }

    // Start your game from here

    void playTicTacToe()
    {
        int gameResult = 0;
        int cell = 0;
        int playCount = 0;
        int updationResult = 1;
        int a;

        char playerSign = ' ';

        // start playing the game

        while (!gameResult && playCount < 9)
        {
            if (playCount % 2 == 0)
            {
                // player 1

                cout << "\nPlayer 1 [ X ] : ";
                playerSign = 'X';
            }
            else
            {
                // player 2

                cout << "\nPlayer 2 [ O ] : ";
                playerSign = 'O';
            }
            scanf("%d", &cell);

            if (cell > 0 && cell < 10)
            {
                updationResult = updateBoard(cell, playerSign);

                // if updation is possible

                if (updationResult)
                {
                    gameResult = checkWinner(playerSign);

                    // print the winner of the game

                    if (gameResult)
                    {
                        a = playerSign == 'X' ? 1 : 2;
                        cout << "\t * Player " << a << " Won!! *\n";
                    }

                    playCount++;
                }
            }

            else if (cell == -1)
            {
                cout << "\n\tGame Terminated\n";
                return;
            }

            else
            {
                cout << "\nPlease Enter a valid cell value\n";
            }
        }

        // no one won the game

        if (!gameResult && playCount == 9)
        {
            cout << "\n\t * Draw...  *\n";
        }
        cout << "\n\t --- Game Over --- \n";
    }

    void work()
    {

        cout << "---------- Tic Tac Toe ----------\n\n";

        cout << "\n* Instructions \n\n";
        cout << "\tPlayer 1 sign = X\n";
        cout << "\tPlayer 2 sign = O";
        cout << "\n\tTo exit from game, Enter -1\n";

        cout << "\n\n* Cell Numbers on Board\n";
        initializeBoard();

        char start = ' ';
        cout << "\n> Press Enter to start...";

        scanf("%c", &start);

        if (start)
        {
            int userChoice = 1;
            // restart the game
            while (userChoice)
            {
                playTicTacToe();
                cout << "\n* Menu\n";
                cout << "\nPress 1 to Restart";
                cout << "\nPress 0 for Exit";
                cout << "\n\nChoice: ";
                scanf("%d", &userChoice);
                if (userChoice)
                {
                    initializeBoard();
                }
                cout << "\n";
            }
        }
        cout << "\n :: Thanks for playing Tic Tac Toe game! :: \n";
    }
};


int main()
{
    cout << "\n\n\n\t\t\t\t\tSDF PROJECT BASED LEARNING \n\n\n";
    cout << "\t\t\t\t\t\tGAME ZONE\n\n\n\n\n";
    cout << "WELCOME TO OUR GAME ZONE" << endl;
    cout << "OUR GAME ZONE CONSIST OF FOUR GAMES" << endl;
    cout << "NAMELY :" << endl;
    cout << "HANGMAN" << endl;
    cout << "ROCK PAPER SCISSOR" << endl;
    cout << "SUDOKU" << endl;
    cout << "TIC-TAC-TOE" << endl;
    cout << "USERS CAN PLAY ANY GAME OF THEIR CHOICE" << endl;

    int choice;
    game1 g1;
    game2 g2;
    game3 g3;
    game4 g4;
    choice = 10;

    while (choice != 0)
    {
        cout << "ENTER\n1. TO PLAY HANGMAN\n";
        cout<<"2. TO PLAY SUDOKU \n";
        cout<<"3. TO PLAY ROCK,PAPER AND SCISSOR \n";
        cout<<"4. TO PLAY TIC-TAC-TOE \n";
        cout<<"0. TO EXIT GAME ZONE\n\n";
        cin >> choice;

        if (choice == 1)
            g1.work();
        if (choice == 2)
            g2.work();
        if (choice == 3)
            g3.work();
        if (choice == 4)
            g4.work();
    }
    if (choice == 0)
        exit(0);

    return 0;
}
