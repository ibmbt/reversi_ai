# Reversi AI (C++)

A professional, object-oriented implementation of the classic board game Reversi (Othello) in C++. This project features a robust AI opponent powered by the Minimax algorithm with Alpha-Beta pruning and positional weight evaluation.

## Features

* **Minimax AI:** Intelligent opponent using Alpha-Beta pruning for highly efficient decision-making (Depth 6).
* **Positional Evaluation:** The AI heavily prioritizes capturing high-value corners while avoiding adjacent edge traps.
* **Game Modes:** Play single-player against the AI or local multiplayer against a second player.
* **State Management:** Game progress is automatically serialized to a local file, allowing you to pause and resume later.
* **Clean Architecture:** Fully encapsulated logic separating the board state, AI calculations, and the main game loop.

## Project Structure

```text
reversi_ai/
├── Makefile                  # Build instructions
├── inc/
│   ├── ai.h                  # AI class definitions
│   └── board.h               # Board class definitions
├── savefile/
│   └── reversi_save.txt      # Game state serialization
└── src/
    ├── ai.cpp                # Minimax and evaluation logic
    ├── board.cpp             # Game mechanics and move validation
    └── main.cpp              # Game loop and user I/O
```

## Compilation & Execution

This project utilizes a `Makefile` for streamlined building. Ensure you have the GCC compiler (`g++`) installed on your Linux environment.

### 1. Build and Run
The fastest way to compile the source code and immediately launch the game in the terminal:
```bash
make run
```

### 2. Manual Build
If you only want to compile the project into an executable:
```bash
make
```
Then execute it manually:
```bash
./reversi
```

### 3. Clean Environment
To wipe the compiled `.o` object files and the executable to keep your directory clean:
```bash
make clean
```

## Gameplay Instructions

1. Launch the executable and select your game mode (`[1] VS AI` or `[2] VS Player 2`).
2. Choose to start a `[N] New Game` or `[C] Continue` from your previous saved state.
3. When prompted, enter your moves as row and column coordinates separated by a space (e.g., `2 3`).
4. The engine will automatically validate the move, place your piece, and flip the appropriate opposing tiles.
5. The game ends when neither player can make a valid move. The player with the highest piece count wins.