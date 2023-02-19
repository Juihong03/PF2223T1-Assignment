// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT7L
// Names: SUNTERRESAA SANKAR | Wong Jui Hong | Wong Wei Ping
// IDs: 1211102415 | 1211101452 | 1211102080
// Emails: 1211102415@student.mmu.edu.my | 1211101452@student.mmu.edu.my | 1211102080@student.mmu.edu.my
// Phones: 0197007723 | 0187783396 | 0105458442
// *********************************************************

//---------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

const int NUM_COMMANDS = 8;
const int MIN_LIFE = 10;
const int MAX_LIFE = 100;
const int MIN_ATTACK = 0;
const int MAX_ATTACK = 10;
const int MIN_RANGE = 1;
const int MAX_RANGE = 5;
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 20;
const int MIN_DIMENSION = 3;
int row = 5;
int column = 9;
int zombieCount = 1;
int alienX, alienY;
int aLife = MIN_LIFE + rand() % (MAX_LIFE - MIN_LIFE + 1);
int aAttack = 0;
int zLife = MIN_LIFE + rand() % (MAX_LIFE - MIN_LIFE + 1);
int zAttack = MIN_ATTACK + rand() % (MAX_ATTACK - MIN_ATTACK + 1);
vector<vector<string>> map_;

string commands[NUM_COMMANDS] =
    {
        "up     - Move up. ",
        "down   - Move down. ",
        "left   - Move left. ",
        "right  - Move right. ",
        "arrow  - Change the direction of an arrow.",
        "save   - Save the game.",
        "load   - Load a game. ",
        "quit   - Quit the game. "};

void gameDisplay();
void defaultSetting();
void init();
void gameboard();
void zombie();
void printHelps();
void getAlienPos();
void moveAlien(int directionX, int directionY);

struct gamezombie
{
    string name;
    int attackrange;
    int damage;
    int health;
};

// struct Game
// {
//     int row;
//     int column;
// };

void getAlienPos()
{
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            if (map_[i][j] == "A")
            {
                alienX = j;
                alienY = i;
            }
        }
    }
}

void gameDisplay()
{
    system("Color 0B");
    cout << endl;
    cout << "  W           W  EEEEEE  L        CCCC     OOO       M   M     EEEEEE           " << endl;
    cout << "  W    W W    W  E       L      C         O   O     M M M M    E           O    " << endl;
    cout << "   W  W   W  W   EEEEEE  L     C         O     O   M  M M  M   EEEEEE           " << endl;
    cout << "    W W   W W    E       L      C         O   O    M   M   M   E           O    " << endl;
    cout << "     W     W     EEEEEE  LLLLLL   CCCC     OOO     M       M   EEEEEE           " << endl;
    cout << endl;
    system("PAUSE");
    system("CLS");
}

void defaultSetting()
{
    cout << "----------------------------------------------------" << endl;
    cout << "|      #       Default Game Settings       #       |" << endl;
    cout << "|--------------------------------------------------|" << endl;
    cout << "|              Board Rows       :  5               |" << endl;
    cout << "|              Board Columns    :  9               |" << endl;
    cout << "|              Zombie Count     :  1               |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << endl;

    cout << "Do you wish to change the game setting (y/n) ? => ";

    char choice;
    cin >> choice;
    choice = tolower(choice);
    while (choice != 'y' && choice != 'n')
    {
        cout << "********************************************" << endl;
        cout << "| ERROR. Only Character (y/n) is Accepted. |" << endl;
        cout << "********************************************" << endl;
        cout << endl;
        cout << "Do you wish to change the game setting (y/n) ? => ";
        cin >> choice;
    }

    system("CLS");
    switch (choice)
    {
    case 'y':
        cout << "--------------------------------------------" << endl;
        cout << "|      #       Board Settings      #       |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << endl;
        cout << "Enter Rows => ";
        cin >> row;
        cout << endl;
        cout << "Enter Columns => ";
        cin >> column;

        while (row < MIN_DIMENSION || column < MIN_DIMENSION || row % 2 == 0 || column % 2 == 0 || cin.fail())
        {
            cout << endl;
            cout << "****************************************************************************************" << endl;
            cout << "| Invalid dimensions! Please enter odd numbers only and must be greater or equal to 3. |" << endl;
            cout << "****************************************************************************************" << endl;
            cout << "Enter Rows => ";
            cin >> row;
            cout << endl;
            cout << "Enter Columns => ";
            cin >> column;
        }

        cout << endl;

        cout << "--------------------------------------------" << endl;
        cout << "|      #       Zombie Settings     #       |" << endl;
        cout << "--------------------------------------------" << endl;
        cout << endl;
        cout << "Enter number of zombies => ";
        cin >> zombieCount;

        while (zombieCount > 9 || cin.fail())
        {
            cout << "**********************************************************" << endl;
            cout << "| ERROR. The number of Zombies cannot be greater than 9. |" << endl;
            cout << "**********************************************************" << endl;
            cout << "Enter number of zombies => ";
            cin >> zombieCount;
        }
        cout << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "|      *       SETTINGS UPDATED.       *        |" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << endl;
        system("PAUSE");
        break;

    case 'n':
        row = 5;
        column = 9;
        zombieCount = 1;
        break;
    }
}

void init(int column, int row)
{
    cout << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "|      #       Launching the game....      #       |" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << endl;
    system("PAUSE");
    system("CLS");

    char objects[] = {'P', 'R', 'H', 'v', '^', '<', '>', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    srand(time(NULL));

    int noOfObjects = 14;
    random_shuffle(objects, objects + noOfObjects);

    map_.resize(row);
    for (int i = 0; i < row; ++i)
    {
        map_[i].resize(column);
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    int m;
    int n;
    m = (column - 1) / 2;
    n = (row - 1) / 2;
    map_[n][m] = 'A';
}

void gameboard()
{
    system("CLS");
    cout << "\033[35m" << " --__--__--__--__--__--__--__--_" << "\033[0m" << endl;
    cout << "\033[35m" << "|                              |" << "\033[0m" << endl;
    cout << "\033[35m" << "=    .: Alien vs Zombie :.     =" << "\033[0m" << endl;
    cout << "\033[35m" << "|                              |" << "\033[0m" << endl;
    cout << "\033[35m" << " __--__--__--__--__--__--__--__-" << "\033[0m" << endl;
    cout << endl;

    for (int i = 0; i < row; ++i)
    {
        cout << "  ";
        for (int j = 0; j < column; ++j)
        {
            cout << "\033[33m" << "+-" << "\033[0m";
        }
        cout << "\033[33m" << "+" << "\033[0m" << endl;
        cout << setw(2) << (i + 1);
        for (int j = 0; j < column; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        cout << "\033[33m" << "+-" << "\033[0m";
    }
    cout << "\033[33m" << "+" << "\033[0m" << endl;
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl;
    cout << endl;
}

void zombie()
{
    vector<gamezombie> zombie;

    zombie.resize(zombieCount);
    for (int i = 0; i < zombieCount; i++)
    {
        zombie[i].name = to_string(i + 1) + "";

        zombie[i].health = rand() % 200;

        zombie[i].attackrange = rand() % 10;

        zombie[i].damage = rand() % 150;
    }

    for (int i = 0; i < zombieCount; ++i)
    {

        int rand1 = rand() % row;

        int rand2 = rand() % column;

        if (map_[rand1][rand2] != to_string(i))
        {
            map_[rand1][rand2] = zombie[i].name;
        }
        else
        {
            i--;
        }
    }
}

int initializeLife()
{
    return MIN_LIFE + rand() % (MAX_LIFE - MIN_LIFE + 1);
}

void attackOpponent(int &opponentLife, int attack)
{
    opponentLife -= attack;
}

int initializeRange(int range)
{
    range = MIN_RANGE + rand() % (MAX_RANGE - MIN_RANGE + 1);
    range = min(range, min(BOARD_WIDTH, BOARD_HEIGHT));
    return range;
}

int initializeAttack()
{
    return MIN_ATTACK + rand() % (MAX_ATTACK - MIN_ATTACK + 1);
}

void zombieAttackOpponent(int &opponentLife, int attack, int range, int x, int y, int opponentX, int opponentY)
{
    if (abs(x - opponentX) <= range && abs(y - opponentY) <= range)
    {
        opponentLife -= attack;
    }
}

void collect()
{
    srand(time(0));

    cout << "\033[36m" << "Alien:" << "\033[0m" << " life = " << aLife << ", attack = " << aAttack << endl;

    for (int i = 0; i < zombieCount; i++)
    {
        cout << "\033[32m" << "Zombie " << (i + 1) << "\033[0m" << ": life = " << zLife << ", attack = " << zAttack << ", range = " << initializeRange(MAX_RANGE) << endl;
    }
}

void resetTrails()
{
    system("CLS");
    gameboard();
    collect();
    cout << endl;
    cout << "--------------------------------------------" << endl;
    cout << "|  Alien's turn ends. The trial is reset.  |" << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            if (map_[i][j] == ".")
            {
                char objects[] = {'P', 'H', 'v', '^', '<', '>', ' ', ' ', ' ', ' ', ' ', ' '};
                int objNo = rand() % 12; // get a random number from 0 to 9
                char newObject = objects[objNo];
                map_[i][j] = string(1, newObject); // replace "." with the new object
            }
        }
    }
}

void moveAlien(int directionX, int directionY)
{
    // Calculate the new position of Alien based on the given direction
    getAlienPos();

    int newAlienX = alienX + directionX;
    int newAlienY = alienY + directionY;
    // when alien hit the border
    if (newAlienX < 0 || newAlienX >= map_[0].size() || newAlienY < 0 || newAlienY >= map_.size())
    {
        cout << endl;
        cout << "Alien Hit Border." << endl;
        cout << endl;
        return;
    }

    if (map_[newAlienY][newAlienX] == "R")
    {
        // Alien hits a rock, replace it with a random object and stop moving
        char objects[] = {'P', 'H', 'v', '^', '<', '>', ' ', ' ', ' ', ' '};
        int objNo = rand() % 10; // get a random number from 0 to 12 (excluding 1 for "R")
        char newObject = objects[objNo];
        map_[newAlienY][newAlienX] = string(1, newObject); // replace "R" with the new object
        cout << endl;
        cout << "Alien Hit a rock!" << endl;
        cout << "Hidden Object Revealed!" << newObject << "." << endl;
        cout << endl;
        system("PAUSE");
        gameboard(); // show the updated board
        return;
    }
    if (map_[newAlienY][newAlienX] == "P")
    {
        // Instantly inflict 10 damage to Zombie
        zLife -= 10;
        cout << endl;
        cout << "Alien finds a pod." << endl;
        cout << "Alien inflicts 10 damage to Zombie." << endl;
    }

    // Check if the new position is occupied by a health object
    if (map_[newAlienY][newAlienX] == "H")
    {
        if (aLife == MAX_LIFE)
        {
            cout << endl;
            cout << "Health is already full!" << endl;
        }
        else
        {
            aLife += 20;
            if (aLife > MAX_LIFE)
            {
                aLife = MAX_LIFE;
            }
            cout << endl;
            cout << "Alien picked up a health object. Alien's health is now " << aLife << endl;
        }
    }
    if (map_[newAlienY][newAlienX] == ">" || map_[newAlienY][newAlienX] == "<" ||
        map_[newAlienY][newAlienX] == "^" || map_[newAlienY][newAlienX] == "v")
    {
        cout << endl;
        cout << "Alien found an arrow" << endl;
        cout << "   Add 20 attack    " << endl;
        aAttack += 20;
    }
    // Check if the new position is a arrow indicating direction change
    if (map_[newAlienY][newAlienX] == "<")
    {

        directionX = -1;
        directionY = 0;
    }
    if (map_[newAlienY][newAlienX] == ">")
    {

        directionX = 1;
        directionY = 0;
    }
    if (map_[newAlienY][newAlienX] == "v")
    {

        directionX = 0;
        directionY = 1;
    }
    if (map_[newAlienY][newAlienX] == "^")
    {

        directionX = 0;
        directionY = -1;
    }
    

    // Check if the new position is occupied by a zombie
    if (map_[newAlienY][newAlienX] == "1" || map_[newAlienY][newAlienX] == "2" || map_[newAlienY][newAlienX] == "3" ||
        map_[newAlienY][newAlienX] == "4" || map_[newAlienY][newAlienX] == "5" || map_[newAlienY][newAlienX] == "6" ||
        map_[newAlienY][newAlienX] == "7" || map_[newAlienY][newAlienX] == "8" || map_[newAlienY][newAlienX] == "9")
    {
        // resetTrails();
        cout << endl;
        cout << "Alien meets zombie." << endl;
        // Calculate the damage inflicted by the alien
        int damage = aAttack; // 

        // Inflict the damage to the zombie
        if (damage > 0)
        {
            map_[newAlienY][newAlienX][0] = map_[newAlienY][newAlienX][0] - damage; // reduce the zombie label by the inflicted damage
            cout << endl;
            cout << "Alien inflicts " << damage << " damage to Zombie " << map_[newAlienY][newAlienX] << "." << endl;
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << "Alien's attack is too weak to inflict any damage to Zombie " << map_[newAlienY][newAlienX] << "." << endl;
            cout << endl;
        }
        return;
    }

    map_[alienY][alienX] = ".";
    map_[newAlienY][newAlienX] = "A";
    alienX = newAlienX;
    alienY = newAlienY;
    cout << endl;
    system("PAUSE");
    gameboard();
    collect();
    moveAlien(directionX, directionY);
}

void switchArrow()
{
    int erow, ecol;
    cout << endl;
    cout << "Enter the row of the arrow object: "; 
    cin >> erow;
    cout << endl;
    cout << "Enter the column of the arrow object: ";
    cin >> ecol;

    if (map_[erow - 1][ecol - 1] != "^" && map_[erow - 1][ecol - 1] != "v" && map_[erow - 1][ecol - 1] != "<" && map_[erow - 1][ecol - 1] != ">")
    {
        cout << endl;
        cout << "This is not an arrow." << endl;
        return;
    }

    string direction;
    cout << endl;
    cout << "Enter the direction to switch the arrow object to (up, down, left, right): ";
    cin >> direction;

    if (direction == "up")
    {
        map_[erow-1][ecol-1] = '^';
    }
    else if (direction == "down")
    {
        map_[erow-1][ecol-1] = 'v';
    }
    else if (direction == "left")
    {
        map_[erow-1][ecol-1] = '<';
    }
    else if (direction == "right")
    {
        map_[erow-1][ecol-1] = '>';
    }
    gameboard();
    collect();
}

void saveMap()
{
    string fileName;
    cout << endl;
    cout << "Enter the file name to save the current game: ";
    getline(cin >> ws, fileName);

    cout << endl;
    cout << "Game saved succesfully !" << endl;
    system("PAUSE");
    gameboard();
    collect();
}

void loadMap()
{
    char choice;
    string fileName;
    cout << endl;
    cout << "Do you want to save the current game? (y/n): ";
    cin >> choice;
    choice = tolower(choice);
    while (choice != 'y' && choice != 'n')
    {
        cout << endl;
        cout << "********************************************" << endl;
        cout << "| ERROR. Only Character (y/n) is Accepted. |" << endl;
        cout << "********************************************" << endl;
        cout << endl;
        cout << "Do you want to save the current game? (y/n): ";
        cin >> choice;
    }

    if (choice == 'y')
    {
        cout << endl;
        cout << "Game saved successfully!" << endl;
    }
    else if (choice == 'n')
    {
        cout << endl;
        cout << "Enter the file name to load: ";
        cin >> fileName;
        cout << endl;
        cout << "Game loaded." << endl;
        cout << endl;
        system("PAUSE");
    }
}

void askCommand()
{
    string command;
    bool loop = true;
    bool quit = false;

    while (loop)
    {
        cout << endl;
        cout << "command (Type help to show list of commands) > ";
        getline(cin >> ws, command);
        system("CLS");
        gameboard();
        collect();
        if (command == "help")
        {
            cout << endl;
            printHelps();
        }
        else if (command == "right")
        {
            moveAlien(1, 0);
            system("PAUSE");
            resetTrails();
        }
        else if (command == "left")
        {
            moveAlien(-1, 0);
            system("PAUSE");
            resetTrails();
        }
        else if (command == "down")
        {
            moveAlien(0, 1);
            system("PAUSE");
            resetTrails();
        }
        else if (command == "up")
        {
            moveAlien(0, -1);
            system("PAUSE");
            resetTrails();
        }
        else if (command == "arrow")
        {
            switchArrow();
        }
        else if (command == "save")
        {
            saveMap();
        }
        else if (command == "load")
        {
            loadMap();
        }
        else if (command == "quit")
        {
            quit = true;
            system("CLS");
            cout << endl;
            cout << " BBBBBB   Y       Y   EEEEEEE   ||  || " << endl;
            cout << " B    BB   Y     Y    E         ||  || " << endl;
            cout << " B    BB    Y   Y     E         ||  || " << endl;
            cout << " BBBBBB      Y Y      EEEEEEE   ||  || " << endl;
            cout << " B    BB      Y       E         ||  || " << endl;
            cout << " B    BB      Y       E         ||  || " << endl;
            cout << " BBBBBB       Y       EEEEEEE   ##  ## " << endl;
            cout << endl;
            system("PAUSE");
            exit(0);
        }
        else
        {
            cout << endl;
            cout << "*************************************" << endl;
            cout << "|          Invalid Command          |" << endl;
            cout << "*************************************" << endl;
        }
    }
}

void printHelps()
{
    cout << "List of available commands: " << endl;
    cout << endl;
    for (int i = 0; i < NUM_COMMANDS; i++)
    {
        cout << commands[i] << endl;
    }
}

int main()
{
    gameDisplay();
    defaultSetting();
    init(column, row);
    zombie();
    gameboard();
    collect();
    askCommand();

    system("pause");
    return 0;
}
