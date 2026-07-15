#include "../inc/ai.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int AI::evaluateBoard(const Board& board, char symbol) {
    int score = 0;
    char opponent;
    if (symbol == 'O') {
        opponent = 'X';
    }
    else {
        opponent = 'O';
    }

    const int weights[8][8] = {
        {100, -20, 10,  5,  5, 10, -20, 100},
        {-20, -50, -2, -2, -2, -2, -50, -20},
        { 10,  -2, -1, -1, -1, -1,  -2,  10},
        {  5,  -2, -1, -1, -1, -1,  -2,   5},
        {  5,  -2, -1, -1, -1, -1,  -2,   5},
        { 10,  -2, -1, -1, -1, -1,  -2,  10},
        {-20, -50, -2, -2, -2, -2, -50, -20},
        {100, -20, 10,  5,  5, 10, -20, 100}
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getCell(i, j) == symbol) {
                score += weights[i][j];
            }
            else if (board.getCell(i, j) == opponent) {
                score -= weights[i][j];
            }
        }
    }
    return score;
}

int AI::minimax(const Board& board, int depth, int alpha, int beta, bool isMaximizing, char aiSymbol, char oppSymbol) {
    if (depth == 0 || board.isGameOver()) {
        return evaluateBoard(board, aiSymbol);
    }

    char currentTurn = isMaximizing ? aiSymbol : oppSymbol;
    vector<Move> validMoves = board.getValidMoves(currentTurn);

    if (validMoves.empty()) {
        return minimax(board, depth - 1, alpha, beta, !isMaximizing, aiSymbol, oppSymbol);
    }

    if (isMaximizing) {
        int maxEval = -100000;
        for (const Move& m : validMoves) {
            Board tempBoard = board;
            tempBoard.applyMove(m.r, m.c, currentTurn);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, false, aiSymbol, oppSymbol);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = 100000;
        for (const Move& m : validMoves) {
            Board tempBoard = board;
            tempBoard.applyMove(m.r, m.c, currentTurn);
            int eval = minimax(tempBoard, depth - 1, alpha, beta, true, aiSymbol, oppSymbol);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

Move AI::getBestMove(const Board& board, char symbol, int depth) {
    vector<Move> validMoves = board.getValidMoves(symbol);
    char oppSymbol;
    if (symbol == 'O') {
        oppSymbol = 'X';
    }
    else {
        oppSymbol = 'O';
    }

    Move bestMove = { -1, -1 };
    int bestValue = -100000;

    for (const Move& m : validMoves) {
        Board tempBoard = board;
        tempBoard.applyMove(m.r, m.c, symbol);

        int moveValue = minimax(tempBoard, depth - 1, -100000, 100000, false, symbol, oppSymbol);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = m;
        }
    }
    return bestMove;
}