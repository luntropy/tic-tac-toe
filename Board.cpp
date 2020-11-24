#include "Board.h"

void Board::copy_board_obj(const Board& a) {
    this->allocate_memory();
    this->copy_board(a);
    this->copy_children(a);
}

void Board::copy_board(const Board& a) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = a.board[i][j];
        }
    }
}

void Board::copy_children(const Board& a) {
    std::vector<Board*>::iterator it;
    for (it = a.get_children().begin(); it != a.get_children().end(); ++it) {
        Board* new_child = new Board(a.get_board());
        this->children.push_back(new_child);
    }
}

void Board::allocate_memory() {
    this->board = new char*[N];
    for (int i = 0; i < N; ++i) {
        this->board[i] = new char[N];
    }
}

void Board::clear() {
    for (int i = 0; i < N; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;

    std::vector<Board*>::iterator it;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        delete *it;
    }
}

Board::Board() {
    this->allocate_memory();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = '-';
        }
    }
}

Board::Board(char** board) {
    this->allocate_memory();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = board[i][j];
        }
    }
}

Board::Board(char board[N][N]) {
    this->allocate_memory();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = board[i][j];
        }
    }
}

Board::Board(const Board& a) {
    this->copy_board_obj(a);
}

Board& Board::operator=(const Board& a) {
    if (this != &a) {
        this->clear();
        this->copy_board_obj(a);
    }

    return *this;
}

Board::~Board() {
    this->clear();
}

char** Board::get_board() const {
    return this->board;
}

std::vector<Board*> Board::get_children() const {
    return this->children;
}

void Board::print_state() const {
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            std::cout << "  ";
        }
        std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < N; ++i) {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < N; ++j) {
            std::cout << this->board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
