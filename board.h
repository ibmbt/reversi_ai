#pragma once
#include <vector>
#include <iostream>
#include <fstream>

struct Move {
    int r, c;
};

class Board {
private:
    char grid[8][8];
    const int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

public:
    Board();
    void initialize();
    void display() const;
    bool isValidMove(int r, int c, char symbol) const;
    void applyMove(int r, int c, char symbol);
    bool canMakeMove(char symbol) const;
    vector<Move> getValidMoves(char symbol) const;
    bool isGameOver() const;
    void getScores(int& scoreO, int& scoreX) const;
    char getCell(int r, int c) const;
    void saveState(int turn) const;
    bool loadState(int& turn);
};