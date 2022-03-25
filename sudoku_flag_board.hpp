#ifndef _SUDOKU_FLAG_BOARD_HPP_
#define _SUDOKU_FLAG_BOARD_HPP_

#include "sudoku_board.hpp"
#include <bitset>

using numflag = std::bitset<9>;

class SudokuFlagBoard : public SudokuBoard
{
    numflag flag_row[9];
    numflag flag_col[9];
    numflag flag_box[9];
    inline numflag flag_of(int n) const {
        return (1 <= n && n <= 9) ? (0x1 << (n - 1)) : 0x0;
    }
    void set_flag(int n, numflag& flg) {
        flg |= flag_of(n);
    }
    void remove_flag(int n, numflag& flg) {
        flg &= ~flag_of(n);
    }
    void init();
public:
	SudokuFlagBoard(void);
	SudokuFlagBoard(int seed);
	SudokuFlagBoard(const SudokuBoard& sdk);
    void put(int x, int y, int n);
    void del(int x, int y);
    inline numflag get_flag_row(int y) const {
        return flag_row[y];
    }
    inline numflag get_flag_col(int x) const {
        return flag_col[x];
    }
    inline numflag get_flag_box(int x, int y) const {
        return flag_box[(x / 3) + 3 * (y / 3)];
    }
    inline numflag get_flag_at(int x, int y) const {
        return (get(x, y) == 0) ? get_flag_row(y) & get_flag_col(x) & get_flag_box(x, y) : 0x000;
    }
};

uint64_t count_answer(SudokuFlagBoard&);

#endif