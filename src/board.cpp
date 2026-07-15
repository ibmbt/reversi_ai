#include "../inc/board.h"

Board::Board() {
    initialize();
}

void Board::initialize() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = '-';
    grid[3][3] = 'O';
    grid[3][4] = 'X';
    grid[4][3] = 'X';
    grid[4][4] = 'O';
}

void Board::display() const {
    cout << "\n  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
        for (int j = 0; j < 8; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool Board::isValidMove(int r, int c, char symbol) const {
    if (r < 0 || r >= 8 || c < 0 || c >= 8 || grid[r][c] != '-') return false;

    char opponent = (symbol == 'O') ? 'X' : 'O';

    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        bool foundOpponent = false;

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && grid[nr][nc] == opponent) {
            foundOpponent = true;
            nr += dr[i];
            nc += dc[i];
        }

        if (foundOpponent && nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && grid[nr][nc] == symbol) {
            return true;
        }
    }
    return false;
}

void Board::applyMove(int r, int c, char symbol) {
    grid[r][c] = symbol;
    char opponent = (symbol == 'O') ? 'X' : 'O';

    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        bool foundOpponent = false;

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && grid[nr][nc] == opponent) {
            foundOpponent = true;
            nr += dr[i];
            nc += dc[i];
        }

        if (foundOpponent && nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && grid[nr][nc] == symbol) {
            int currR = r + dr[i];
            int currC = c + dc[i];
            while (currR != nr || currC != nc) {
                grid[currR][currC] = symbol;
                currR += dr[i];
                currC += dc[i];
            }
        }
    }
}

vector<Move> Board::getValidMoves(char symbol) const {
    vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValidMove(i, j, symbol)) {
                moves.push_back({ i, j });
            }
        }
    }
    return moves;
}

bool Board::canMakeMove(char symbol) const {
    return !getValidMoves(symbol).empty();
}

bool Board::isGameOver() const {
    return !canMakeMove('O') && !canMakeMove('X');
}

void Board::getScores(int& scoreO, int& scoreX) const {
    scoreO = 0;
    scoreX = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == 'O') scoreO++;
            else if (grid[i][j] == 'X') scoreX++;
        }
    }
}

char Board::getCell(int r, int c) const {
    return grid[r][c];
}

void Board::saveState(int turn) const {
    ofstream fout("../savefile/reversi_save.txt");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fout << grid[i][j];
        }
        fout << "\n";
    }
    fout << turn;
}

bool Board::loadState(int& turn) {
    ifstream fin("../savefile/reversi_save.txt");
    if (!fin) return false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fin >> grid[i][j];
        }
    }
    fin >> turn;
    return true;
}