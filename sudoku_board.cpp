#include "sudoku_board.hpp"

SudokuBoard::SudokuBoard(void)
{
	memset(m_board, 0, BOARD_SIZE * sizeof(board_i));
}

SudokuBoard::SudokuBoard(int seed)
{
	memset(m_board, 0, BOARD_SIZE * sizeof(board_i));
	srand(seed);
	make_board(0, 0);
}

SudokuBoard::SudokuBoard(const SudokuBoard& sdk)
{
	memcpy(this->m_board, sdk.m_board, BOARD_SIZE * sizeof(board_i));
}

bool SudokuBoard::check_row(int x, int y) const
{
	if (get(x, y) < 1 || 9 < get(x, y))
		return true;
	for (int i = 0; i < 9; i++) {
		if (i != y && get(x, y) == get(x, i))
			return false;
	}
	return true;
}

bool SudokuBoard::check_colmn(int x, int y) const
{
	if (get(x, y) < 1 || 9 < get(x, y))
		return true;
	for (int i = 0; i < 9; i++) {
		if (i != x && get(x, y) == get(i, y))
			return false;
	}
	return true;
}

bool SudokuBoard::check_box(int x, int y) const
{
	if (get(x, y) < 1 || 9 < get(x, y))
		return true;
	int i_s = (y / 3) * 3;
	int j_s = (x / 3) * 3;
	for (int i = i_s; i < i_s + 3; i++) {
		for (int j = j_s; j < j_s + 3; j++) {
			if (!(i == y && j == x) && get(x, y) == get(j, i))
				return false;
		}
	}
	return true;
}

bool SudokuBoard::make_board(int x, int y) {
	//std::cout << "(" << x << "," << y << ") ";
	if (y == 9)
		return true;
	if (x == 9)
		return make_board(0, y + 1);
	
	int num_list[9] = {1,2,3,4,5,6,7,8,9};
	for (int i = 0; i < 8; i++) std::swap(num_list[i], num_list[i + std::rand() % (8 - i)]); // shuffle
	int t = 0;
	while (t < 9) {
		board(x, y) = num_list[t];
		if (check_row(x, y) && check_colmn(x, y) && check_box(x, y) && make_board(x + 1, y))
			return true;
		t++;
	}
	board(x, y) = 0;
	return false;
}

void print_board(const SudokuBoard& sdk, const std::string& w)
{
	std::cout << w << std::endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << sdk.get(j, i);
			if (j == 2 || j == 5)
				std::cout << "|";
		}
		std::cout << std::endl;
		if (i == 2 || i == 5)
			std::cout << "---+---+---" << std::endl;
	}
}