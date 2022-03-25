#include <iostream>
#include "sudoku_board.hpp"
#include "sudoku_flag_board.hpp"
#include <omp.h>

int main(void) {
	SudokuBoard sudoku(101);
	print_board(sudoku, "");
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			sudoku.del(j, i);
		}
	}
	print_board(sudoku, "del");
	sudoku.put(0, 0, 1);
	print_board(sudoku, "put at (0,0) 1");

	SudokuFlagBoard sdkf(sudoku);
	//sdkf.put(0, 0, 1);
	//print_board(sdkf, "put at (0,0) 1");
	
	for (int i = 0; i < 9; i++) {
		for (int j = 2; j < 7; j++) {
			sdkf.del(j, i);
		}
	}
	print_board(sdkf, "del");
	
	//td::cout << sdkf.get(0, 3) << std::endl;
	
	std::cout << count_answer(sdkf) << std::endl;

	/*
	SudokuFlagBoard sdkf2;
	for (int i = 0; i < 8; i++) {
		sdkf2.put(i, 0, i + 1);
	}
	print_board(sdkf2, "new board");

	std::cout << count_answer(sdkf2) << std::endl;
	*/

	std::cout << omp_get_max_threads() << std::endl;

	return 0;
}

