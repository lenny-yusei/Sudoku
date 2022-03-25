#ifndef _SUDOKU_SEARCH_HPP_
#define _SUDOKU_SEARCH_HPP_

#include "sudoku_board.hpp"
#include <bitset>

class SudokuSearch {
    using numflag = std::bitset<9>;
    numflag putable_num[9 * 9];
    void remove_flag(int x, int y, int n);
    inline numflag flag_of(int n) const {
        return numflag(1 << (n - 1));
    }
public:
    SudokuSearch(const SudokuBoard& sdk);
    SudokuSearch(const SudokuSearch& sdks);
    uint64_t count_answer();
    inline numflag get_flag(int x, int y) const {
        return putable_num[x + 9 * y];
    }
};

#endif