#include <iostream>

#include <vector>

#ifndef BOARD_H
#define BOARD_H

const int N = 3;

class Board {
private:
    char** board;
    std::vector<Board*> children;

    void copy_board_obj(const Board&);
    void copy_board(const Board&);
    void copy_children(const Board&);
    void allocate_memory();
    void clear();
public:
    Board();
    Board(char**);
    Board(char[N][N]);
    Board(const Board&);
    Board& operator=(const Board&);
    ~Board();

    char** get_board() const;
    std::vector<Board*> get_children() const;

    // bool player_wins();
    // bool ai_wins();

    void print_state() const;
};

#endif
