#include <iostream>

using namespace std;

struct player {
    string firstName, lastName;
    char piece;
    int wins = 0, loss = 0, draws = 0;
};

void capitalize(char[], char, int, int, int);// args: game[], piece, spot1, spot2, spot3
void tallyScore(char, player&, player&);// args: piece, &p1, &p2
void setPiece(char, player&);// args: piece, &user
void displayBoard(char []);// args: game[]
void splitName(string, char, player&);// args: name, piece, &user
void placePiece(char [], player, int);// args: game[], user, spot
void displayStats(player, player);// args: p1, p2
void resetGame(char []);// args: game[]
bool checkDraw(char []);// args: game[]
bool checkWin(char[], char, int);// args: game[], piece, spot
bool checkDiag(char[], char);// args: game[], piece
bool checkDown(char[], char);// args: game[], piece
bool checkAcross(char[], char);// args: game[], piece
player playGame(char[], player, player);// args: game[], p1, p2
player goesFirst(player, player);//args: p1, p2, firstGame


int main()
{
    player p1, p2, loser;
    string name;
    char playAgain;
    char game[9] = {
    '1', '4', '7', '2', '5', '8', '3', '6', '9'
    };
    int games = 0;

    cout << "Please enter the name of player 1: ";
    getline(cin, name);

    splitName(name, 'o', p1);
    cout << "Please enter the name of player 2: ";
    getline(cin, name);
    splitName(name, 'x', p2);

    player first, second;
    first = goesFirst(p1, p2);
    cout << "Play Game!\n";

    if (first.firstName == p1.firstName)
    {
        second = p2;
    }
    else
    {
        second = p1;
    }

    loser = playGame(game, first, second);
    tallyScore(loser.piece, p1, p2);
    displayStats(p1, p2);

    cout << "\nPlay again? (y, n): ";
    cin >> playAgain;
    games++;

    while (playAgain == 'y')
    {
        resetGame(game);
        if (loser.firstName == p1.firstName)
        {
            loser = playGame(game, loser, p2);
        }
        else
        {
            loser = playGame(game, loser, p1);
        }

        tallyScore(loser.piece, p1, p2);
        displayStats(p1, p2);
        cout << "\nPlay again? (y, n): ";
        cin >> playAgain;
        games++;
    }

    return 0;
}

/*
=========================================================================
Args:
    - name: string of user's full name from cin statement
    - user: used to place the first and last name of the user in the struct
        members firstName and lastName.

This function is designed to isolate the first and last name and set them
inside the player ADT.
=========================================================================
*/
void splitName(string name, char piece, player& user)
{
    string n = "";

    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] == ' ')
        {
            user.firstName = n;
            n = "";
        }
        else
        {
            n = n + name[i];
        }
    }
    user.lastName = n;
    setPiece(piece, user);
}

/*
=====================================================================================
Args:
    -piece: players game piece
    -&user: reference to player
Set's the players game piece based on the piece argument.
=====================================================================================
*/

void setPiece(char piece, player& user)
{
    user.piece = piece;
}

/*
=====================================================================================
Args:
    -game[]: array to contain the board
Game board is to be arranged as follows:
+---+---+---+
| 1 | 4 | 7 |
+---+---+---+
| 2 | 5 | 8 |
+---+---+---+
| 3 | 6 | 9 |
+---+---+---+
=====================================================================================
*/
void displayBoard(char game[])
{
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "| " << game[i] << " ";
        if ((i + 1) % 3 == 0)
        {
            cout << "|\n+---+---+---+\n";
        }
    }
}
/*
=====================================================================================
Args:
    -game[]: array that contains the board data
    -user: ADT used to reference the user's info
    -spot: User-selected spot to place their game piece

This functions purpose is to place each players game piece in the array game.
=====================================================================================
*/
void placePiece(char game[], player user, int spot)
{
    switch(spot)
    {
    case 1:
        {
            game[0] = user.piece;
            break;
        }
    case 2:
        {
            game[3] = user.piece;
            break;
        }
    case 3:
        {
            game[6] = user.piece;
            break;
        }
    case 4:
        {
            game[1] = user.piece;
            break;
        }
    case 5:
        {
            game[4] = user.piece;
            break;
        }
    case 6:
        {
            game[7] = user.piece;
            break;
        }
    case 7:
        {
            game[2] = user.piece;
            break;
        }
    case 8:
        {
            game[5] = user.piece;
            break;
        }
    case 9:
        {
            game[8] = user.piece;
            break;
        }
    }
}
/*
=====================================================================================
Args:
    -game[]: game board
    -piece: user's game piece to be passed to checkWin child functions
    -spot: last place a user placed a piece

Handler function that calls all winning configurations and capitalizes them and
returns a boolean value based on game status.
=====================================================================================
*/
bool checkWin(char game[], char piece, int spot)
{
    bool winA, winB, winC;
    int row, col;

    winA = checkAcross(game, piece);
    winB = checkDiag(game, piece);
    winC = checkDown(game, piece);

    if (winA)
    {
        if (spot == 1 || spot == 4 || spot == 7)
            row = 0;
        else if (spot == 2 || spot == 5 || spot == 8)
            row = 3;
        else
            row = 6;

        capitalize(game, piece, row, row + 1, row + 2);
    }

    if (winC)
    {
        if (spot == 1 || spot == 2 || spot == 3)
            col = 0;
        else if (spot == 4 || spot == 5 || spot == 6)
            col = 1;
        else
            col = 2;

        capitalize(game, piece, col, col + 3, col + 6);
    }

    if (winB)
    {
        int center = 4;

        if (spot == 1 || spot == 9)
        {
            capitalize(game, piece, center, 0, 8);
            if(game[2] == piece)
            {
                if (game[6] == piece)
                {
                    capitalize(game, piece, center, 2, 6);
                }
            }
        }
        else
        {
            capitalize(game, piece, center, 2, 6);
            {
                if (game[0] == piece)
                {
                    if (game[8] == piece)
                    {
                        capitalize(game, piece, center, 0, 8);
                    }
                }
            }
        }
    }

    return (winA || winB || winC);
}

/*
=====================================================================================
Args:
    -game[]: game board
    -piece: users piece
Scans the whole board and looks for any consistent 3 pieces going across the board
and returns a boolean value based on the findings.
=====================================================================================
*/
bool checkAcross(char game[], char piece)
{
    bool result = false;

    if (piece == game[0])
    {
        if (piece == game[1])
        {
            if (piece == game[2])
                result = true;
        }
    }

    if (piece == game[3])
    {
        if (piece == game[4])
        {
            if (piece == game[5])
                result = true;
        }
    }
    if (piece == game[6])
    {
        if (piece == game[7])
        {
            if (piece == game[8])
                result = true;
        }
    }


    return result;
}
/*
=====================================================================================
Args:
    -game[]: game board
    -piece: users piece
Scans the whole board and looks for any consistent 3 pieces going down the board and
returns a boolean value based on the findings.
=====================================================================================
*/
bool checkDown(char game[], char piece)
{
    bool result = false;

    if (piece == game[0])
    {
        if (piece == game[3])
        {
            if (piece == game[6])
                result = true;
        }
    }
    if (piece == game[1])
    {
        if (piece == game[4])
        {
            if (piece == game[7])
                result = true;
        }
    }
    if (piece == game[2])
    {
        if (piece == game[5])
        {
            if (piece == game[8])
                result = true;
        }
    }

    return result;
}
/*
=====================================================================================
Args:
    -game[]: game board
    -piece: users piece
Scans the whole board and looks for any consistent 3 pieces going diagonally across
the board and returns a boolean value based on findings.
=====================================================================================
*/
bool checkDiag(char game[], char piece)
{
    bool result = false;
    if (piece == game[4])
    {
        if(piece == game[0])
        {
            if (piece == game[8])
                result = true;
        }
        if (piece == game[2])
        {
            if (piece == game[6])
                result = true;
        }
    }

    return result;
}
/*
=====================================================================================
Args:
    -game: game board
    -piece:winning user's piece
    -spot1, spot2, spot3: positions of 3 winning pieces

Capitalizes any winning position passed into the function.
=====================================================================================
*/
void capitalize(char game[], char piece, int spot1, int spot2, int spot3)
{
    if(piece == 'x')
    {
        game[spot1] = 'X';
        game[spot2] = 'X';
        game[spot3] = 'X';
    }
    else if (piece == 'o')
    {
        game[spot1] = 'O';
        game[spot2] = 'O';
        game[spot3] = 'O';
    }
}
/*
=====================================================================================
Args:
    -p1, p2: players of the game
Prints out the stats of each player in a given format.
=====================================================================================
*/
void displayStats(player p1, player p2)
{
    string name1 = p1.firstName + " " + p1.lastName;
    string name2 = p2.firstName + " " + p2.lastName;

    cout << name1 << " has "
         << p1.wins << " win(s), "
         << p1.loss << " loss(es), and "
         << p1.draws << " draw(s).\n";
    cout << name2 << " has "
         << p2.wins << " win(s), "
         << p2.loss << " loss(es), and "
         << p2.draws << " draw(s).\n";
}
/*
=====================================================================================
Args:
    -p1, p2: players

Returns the player whose name has the lower first name according to ASCII value.
=====================================================================================
*/
player goesFirst(player p1, player p2)
{
    string name1 = p1.firstName + p1.lastName;
    string name2 = p2.firstName + p2.lastName;

    if (name1 > name2)
        return p2;
    else
        return p1;
}
/*
=====================================================================================
Args:
    -piece: winning piece
    -p1, p2: players of the game
Increments the wins, losses, and draws of each player.
=====================================================================================
*/
void tallyScore(char piece, player& p1, player& p2)
{
    if (piece == 'd')
    {
        p1.draws = p1.draws + 1;
        p2.draws = p2.draws + 1;
    }
    else if (piece == p2.piece)
    {
        p1.wins = p1.wins + 1;
        p2.loss = p2.loss + 1;
    }
    else if (piece == p1.piece)
    {
        p1.loss = p1.loss + 1;
        p2.wins = p2.wins + 1;
    }
}
/*
=====================================================================================
Args:
    -game:game board
Checks to see if the game board is full and that there is a draw game, and returns
false otherwise.
=====================================================================================
*/
bool checkDraw(char game[])
{

    for (int i = 0; i < 9; i++)
    {
        char val = game[i];

        if (val != 'x' && val != 'o')
            return false;
    }

    return true;
}
/*
=====================================================================================
Args:
    -game:game board
    -p1, p2: players
This function serves as the main function in the program. It runs the bulk of the
other functions present in the file.
=====================================================================================
*/
player playGame(char game[], player p1, player p2)
{
    cout << "This is a tic-tac-toe game that involves two human\n"
         << "players. The objective is the same as a regular game.\n"
         << "Each player will select a number between 1 and 9 and \n"
         << "after each move the game board will print again and\n"
         << "prompt the next move. Enjoy the game!\n";
    bool gameOver, draw;
    int pos;
    player loser;
    player noWinner;

    while (!gameOver)
    {
        displayBoard(game);
        cout << p1.firstName << " please select your move: ";
        cin >> pos;
        placePiece(game, p1, pos);
        gameOver = checkWin(game, p1.piece, pos);
        draw = checkDraw(game);
        loser = p2;

        if (draw)
        {
            displayBoard(game);
            return p1;
        }

        if (!gameOver)
        {
            displayBoard(game);
            cout << p2.firstName << " please select your move: ";
            cin >> pos;
            placePiece(game, p2, pos);
            loser = p1;
            gameOver = checkWin(game, p2.piece, pos);
        }

    }
    displayBoard(game);

    return loser;
}
/*
=====================================================================================
Args:
    -game:game board
Resets the board back to the start of the game. If this is not done all of the
previous winning configurations will still be present on the board.
=====================================================================================
*/
void resetGame(char game[])
{
    char game2[9] = {
    '1', '4', '7', '2', '5', '8', '3', '6', '9'
    };

    for (int x = 0; x < 9; x++)
    {
        game[x] = game2[x];
    }
}
