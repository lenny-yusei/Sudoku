#include "sudoku_search.hpp"

SudokuSearch::SudokuSearch(const SudokuBoard& sdk)
{
    for (int i = 0; i < SudokuBoard::BOARD_SIZE; i++) {
        putable_num[i] = 0x1FF;
    }
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (sdk.get(x, y) != 0)
                remove_flag(x, y, sdk.get(x, y));
        }
    }
}

SudokuSearch::SudokuSearch(const SudokuSearch& sdks)
{
    for (int i = 0; i < SudokuBoard::BOARD_SIZE; i++) {
        this->putable_num[i] = sdks.putable_num[i];
    }
}

void SudokuSearch::remove_flag(int x, int y, int n)
{
    numflag flag_n = flag_of(n);
    for (int i = 0; i < 9; i++) {
        putable_num[x + 9 * i] &= ~flag_n;
    }
    for (int j = 0; j < 9; j++) {
        putable_num[j + 9 * y] &= ~flag_n;
    }
    for (int i = (y / 3) * 3; i < (y / 3 + 1) * 3; i++) {
        for (int j = (x / 3) * 3; j < (x / 3 + 1) * 3; j++) {
            putable_num[j + 9 * i] &= ~flag_n;
        }
    }
}

uint64_t SudokuSearch::count_answer()
{
    // 次はここから
    return 0;
}