#include <iostream>
#include <random>
#include <fstream>
using namespace std;

char board[3][3];

class Player {
protected:
    string name;
    int chips;
    int wins;

public:
    Player(string name, int chips = 1000, int wins = 0) {
        this->name = name;
        this->chips = chips;
        this->wins = wins;
    }
    void ShowInfo() {
        cout << "Name: " << name << endl;
        cout << "Chips: " << chips << endl;
        cout << "Wins: " << wins << endl;
    }
    void AddWin() {
        wins++;
    }

    void AddChips(int amount) {
        chips += amount;
    }

    void RemoveChips(int amount) {
        chips -= amount;
    }

    int CountChips() {
        return chips;
    }
};

void PrintBoard()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkWin(char p) {
    // Строки
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == p &&
            board[i][1] == p &&
            board[i][2] == p)
            return true;
    }

    // Столбцы
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == p &&
            board[1][j] == p &&
            board[2][j] == p)
            return true;
    }

    // Диагонали
    if (board[0][0] == p &&
        board[1][1] == p &&
        board[2][2] == p)
        return true;

    if (board[0][2] == p &&
        board[1][1] == p &&
        board[2][0] == p)
        return true;

    return false;
}

void play(Player& player)
{


}

int main()
{
    int choice;
    string  name;

    cout << "Enter your name: ";
    cin >> name;
    Player player(name);


    while (true) {
        cout << "Menu" << endl;
        cout << "1. Start new game" << endl;
        cout << "2. Show player info" << endl;
        cout << "3. Statitcs" << endl;
        cout << "4. Save game" << endl;
        cout << "5. exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            PrintBoard();
            break;
        case 2:
            player.ShowInfo();
            break;
        }
    }
}