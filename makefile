OBJS=		sudoku.o sudoku_board.o sudoku_flag_board.o
CMD=		sudoku.exe

CFLAGS+=		-Wall -Wextra -fopenmp
CC=			g++

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

sudoku.o: sudoku.cpp
	$(CC) $(CFLAGS) -c sudoku.cpp -o sudoku.o

sudoku_board.o: sudoku_board.cpp
	$(CC) $(CFLAGS) -c sudoku_board.cpp -o sudoku_board.o

sudoku_flag_board.o: sudoku_flag_board.cpp
	$(CC) $(CFLAGS) -c sudoku_flag_board.cpp -o sudoku_flag_board.o

clean:
	del -f "$(CMD)"
	del -f *.o
