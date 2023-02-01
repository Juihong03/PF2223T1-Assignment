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
using namespace std;

const int MIN_DIMENSION = 3;
int row = 5;
int column = 9;
int zombieCount = 1;
vector<vector<string>> map_;
// int column = 13 , row = 17;

struct gamezombie
{
    string name;
    int attackrange;
    int damage;
    int health;
};

void defaultSetting()
{
    cout << " ------------------------- " << endl;
    cout << "|  Default Game Settings  |" << endl;
    cout << "|-------------------------|" << endl;
    cout << "|  Board Rows       :  " << row << "  |" << endl;
    cout << "|  Board Columns    :  " << column << "  |" << endl;
    cout << "|  Zombie Count     :  " << zombieCount << "  |" << endl;
    cout << " ------------------------- " << endl << endl;

    cout << "Do you wish to change the game setting (y/n) ? => ";

    char choice;
    cin >> choice;
    choice = tolower(choice);
    while (choice != 'y' && choice != 'n')
    {
        cout << "********************************************" << endl;
        cout << "| ERROR. Only Character (y/n) is Accepted. |" << endl;
        cout << "********************************************" << endl << endl;
        cout << "Do you wish to change the game setting (y/n) ? => ";
        cin >> choice;
    }

    system("CLS");
    switch (choice)
    {
    case 'y':
        cout << "------------------" << endl;
        cout << "| Board Settings |" << endl;
        cout << "------------------" << endl << endl;
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

        cout << "-------------------" << endl;
        cout << "| Zombie Settings |" << endl;
        cout << "-------------------" << endl << endl;
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
        cout << "---------------------" << endl;
        cout << "| SETTINGS UPDATED. |" << endl;
        cout << "---------------------" << endl << endl;
        system("PAUSE");
        break;

    case 'n':
        row = 5;
        column = 9;
        zombieCount = 1;
        break;
    }
    // cout << choice;
}

void init(int column, int row)
{

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(row); // create empty rows 
    for (int i = 0; i < row; ++i)
    {
        map_[i].resize(column); // resize each row
    }
    // put random characters into the vector array
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
    cout << " --__--__--__--__--__--__--__--_" << endl;
    cout << "|                              |" << endl;
    cout << "=    .: Alien vs Zombie :.     =" << endl;
    cout << "|                              |" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl << endl;

    // for each row
    for (int i = 0; i < row; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < column; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (i + 1);
        // display cell content and border of each column
        for (int j = 0; j < column; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < column; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
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
    for (int j = 0; j < column; ++j) // j== 0..14
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl << endl;
}

void zombie()
{
    vector<gamezombie> zombie;

    // int zombieamount;
    // cout << "How many zombies do you want?";
    // cin >> zombieamount;
    zombie.resize(zombieCount);
    for (int i = 0; i < zombieCount; i++)
    {
        zombie[i].name = to_string(i+1) + "";

        zombie[i].health = rand() % 200;

        zombie[i].attackrange = rand() % 10;

        zombie[i].damage = rand() % 150;
    }

    for (int i = 0; i < zombieCount; ++i)
    {

        int rand1 = rand() % row;

        int rand2 = rand() % column;


        if (map_[rand1][rand2] !=  to_string(i))
        {
            map_[rand1][rand2] = zombie[i].name;
        }
        else
        {
            i--;
        }
    }
}

int main()
{
    defaultSetting();
    init(column, row);
    zombie();
    gameboard();
    system("pause");

    return 0;
}
