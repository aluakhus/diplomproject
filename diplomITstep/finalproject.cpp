#include <iostream>
#include <fstream>

using namespace std;

char board[3][3];

class Player {
protected:
    string name;
    int wins;
    int gamesPlayed;

public:
    Player(string name, int wins = 0, int gamesPlayed = 0) {
        this->name = name;
        this->wins = wins;
        this->gamesPlayed = gamesPlayed;
    }
    void ShowInfo() {
        cout << "Имя: " << name << endl;
        cout << "Победы: " << wins << endl;
    }
    void AddWin() {
        wins++;
    }
    void ShowStatistics() {
        double percent = (double)wins / gamesPlayed * 100;
        cout << "Процент побед: "<< percent<< "%\n";
    }
    void AddGamesPlayed() {
        gamesPlayed++;
    }
};

void InitBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '-';
        }
    }
}

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
            board[i][2] == p) {
            return true;
        }
    }

    // Столбцы
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == p &&
            board[1][j] == p &&
            board[2][j] == p) {
            return true;
        }
    }

    // Диагонали
    if (board[0][0] == p &&
        board[1][1] == p &&
        board[2][2] == p){
        return true;
        }

    if (board[0][2] == p &&
        board[1][1] == p &&
        board[2][0] == p) {
        return true;
    }
    return false;
}

bool IsDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
                return false;
        }
    }
    return true;
}


void play(Player& player)
{
    InitBoard();

    while (true) 
    {
        PrintBoard();

        int row, col;
        cout << "Ваш ход" << endl;
        cout << "Введите ряд(0-2): ";
        cin >> row;
        cout << "Введите столбец(0-2): ";
        cin >> col;

        if (row < 0 || row > 2 || col < 0 || col> 2 ||
            board[row][col] != '-')
        {
            cout << "Неправильный ход" << endl;
            continue;

        }
        board[row][col] = 'X';

        if (checkWin('X'))
        {
            PrintBoard();
            cout << "Вы выиграли" << endl;
            player.AddWin();
            break;
        }
        else if (IsDraw())
        {
            PrintBoard();
            cout << "Ничья" << endl;
            break;
        }

        int r, c;

        do {
            r = rand() % 3;
            c = rand() % 3;
        }
        while (board[r][c] != '-');

        board[r][c] = '0';
        if (checkWin('0'))
        {
            PrintBoard();
            cout << "Вы проиграли" << endl;
            break;
        }
    }
}

void SaveGame(Player& player)
{
    ofstream file("saves.txt");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            file << board[i][j] << " ";
        }
        file << endl;
    }

    file.close();
    cout << "Игра сохранена/n" << endl;
}

bool LoadGame()
{
    ifstream file("saves.txt", ios:: app);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            file >> board[i][j];
        }
    }

    file.close();
    cout << "Игра загружена\n" << endl;
    PrintBoard();
    return true;
}

int main()
{
    setlocale(0,"rus");
    int choice;
    string  name;

    cout << "Введите ваше имя: ";
    cin >> name;
    Player player(name);


    while (true) {
        cout << "----Меню----" << endl;
        cout << "1. Начать новую игру" << endl;
        cout << "2. Показать инфо игрока" << endl;
        cout << "3. Статистика" << endl;
        cout << "4. Сохранить игру" << endl;
        cout << "5. Загрузить игру" << endl;
        cout << "6. выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice) {
        case 1:
            play(player);
            player.AddGamesPlayed();
            break;
        case 2:
            player.ShowInfo();
            break;
        case 3:
            player.ShowStatistics();
            break;
        case 4:
            SaveGame(player);
            break;
        case 5:
            LoadGame();
            break;
        case 6:
            return 0;
        }
    }
}