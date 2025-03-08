#include <iostream>
#include <fstream>
using namespace std;

const int ROWS = 8;
const int COLS = 8;
char BOARD[ROWS][COLS];

void initialize_board(int& turn);
void display_board();
void display_score();
bool valid_move(int r, int c, char symbol);
bool can_make_move(char symbol);
void flip_diagonal(int r, int c, char symbol);
void flip_straight(int r, int c, char symbol);
void flip(int r, int c, char symbol);
void move(int r, int c, char symbol);
void ai_move(char symbol);
void resume_board(int& turn);
void print_to_file(int& turn);
bool draw();
bool win(char symbol);
bool game_over();
void turn_change(int& turn);
void replay(char& choice);
bool all_filled();
void print_winner();

int main()
{
	char repeat = 'Y';
	int r = 0, c = 0;
	char choice;
	char resume, undo;
	while (repeat == 'Y' || repeat == 'y')
	{
		cout << "\n===|REVERSI|===\n"
			<< endl;
		cout << "\n[1] VS AI" << endl;
		cout << "[2] VS PLAYER 2\n"
			<< endl;
		cin >> choice;
		if (choice == '1')
		{

			int turn = 0;
			char symbol = 'O';
			cout << "\t\t   ===|REVERSI|===\n"
				<< endl;
			cout << "[N] NEW GAME" << endl;
			cout << "[C] CONTINUE\n\n" << endl;
			cin >> resume;
			cout << endl;
			if (resume == 'C') {

				resume_board(turn);

			}
			else if (resume == 'N') {

				initialize_board(turn);
			}

			display_board();

			while (!all_filled())
			{
				if (game_over())
				{
					cout << "NO MOVES POSSIBLE! GAME OVER" << endl;
					print_winner();
					break;
				}

				if (turn == 0)
				{
					symbol = 'O';
					if (can_make_move(symbol))
					{
						do
						{
							cin >> r >> c;
							if (!(valid_move(r, c, symbol)))
							{
								cout << "INVALID MOVE, SELECT ANOTHER CELL." << endl;
							}
						} while (!(valid_move(r, c, symbol)));

						move(r, c, symbol);
						flip(r, c, symbol);
						cout << "\nPLAYER 1 TOOK THE TURN.\n\n";
					}
				}

				else if (turn == 1)
				{
					symbol = 'X';
					if (can_make_move(symbol))
					{
						ai_move(symbol);
						cout << "AI TOOK THE TURN.\n\n";
					}
				}

				turn_change(turn);
				display_score();
				display_board();
				print_to_file(turn);

				if (all_filled())
				{
					if (draw())
					{
						cout << "\nGAME ENDED IN A DRAW!\n"
							<< endl;
						break;
					}
					else if (win(symbol))
					{
						if (turn == 0)
							cout << "\nPLAYER 1 WINS!\n"
							<< endl;
						if (turn == 1)
							cout << "\nAI WINS!\n"
							<< endl;
						break;
					}
					else
					{
						if (turn == 0)
							cout << "\nAI WINS!\n"
							<< endl;
						if (turn == 1)
							cout << "\nPLAYER 1 WINS!\n"
							<< endl;
						break;
					}
				}

				cout << endl;
				cout << endl;
			}
		}
		else if (choice == '2')
		{
			int turn = 0;
			char symbol = 'O';
			cout << "\t\t   ===|REVERSI|===\n"
				<< endl;
			cout << "[N] NEW GAME" << endl;
			cout << "[C] CONTINUE\n\n" << endl;
			cin >> resume;
			cout << endl;
			if (resume == 'C') {

				resume_board(turn);

			}
			else if (resume == 'N') {

				initialize_board(turn);
			}

			display_board();

			while (!all_filled())
			{
				if (game_over())
				{
					cout << "NO MOVES POSSIBLE! GAME OVER" << endl;
					print_winner();
					break;
				}

				if (turn == 0)
				{
					symbol = 'O';
					if (can_make_move(symbol))
					{
						do
						{
							cin >> r >> c;
							if (!(valid_move(r, c, symbol)))
							{
								cout << "INVALID MOVE, SELECT ANOTHER CELL." << endl;
							}
						} while (!(valid_move(r, c, symbol)));

						move(r, c, symbol);
						flip(r, c, symbol);
						cout << "\nPLAYER 1 TOOK THE TURN.\n\n";
					}
				}

				else if (turn == 1)
				{
					symbol = 'X';
					if (can_make_move(symbol))
					{
						do
						{
							cin >> r >> c;
							if (!(valid_move(r, c, symbol)))
							{
								cout << "INVALID MOVE, SELECT ANOTHER CELL." << endl;
							}
						} while (!(valid_move(r, c, symbol)));

						move(r, c, symbol);
						flip(r, c, symbol);
						cout << "\nPLAYER 2 TOOK THE TURN.\n\n";
					}
				}

				turn_change(turn);
				display_score();
				display_board();
				print_to_file(turn);

				if (all_filled())
				{
					if (draw())
					{
						cout << "\nGAME ENDED IN A DRAW!\n"
							<< endl;
						break;
					}
					else if (win(symbol))
					{
						if (turn == 0)
							cout << "\nPLAYER 1 WINS!\n"
							<< endl;
						if (turn == 1)
							cout << "\nPLAYER 2 WINS!\n"
							<< endl;
						break;
					}
					else
					{
						if (turn == 0)
							cout << "\nPLAYER 2 WINS!\n"
							<< endl;
						if (turn == 1)
							cout << "\nPLAYER 1 WINS!\n"
							<< endl;
						break;
					}
				}



				cout << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "INVALID ENTRY" << endl;
		}

		replay(repeat);
		if ((repeat != 'y') && (repeat != 'Y'))
			cout << "THANK YOU FOR PLAYING.." << endl;
	}
	return 0;
}


void initialize_board(int& turn)
{
	ifstream fin("reversi.txt");

	if (fin) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				fin >> BOARD[i][j];
			}
		}
		fin >> turn;
	}
	else {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				BOARD[i][j] = '-';
			}
		}
		BOARD[3][3] = 'O';
		BOARD[3][4] = 'X';
		BOARD[4][3] = 'X';
		BOARD[4][4] = 'O';
	}
	fin.close();
}

void display_board()
{
	for (int i = 0; i < ROWS; i++)
	{
		cout << i << " ";
		cout << "|";
		for (int j = 0; j < COLS; j++)
		{
			if (j == 0)
			{
				cout << "  ";
			}
			cout << BOARD[i][j];
			if (j < COLS - 1)
			{
				cout << "  |  ";
			}
		}
		cout << endl;
		if (i < ROWS - 1)
			cout << "    ----------------------------------------------" << endl;
	}
	cout << "    ----------------------------------------------" << endl;
	cout << "     0  |  1  |  2  |  3  |  4  |  5  |  6  |  7   " << endl;
}

void display_score()
{
	int score1 = 0, score2 = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (BOARD[i][j] == 'O')
			{
				score1++;
			}
			else if (BOARD[i][j] == 'X')
			{
				score2++;
			}
		}
	}
	cout << "\nSCORE O:\t" << score1 << endl;
	cout << "\nSCORE X:\t" << score2 << "\n\n"
		<< endl;
}

bool valid_move(int r, int c, char symbol)
{
	if (r < 0 || r >= ROWS || c < 0 || c >= COLS || BOARD[r][c] != '-')
	{
		return false;
	}

	char opponent;
	if (symbol == 'O')
	{
		opponent = 'X';
	}
	else
	{
		opponent = 'O';
	}

	// [-1, -1]
	int i = r - 1, j = c - 1;
	bool opp_symbol = false;
	while (i >= 0 && j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i--;
		j--;
	}

	// [-1, 0]
	i = r - 1;
	j = c;
	opp_symbol = false;
	while (i >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i--;
	}

	// [-1, 1]
	i = r - 1;
	j = c + 1;
	opp_symbol = false;
	while (i >= 0 && j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i--;
		j++;
	}

	// [0, -1]
	i = r;
	j = c - 1;
	opp_symbol = false;
	while (j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		j--;
	}

	// [0, 1]

	i = r;
	j = c + 1;
	opp_symbol = false;
	while (j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		j++;
	}

	// [1, -1]
	i = r + 1;
	j = c - 1;
	opp_symbol = false;
	while (i < ROWS && j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i++;
		j--;
	}

	// [1, 0]
	i = r + 1;
	j = c;
	opp_symbol = false;
	while (i < ROWS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i++;
	}

	// [1, 1]
	i = r + 1;
	j = c + 1;
	opp_symbol = false;
	while (i < ROWS && j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			return true;
		}
		else
		{
			break;
		}
		i++;
		j++;
	}

	return false;
}

bool can_make_move(char symbol)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (valid_move(i, j, symbol))
			{
				return true;
			}
		}
	}
	return false;
}

void flip_diagonal(int r, int c, char symbol)
{

	char opponent;
	if (symbol == 'O')
	{
		opponent = 'X';
	}
	else
	{
		opponent = 'O';
	}

	int i = r - 1, j = c - 1;
	bool opp_symbol = false;
	while (i >= 0 && j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{

			int x = r - 1, y = c - 1;
			while (x > i && y > j)
			{
				BOARD[x][y] = symbol;
				x--;
				y--;
			}
			break;
		}
		else
		{
			break;
		}
		i--;
		j--;
	}

	i = r - 1;
	j = c + 1;
	opp_symbol = false;
	while (i >= 0 && j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int x = r - 1, y = c + 1;
			while (x > i && y < j)
			{
				BOARD[x][y] = symbol;
				x--;
				y++;
			}
			break;
		}
		else
		{
			break;
		}
		i--;
		j++;
	}

	i = r + 1;
	j = c - 1;
	opp_symbol = false;
	while (i < ROWS && j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int x = r + 1, y = c - 1;
			while (x < i && y > j)
			{
				BOARD[x][y] = symbol;
				x++;
				y--;
			}
			break;
		}
		else
		{
			break;
		}
		i++;
		j--;
	}

	i = r + 1;
	j = c + 1;
	opp_symbol = false;
	while (i < ROWS && j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int x = r + 1, y = c + 1;
			while (x < i && y < j)
			{
				BOARD[x][y] = symbol;
				x++;
				y++;
			}
			break;
		}
		else
		{
			break;
		}
		i++;
		j++;
	}
}

void flip_straight(int r, int c, char symbol)
{

	char opponent;
	if (symbol == 'O')
	{
		opponent = 'X';
	}
	else
	{
		opponent = 'O';
	}

	int i = r, j = c - 1;
	bool opp_symbol = false;
	while (j >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int y = c - 1;
			while (y > j)
			{
				BOARD[i][y] = symbol;
				y--;
			}
			break;
		}
		else
		{
			break;
		}
		j--;
	}

	i = r;
	j = c + 1;
	opp_symbol = false;
	while (j < COLS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int y = c + 1;
			while (y < j)
			{
				BOARD[i][y] = symbol;
				y++;
			}
			break;
		}
		else
		{
			break;
		}
		j++;
	}

	i = r - 1;
	j = c;
	opp_symbol = false;
	while (i >= 0)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int x = r - 1;
			while (x > i)
			{
				BOARD[x][j] = symbol;
				x--;
			}
			break;
		}
		else
		{
			break;
		}
		i--;
	}

	i = r + 1;
	j = c;
	opp_symbol = false;
	while (i < ROWS)
	{
		if (BOARD[i][j] == opponent)
		{
			opp_symbol = true;
		}
		else if (BOARD[i][j] == symbol && opp_symbol)
		{
			int x = r + 1;
			while (x < i)
			{
				BOARD[x][j] = symbol;
				x++;
			}
			break;
		}
		else
		{
			break;
		}
		i++;
	}
}

void flip(int r, int c, char symbol)
{

	flip_straight(r, c, symbol);
	flip_diagonal(r, c, symbol);
}

void move(int r, int c, char symbol)
{
	BOARD[r][c] = symbol;
}

bool draw()
{
	int count_O = 0, count_X = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (BOARD[i][j] == 'O')
				count_O++;
			else if (BOARD[i][j] == 'X')
				count_X++;
		}
	}
	return count_O == count_X;
}

bool win(char symbol)
{
	int ct = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (BOARD[i][j] == symbol)
			{
				ct++;
			}
		}
	}

	return ct > ((ROWS * COLS) / 2);
}

void turn_change(int& turn)
{
	turn++;
	turn = turn % 2;
}

bool all_filled()
{

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (BOARD[i][j] == '-')
			{
				return false;
			}
		}
	}
	return true;
}

void ai_move(char symbol)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (valid_move(i, j, symbol))
			{
				move(i, j, symbol);
				flip(i, j, symbol);
				return;
			}
		}
	}
}

void print_to_file(int& turn) {

	ofstream fout("resume.txt");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			fout << BOARD[i][j];
		}
		fout << endl;
	}
	fout << turn;
	fout.close();
}

void resume_board(int& turn) {

	ifstream fin("resume.txt");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			fin >> BOARD[i][j];
		}
	}
	fin >> turn;
	fin.close();
}


void print_winner()
{

	int score1 = 0, score2 = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (BOARD[i][j] == 'O')
			{
				score1++;
			}
			else if (BOARD[i][j] == 'X')
			{
				score2++;
			}
		}
	}

	if (score1 > score2)
	{
		cout << "O WINS" << endl;
	}
	else if (score2 > score1)
	{
		cout << "X WINS" << endl;
	}
	else
	{
		cout << "DRAW!!!" << endl;
	}
}

void replay(char& choice)
{
	cout << "DO YOU WANT TO PLAY AGAIN? (Y/N):" << endl;
	cin >> choice;
}

bool game_over()
{
	if ((!can_make_move('O')) && (!can_make_move('X')))
	{
		return true;
	}
	else
	{
		return false;
	}
}