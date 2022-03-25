#include "sudoku_flag_board.hpp"
#include <vector>
#include <array>
#include <algorithm>
#include <omp.h>

SudokuFlagBoard::SudokuFlagBoard(void) : SudokuBoard()
{
    init();
}

SudokuFlagBoard::SudokuFlagBoard(int seed) : SudokuBoard(seed)
{
    init();
}

SudokuFlagBoard::SudokuFlagBoard(const SudokuBoard& sdk) : SudokuBoard(sdk)
{
    init();
}

void SudokuFlagBoard::init()
{
    for (int t = 0; t < 9; t++) {
        flag_row[t] = 0x1FF;
        flag_col[t] = 0x1FF;
        flag_box[t] = 0x1FF;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            remove_flag(get(j, i), flag_row[i]);
            remove_flag(get(j, i), flag_col[j]);
            remove_flag(get(j, i), flag_box[(j / 3) + 3 * (i / 3)]);
        }
    }
}

void SudokuFlagBoard::put(int x, int y, int n)
{
    SudokuBoard::put(x, y, n);
    remove_flag(get(x, y), flag_row[y]);
    remove_flag(get(x, y), flag_col[x]);
    remove_flag(get(x, y), flag_box[(x / 3) + 3 * (y / 3)]);
}

void SudokuFlagBoard::del(int x, int y)
{
    set_flag(get(x, y), flag_row[y]);
    set_flag(get(x, y), flag_col[x]);
    set_flag(get(x, y), flag_box[(x / 3) + 3 * (y / 3)]);
    SudokuBoard::del(x, y);
}


class Point
{
public:
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
};
using pair_pi = std::pair<Point, int>;

uint64_t search_answer(std::vector<pair_pi> empty_points_heaped, SudokuFlagBoard board);

auto foo1 = [](const pair_pi& a, const pair_pi& b)
{
    return a.second > b.second;
};

uint64_t count_answer(SudokuFlagBoard& board)
{
    uint64_t result = 0;
    //int count_candidate_num[9 * 9] = {0}; // そもそもすべてのマスの候補数を記録する必要はない、空きマスだけでよかった
    std::vector<pair_pi> xxx;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board.get(j, i) == 0) {
                //count_candidate_num[j + 9 * i] = board.get_flag_at(j, i).count();
                xxx.emplace_back(Point(j, i), board.get_flag_at(j, i).count());
            }
        }
    }
    std::make_heap(xxx.begin(), xxx.end(), foo1);

    for (auto node : xxx) {
        std::cout << "(" << node.first.x << "," << node.first.y << ":" << node.second << ") -> ";
    } std::cout << std::endl;

    result = search_answer(xxx, board);

    return result;
}

uint64_t search_answer(std::vector<pair_pi> empty_points_heaped, SudokuFlagBoard board)
{
        /*
    for (auto node : empty_points_heaped) {
        std::cout << "(" << node.first.x << "," << node.first.y << ":" << node.second << ") -> ";
    } std::cout << std::endl;
        */
    if (empty_points_heaped.empty()) {
        return 1;
    }
    uint64_t result = 0;
    Point next_point = empty_points_heaped.front().first;
    int candidate = empty_points_heaped.front().second;

    std::pop_heap(empty_points_heaped.begin(), empty_points_heaped.end(), foo1);
    empty_points_heaped.pop_back();

    if (board.get(next_point.x, next_point.y) != 0) {
        //print_board(board, "Error! Filled point is in the empty_points_heaped." );
    } else if (candidate > 0) {
        numflag next_candidate(board.get_flag_at(next_point.x, next_point.y));
        int ans[9] = {0}, cand_num[9] = {0};
        int s = 0;
        for (int i = 0; i < 9; i++) {
            if (next_candidate[i])
                cand_num[s++] = i + 1;
        }
        
        for (int j = 0; j < candidate; j++) {
            board.put(next_point.x, next_point.y, cand_num[j]);
            for (size_t i = 0; i < empty_points_heaped.size(); i++) {
                pair_pi& hp_i = empty_points_heaped[i];
                if (hp_i.first.x == next_point.x || hp_i.first.y == next_point.y || (hp_i.first.x / 3 == next_point.x / 3 && hp_i.first.y / 3 == next_point.y / 3)) {
                    hp_i.second = board.get_flag_at(hp_i.first.x, hp_i.first.y).count();
                    std::push_heap(empty_points_heaped.begin(), empty_points_heaped.begin() + i + 1, foo1);
                }
            }
            //#pragma omp task shared(ans, j, empty_points_heaped, board)
            ans[j] = search_answer(empty_points_heaped, board);

            board.del(next_point.x, next_point.y);
        }
        #pragma omp taskwait
        
        for (int j = 0; j < candidate; j++)
            result += ans[j];
    }

    return result;
}