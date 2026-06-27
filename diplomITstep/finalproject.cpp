#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
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
        cout << "Победы: " << wins << "\n" << endl;
    }
    void AddWin() {
        wins++;
    }
    void ShowStatistics() {
        cout << "Игр сыграно: " << gamesPlayed << endl;

        if (gamesPlayed == 0) {
            cout << "Процент побед: 0%" << endl;
            return;
        }
        else {
            double percent = (double)wins / gamesPlayed * 100;
            cout << "Процент побед: " << percent << "%\n" << endl;
        }
    }
    void AddGamesPlayed() {
        gamesPlayed++;
    }
    string GetName()
    {
        return name;
    }
    int GetWins()
    {
        return wins;
    }
    int GetGamesPlayed() {
        return gamesPlayed;
    }
    void SetName(string n)
    {
        name = n;
    }
    void SetWins(int w)
    {
        wins = w;
    }
    void SetGamesPlayed(int g)
    {
        gamesPlayed = g;
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
    cout << "  1 2 3\n";

    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << " ";

        for (int j = 0; j < 3; j++)
        {
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
        cout << "Введите ряд(1-3): ";
        if (!(cin >> row))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода!\n";
            continue;
        }
        cout << "Введите столбец(1-3): ";
        if (!(cin >> col))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода!\n";
            continue;
        }
        row--;
        col--;

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

        board[r][c] = 'O';
        if (checkWin('O'))
        {
            PrintBoard();
            cout << "Вы проиграли" << endl;
            break;
        }
        else if (IsDraw())
        {
            PrintBoard();
            cout << "Ничья" << endl;
            break;
        }
    }
}


void SaveGame(Player& player)
{
    ofstream playerfile("savePlayer.txt");

    playerfile << player.GetName()  << endl;
    playerfile << player.GetWins() << endl;
    playerfile << player.GetGamesPlayed() << endl;
    cout << "Данные игрока сохранены\n" << endl;

    playerfile.close();

    ofstream gamefile("saveGame.txt");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gamefile << board[i][j] << " ";
        }
        gamefile << endl;
    }

    gamefile.close();
    cout<<"Игра сохранена" << endl;
}

bool LoadGame(Player& player)
{
    string name;
    int games;
    int wins;

    ifstream playerfile("savePlayer.txt");
    if (!playerfile.is_open())
    {
        cout << "Сохранение игры не найдено!\n";
        return false;
    }
    getline(playerfile, name);
    playerfile >> wins;
    playerfile >> games;


    player.SetName(name);
    player.SetWins(wins);
    player.SetGamesPlayed(games);
    playerfile.close();

    player.ShowInfo();
    cout << "Данные игрока загружены\n" << endl;

    ifstream gamefile("saveGame.txt");

    if (!gamefile.is_open())
    {
        cout << "Сохранение игры не найдено!\n";
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gamefile >> board[i][j];
        }
    }

    gamefile.close();
    cout << "Последняя игра: \n" << endl;
    PrintBoard();
    return true;
}

int main()
{
    setlocale(0, "rus");
    srand((unsigned int)time(0));
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
        cout << "4. Сохранить данные" << endl;
        cout << "5. Загрузить данные" << endl;
        cout << "6. выход" << endl;
        cout << "Ваш выбор: ";
        cout << endl;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода\n";
            continue;
        }
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
            LoadGame(player);
            break;
        case 6:
            return 0;
        default:
            cout << "Ошибка ввода\n"<< endl;
            break;
        }
    }
}