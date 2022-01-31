/*
 * Simulates a game of tic tac toe against the computer
 * Created on 1/30/2022 - 1/31/2022
 *
 * Copyright (c) 2022, Asa Barton
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Gets an empty tic-tac-toe game board represented by a 3x3 2-dimensional vector
std::vector<std::vector<char>> get2DTicTacToeVector();

// Displays a visual representation of what the current tic-tac-toe board looks like
void displayCurrentBoard(const std::vector<std::vector<char>>& v);

// Displays a welcome screen
void displayWelcomeScreen();

// Determines if there is a winner. If so, an X or an O is returned, depending on which letter occupies a three in a row
// Otherwise, the character, *, used to signify an empty spot is returned instead
char getCurrentWinner(const std::vector<std::vector<char>>& v);

// Allows the player to execute his/her move on the board
void executePlayerTurn(std::vector<std::vector<char>>& v, char player);

// Allows the computer to execute a move on the board
void executeComputerTurn(std::vector<std::vector<char>>& v, char computer, char player);

// Updates the board by replacing an asterisk with an 'o' or 'X' in the specified board location
void updateBoard(std::vector<std::vector<char>>& v, char row, char col, char player);

// Gets the number of empty spots left on the board
int getNumOfSpotsLeft(const std::vector<std::vector<char>>& v);

// Determines if the board is full (all spots have been taken)
bool boardIsFull(const std::vector<std::vector<char>>& v);

// Initializes the row and column variables with random integer values, which correspond to a random empty spot on the board
void initializeRandomRowAndColumn(const std::vector<std::vector<char>>& v, int& row, int& col);

// Looks for any two-in-a-rows of the same specified letter in any direction.
// If there are none, then row and col are initialized to -1
void initializeBestRowAndColumn(const std::vector<std::vector<char>>& v, int& row, int& col, char letter);

// Checks for a winner and announces if so
bool checkForWinner(const std::vector<std::vector<char>>& v, char player, char computer);

// Gets the player's game character ('X' or 'O')
char getPlayerChar();

// Gets the computer's game character ('X' or 'O')
char getComputerChar(char player);

//Creates a new line for input handling (discards any extra characters and spaces and the '\n')
void newLine();


int main()
{
    displayWelcomeScreen();
    std::vector<std::vector<char>> v = get2DTicTacToeVector();

    char player = getPlayerChar();
    char computer = getComputerChar(player);

    while (getCurrentWinner(v) == '*')
    {
        if (player == 'X')
            executePlayerTurn(v, player);
        else
            executeComputerTurn(v, computer, player);

        // Checks for a winner and announces if so
        if (checkForWinner(v, player, computer))
            break;

        if (player == 'O')
            executePlayerTurn(v, player);
        else
            executeComputerTurn(v, computer, player);

        // Checks for a winner and announces if so
        if (checkForWinner(v, player, computer))
            break;
    }

    return 0;
}

bool checkForWinner(const std::vector<std::vector<char>>& v, char player, char computer)
{
    if (getCurrentWinner(v) == player)
    {
        std::cout << "You won!!\nFinal board:\n";
        displayCurrentBoard(v);
        return true;
    }
    else if (getCurrentWinner(v) == computer)
    {
        std::cout << "Computer won. Better luck next time!\nFinal Board:\n";
        displayCurrentBoard(v);
        return true;
    }

    return false;
}

char getComputerChar(char player)
{
    if (player != 'X' && player != 'O')
    {
        std::cout << "Error - The player's character hasn't been properly defined.\n";
        exit(1);
    }

    if (player == 'X')
        return 'O';

    return 'X';
}

char getPlayerChar()
{
    char character;

    std::cout << "Choose your character...\n";
    std::cout << "Enter 'X' if you want to be the letter X\nEnter 'O' if you want to be the letter O\n";
    std::cin >> character;

    newLine();

    while (character != 'X' && character != 'x' && character != 'O' && character != 'o')
    {
        std::cout << "Error - '" << character << "' is not a valid character. Try again.\n";
        std::cin >> character;
        newLine();
    }

    std::cout << "Success! You are now the letter '" << char(toupper(character)) << "'\n";

    return toupper(character);
}

bool boardIsFull(const std::vector<std::vector<char>>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if (v[i][j] == '*')
                return false;
        }
    }

    return true;
}

void updateBoard(std::vector<std::vector<char>>& v, char row, char col, char player)
{
    if ((row != '1' && row != '2' && row != '3') || (col != '1' && col != '2' && col != '3'))
    {
        std::cout << "Error - Invalid row and/or column numbers\n";
        exit(1);
    }

    v[row - 49][col - 49] = player;
}

void executePlayerTurn(std::vector<std::vector<char>>& v, char player)
{
    if (boardIsFull(v))
    {
        std::cout << "Due to a full board, the game has come to a draw. :/\n";
        std::cout << "Final Board:\n";
        displayCurrentBoard(v);

        exit(0);
    }

    std::string character;
    bool emptySpotChosen = false;
    char row, col;

    std::cout << "*********************************************************************\n";
    std::cout << "Your turn!\n";
    std::cout << "Enter any character to continue..\n";
    std::cin >> character;
    newLine();

    displayCurrentBoard(v);

    while (! emptySpotChosen)
    {
        std::cout << "Enter row number (1 -> row 1, 2 -> row 2, 3 -> row 3)\n";
        std::cin >> row;

        newLine();

        while (row != '1' && row != '2' && row != '3')
        {
            std::cout << "Error - You must enter a number from 1 - 3\n";
            std::cin >> row;
            newLine();
        }

        std::cout << "Enter column number (1 -> col 1, 2 -> col 2, 3 -> col 3)\n";
        std::cin >> col;

        newLine();

        while (col != '1' && col != '2' && col != '3')
        {
            std::cout << "Error - You must enter a number from 1 - 3\n";
            std::cin >> col;
            newLine();
        }

        if (v[row - 49][col - 49] == '*')
            emptySpotChosen = true;
        else
            std::cout << "Error - That spot on the board has already been taken. Only enter spots not yet taken (noted with an asterisk)\n";
    }

    updateBoard(v, row, col, player);

    std::cout << "Success! Your move has been added to the board..\n";
    displayCurrentBoard(v);

    if (getCurrentWinner(v) != '*')
    {
        std::cout << "Enter any character to continue..\n";
        std::cin >> character;
        newLine();
    }

}

void executeComputerTurn(std::vector<std::vector<char>>& v, char computer, char player)
{
    srand(time(nullptr));

    if (boardIsFull(v))
    {
        std::cout << "Due to a full board, the game has come to a draw. :/\n";
        std::cout << "Final Board:\n";
        displayCurrentBoard(v);

        exit(0);
    }

    std::string character;
    int row, col;

    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Computer's Turn!\n";
    std::cout << "Enter any character to see the move that the computer makes..\n";
    std::cin >> character;
    newLine();

    initializeBestRowAndColumn(v, row, col, computer); // Offense mode
    if (row == -1 && col == -1)
    {
        initializeBestRowAndColumn(v, row, col, player); // Defense mode
        if (row == -1 && col == -1)
        {
            initializeRandomRowAndColumn(v, row, col); // Random mode
        }
    }

    v[row][col] = computer;

    displayCurrentBoard(v);
    std::cout << "Computer put '" << computer << "' at row " << row << " and column " << col << std::endl;

    if (getCurrentWinner(v) != '*')
    {
        std::cout << "Enter any character to continue..\n";
        std::cin >> character;
        newLine();
    }

}

void initializeRandomRowAndColumn(const std::vector<std::vector<char>>& v, int& row, int& col)
{
    int random = rand() % (getNumOfSpotsLeft(v)) + 1;
    int count = 0;

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if (v[i][j] == '*')
                count++;

            if (count == random)
            {
                row = i;
                col = j;
                break;
            }
        }

        if (count == random)
            break;
    }
}

char getCurrentWinner(const std::vector<std::vector<char>>& v)
{
    // Check for any horizontal or vertical 3-in-a-rows
    for (int i = 0; i < v.size(); i++)
    {
        // Horizontal Check
        if (v[i][0] == v[i][1] && v[i][0] == v[i][2] && (v[i][0] == 'X' || v[i][0] == 'O'))
            return v[i][0];

        // Vertical Check
        if (v[0][i] == v[1][i] && v[0][i] == v[2][i] && (v[0][i] == 'X' || v[0][i] == 'O'))
            return v[0][i];
    }

    // Check for any diagonal 3 in a rows
    if (v[0][0] == v[1][1] && v[0][0] == v[2][2] && (v[0][0] == 'X' || v[0][0] == 'O'))
        return v[0][0];

    if (v[2][0] == v[1][1] && v[2][0] == v[0][2] && (v[2][0] == 'X' || v[2][0] == 'O'))
        return v[2][0];

    // No winner yet
    return '*';
}

void initializeBestRowAndColumn(const std::vector<std::vector<char>>& v, int& row, int& col, char letter)
{
    int letterCount = 0, emptyCount = 0, temp = -1;
    row = -1;
    col = -1;

    for (int i = 0; i < v.size(); i++)
    {
        letterCount = 0;
        emptyCount = 0;

        // Check row
        for (int j = 0; j < v[i].size(); j++)
        {
            if (v[i][j] == letter)
                letterCount++;
            if (v[i][j] == '*')
            {
                temp = j;
                emptyCount++;
            }

        }

        if (letterCount == 2 && emptyCount == 1)
        {
            row = i;
            col = temp;
            return;
        }

        letterCount = 0;
        emptyCount = 0;

        // Check Column
        for (int j = 0; j < v.size(); j++)
        {
            if (v[j][i] == letter)
                letterCount++;
            if (v[j][i] == '*')
            {
                temp = j;
                emptyCount++;
            }
        }

        if (letterCount == 2 && emptyCount == 1)
        {
            row = temp;
            col = i;
            return;
        }
    }

    letterCount = 0;
    emptyCount = 0;

    // Check for Diagonal #1
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][i] == letter)
            letterCount++;
        if (v[i][i] == '*')
        {
            temp = i;
            emptyCount++;
        }
    }

    if (letterCount == 2 && emptyCount == 1)
    {
        row = temp;
        col = temp;
        return;
    }

    letterCount = 0;
    emptyCount = 0;

    // Check for Diagonal #2
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][v.size()-i-1] == letter)
            letterCount++;
        if (v[i][v.size()-i-1] == '*')
        {
            temp = i;
            emptyCount++;
        }
    }

    if (letterCount == 2 && emptyCount == 1)
    {
        row = temp;
        col = v.size() - temp - 1;
        return;
    }
}

int getNumOfSpotsLeft(const std::vector<std::vector<char>>& v)
{
    int num = 0;

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            if (v[i][j] == '*')
                num++;
        }
    }

    return num;
}

void displayWelcomeScreen()
{
    std::string character;
    std::cout << "Welcome to the wonderful world of Tic Tac Toe! Press any character and hit 'Enter' to begin.\n";
    std::cin >> character;

    newLine();
}

std::vector<std::vector<char>> get2DTicTacToeVector()
{
    std::vector<std::vector<char>> v;

    for (int i = 0; i < 3; i++)
    {
        std::vector<char> temp = {'*', '*', '*'};
        v.push_back(temp);
    }

    return v;
}

void displayCurrentBoard(const std::vector<std::vector<char>>& v)
{
    std::cout << std::endl;

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
            std::cout << v[i][j] << "  ";

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void newLine()
{
    char c;
    std::cin.get(c);

    while (c != '\n')
    {
        std::cin.get(c);
    }
}
