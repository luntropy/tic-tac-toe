#include <iostream>

#include <vector>

#include <random>

#ifndef BOARD_H
#define BOARD_H

const int N = 3;

class Board {
private:
    Board* parent;
    int depth;
    char** board;
    int board_utility;
    std::vector<Board*> children;

    int calc_depth();
    void copy_board_obj(const Board&);
    void set_depth();
    void set_board_utility();
    void copy_board(const Board&);
    void copy_children(const Board&);
    void allocate_memory();
    void clear();

public:
    Board();
    Board(char**);
    Board(char[N][N]);
    Board(Board*);
    Board(const Board&);
    Board& operator=(const Board&);
    ~Board();

    void generate_children(char);
    char** get_board() const;
    Board* get_parent() const;
    int get_depth() const;
    int get_utility() const;
    std::vector<Board*> get_children() const;

    int utility() const;
    bool terminal_test() const;
    bool test_move(int, int, char) const;
    bool make_move(int, int, char);
    bool x_wins() const;
    bool o_wins() const;
    Board* get_action(Board*, Board*);
    void clear_children();

    void print_state() const;
};

#endif
