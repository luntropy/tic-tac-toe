#include "Board.h"

int Board::calc_depth() {
    if (this->parent) {
        return (this->parent)->get_depth() + 1;
    }

    return 0;
}

void Board::copy_board_obj(const Board& board) {
    this->parent = board.get_parent();
    this->depth = board.get_depth();
    this->allocate_memory();
    this->copy_board(board);
    this->set_board_utility();
    this->copy_children(board);
}

void Board::set_depth() {
    this->depth = this->calc_depth();
}

void Board::set_board_utility() {
    this->board_utility = this->utility();
}

void Board::copy_board(const Board& board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = board.board[i][j];
        }
    }
}

void Board::copy_children(const Board& board) {
    for (unsigned long int i = 0; i < board.get_children().size(); ++i) {
        Board* new_child = new Board(board.get_children().at(i)->get_board());
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

    this->parent = nullptr;
    this->set_depth();
    this->set_board_utility();
}

Board::Board(char** board) {
    this->allocate_memory();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = board[i][j];
        }
    }

    this->parent = nullptr;
    this->set_depth();
    this->set_board_utility();
}

Board::Board(char board[N][N]) {
    this->allocate_memory();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            this->board[i][j] = board[i][j];
        }
    }

    this->parent = nullptr;
    this->set_depth();
    this->set_board_utility();
}

Board::Board(Board* board) {
    this->copy_board_obj(*board);
}

Board::Board(const Board& board) {
    this->copy_board_obj(board);
}

Board& Board::operator=(const Board& board) {
    if (this != &board) {
        this->clear();
        this->copy_board_obj(board);
    }

    return *this;
}

Board::~Board() {
    this->clear();
}

void Board::generate_children(char c) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (this->test_move(i + 1, j + 1, c)) {
                Board* new_child = new Board(this->get_board());

                new_child->make_move(i + 1, j + 1, c);
                new_child->parent = this;
                new_child->depth = new_child->calc_depth();
                new_child->board_utility = new_child->utility();
                this->children.push_back(new_child);
            }
        }
    }
}

char** Board::get_board() const {
    return this->board;
}

Board* Board::get_parent() const {
    return this->parent;
}

int Board::get_depth() const {
    return this->depth;
}

int Board::get_utility() const {
    return this->board_utility;
}

std::vector<Board*> Board::get_children() const {
    return this->children;
}

int Board::utility() const {
    if (this->x_wins()) {
        return 10 - this->depth;
    }
    else if (this->o_wins()) {
        return this->depth - 10;
    }
    else {
        return 0;
    }
}

bool Board::terminal_test() const {
    if (this->x_wins() || this->o_wins()) {
        return true;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (this->board[i][j] == '-') {
                return false;
            }
        }
    }

    return true;
}

bool Board::test_move(int x, int y, char c) const {
    --x;
    --y;

    if (this->board[x][y] == '-') {
        return true;
    }

    return false;
}

bool Board::make_move(int x, int y, char c) {
    --x;
    --y;

    if (this->board[x][y] == '-') {
        this->board[x][y] = c;

        return true;
    }

    return false;
}

bool Board::x_wins() const {
    bool wins = false;
    for (int i = 0; i < N; ++i) {
        if (this->board[i][0] == 'X' && this->board[i][1] == 'X' && this->board[i][2] == 'X') {
            wins = true;
        }
        else if (this->board[0][i] == 'X' && this->board[1][i] == 'X' && this->board[2][i] == 'X') {
            wins = true;
        }
        else {
            wins = false;
        }

        if (wins) {
            return wins;
        }
    }

    if (this->board[0][0] == 'X' && this->board[1][1] == 'X' && this->board[2][2] == 'X') {
        wins = true;
    }

    if (this->board[0][2] == 'X' && this->board[1][1] == 'X' && this->board[2][0] == 'X') {
        wins = true;
    }

    return wins;
}

bool Board::o_wins() const {
    bool wins = false;
    for (int i = 0; i < N; ++i) {
        if (this->board[i][0] == 'O' && this->board[i][1] == 'O' && this->board[i][2] == 'O') {
            wins = true;
        }
        else if (this->board[0][i] == 'O' && this->board[1][i] == 'O' && this->board[2][i] == 'O') {
            wins = true;
        }
        else {
            wins = false;
        }

        if (wins) {
            return wins;
        }
    }

    if (this->board[0][0] == 'O' && this->board[1][1] == 'O' && this->board[2][2] == 'O') {
        wins = true;
    }

    if (this->board[0][2] == 'O' && this->board[1][1] == 'O' && this->board[2][0] == 'O') {
        wins = true;
    }

    return wins;
}

Board* Board::get_action(Board* current, Board* board) {
    while (board->get_parent() != current) {
        board = board->get_parent();
    }

    return board;
}

void Board::clear_children() {
    this->children.clear();
}

void Board::print_state() const {
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            std::cout << "\t    ";
        }
        std::cout << i + 1 << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < N; ++i) {
        std::cout << "\t  " << i + 1 << ' ';
        for (int j = 0; j < N; ++j) {
            std::cout << this->board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
