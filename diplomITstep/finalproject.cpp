#include <iostream>
#include <random>
#include <fstream>
using namespace std;

class Card {
public:
    int value; 
};

Card deck[52];

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

void CreateDeck()
{
    int index = 0;

    for (int value = 2; value <= 14; value++) {
        for (int suit = 0; suit < 4; suit++) {
            deck[index].value = value;
            index++;
        }
    }

    random_shuffle(deck, deck + 52);
}

int CardPoints(int value) 
{
    if (value >= 11 && value <= 13) {
        return 10;
    }
    else if (value == 14) {
        return 11;
    }
    else {
        return value;
    }
}



int main()
{
    int a;
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
            break;
        }

    }
}