#include "../inc/board.h"
#include "../inc/ai.h"
#include <iostream>
using namespace std;

void playGame(bool againstAI) {
    Board board;
    int turn = 0;
    char choice;

    cout << "[N] New Game\n[C] Continue\nChoice: ";
    cin >> choice;
    if (choice == 'C' || choice == 'c') {
        if (!board.loadState(turn)) {
            cout << "Failed to load state. Starting new game.\n";
            board.initialize();
        }
    }

    while (!board.isGameOver()) {
        board.display();

        char currentSymbol;
        if (turn == 0) {
            currentSymbol = 'O';
        }
        else {
            currentSymbol = 'X';
        }

        if (!board.canMakeMove(currentSymbol)) {
            cout << currentSymbol << " has no valid moves. Skipping turn.\n";
            turn = 1 - turn;
            continue;
        }

        if (againstAI && turn == 1) {
            cout << "AI is thinking...\n";
            Move aiMove = AI::getBestMove(board, 'X', 6);
            board.applyMove(aiMove.r, aiMove.c, 'X');
            cout << "AI placed at " << aiMove.r << " " << aiMove.c << "\n";
        }
        else {
            int r, c;
            while (true) {
                cout << "Player " << currentSymbol << " move (row col) or '-1 -1' to save & quit: ";
                cin >> r >> c;

                if (r == -1 && c == -1) {
                    cout << "Saving game and exiting...\n";
                    board.saveState(turn);
                    return;
                }

                if (board.isValidMove(r, c, currentSymbol)) {
                    board.applyMove(r, c, currentSymbol);
                    break;
                }
                cout << "Invalid move. Try again.\n";
            }
        }

        turn = 1 - turn;
        board.saveState(turn);

        int scoreO, scoreX;
        board.getScores(scoreO, scoreX);
        cout << "Score -> O: " << scoreO << " | X: " << scoreX << "\n";
    }

    board.display();
    int scoreO, scoreX;
    board.getScores(scoreO, scoreX);
    if (scoreO > scoreX)    cout << "Player O wins!\n";
    else if (scoreX > scoreO)    cout << "Player X wins!\n";
    else    cout << "Draw!\n";
}

int main() {
    while (true) {
        cout << "\n=== REVERSI ===\n"
            << "[1] VS AI\n"
            << "[2] VS Player 2\n"
            << "[3] Quit\n"
            << "Choice: ";

        char choice;
        cin >> choice;

        if (choice == '1') {
            playGame(true);
        }
        else if (choice == '2') {
            playGame(false);
        }
        else if (choice == '3' || choice == 'q' || choice == 'Q') {
            cout << "Exiting game. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}