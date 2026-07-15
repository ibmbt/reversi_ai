#pragma once
#include "board.h"
#include <limits>

class AI {
private:
    static int evaluateBoard(const Board& board, char symbol);
    static int minimax(const Board& board, int depth, int alpha, int beta, bool isMaximizing, char aiSymbol, char oppSymbol);

public:
    static Move getBestMove(const Board& board, char symbol, int depth = 5);
};