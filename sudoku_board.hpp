#ifndef _SUDOKU_BOARD_HPP_
#define _SUDOKU_BOARD_HPP_

#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>

class SudokuBoard {
	static const int BOARD_SIZE = 9 * 9;
	using board_i = uint8_t;
	board_i m_board[BOARD_SIZE];
	bool make_board(int x, int y);
	inline board_i& board(int x, int y) {
		return m_board[x + 9 * y];
	}
public:
	SudokuBoard(void);
	SudokuBoard(int seed);
	SudokuBoard(const SudokuBoard& sdk);
	bool check_row(int x, int y) const;
	bool check_colmn(int x, int y) const;
	bool check_box(int x, int y) const;
	inline int get(int x, int y) const {
		return m_board[x + 9 * y];
	}
	inline void put(int x, int y, int n) {
		if (1 <= n && n <= 9) m_board[x + 9 * y] = n;
	}
	inline void del(int x, int y) {
		m_board[x + 9 * y] = 0;
	}
};

void print_board(const SudokuBoard& sdk, const std::string& w);

#endif
