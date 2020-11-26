#include "Game.h"

bool Game::get_player_choice() const {
    return this->player_starts;
}

Board* Game::get_game_state() const {
    return this->game_state;
}

void Game::update_game_state(Board* board) {
    this->game_state = board;
}

bool Game::player_first() {
    bool player_starts = true;
    char choice;
    std::cout << "Player starts first? [y/n] " << std::endl;

    std::cout << "> ";
    std::cin >> choice;

    if (choice == 'y') {
        player_starts = true;
    }
    else if (choice == 'n') {
        player_starts = false;
    }

    this->player_starts = player_starts;
    return player_starts;
}

bool Game::player_move() {
    int x, y;
    std::cout << "> ";
    std::cin >> x >> y;

    if (x >= 1 && x <= 3 && y >= 1 && y <= 3) {
        if (this->get_player_choice()) {
            if (!this->game_state->make_move(x, y, "X")) {
                std::cout << "Invalid move" << std::endl;
                return false;
            }
        }
        else {
            if (!this->game_state->make_move(x, y, "O")) {
                std::cout << "Invalid move" << std::endl;
                return false;
            }
        }
    }
    else {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    return true;
}

Board* Game::get_action(Board* current, Board* board) {
    return this->game_state->get_action(current, board);
}

std::pair<int, Board*> Game::max_value(Board* state, int a, int b) {
    if (state->terminal_test()) {
        return std::make_pair(state->get_utility(), state);
    }

    std::pair<int, Board*> v;
    v.first = INT_MIN;

    if (!state->get_children().size()) {
        state->generate_children("X");
    }
    else {
        state->clear_children();
        state->generate_children("X");
    }

    for (unsigned long int i = 0; i < state->get_children().size(); ++i) {
        std::pair<int, Board*> res = this->min_value(state->get_children().at(i), a, b);

        if (v.first < res.first) {
            v = res;
        }

        if (v.first >= b) {
            return v;
        }
        else {
            a = std::max(a, v.first);
        }
    }

    return v;
}

std::pair<int, Board*> Game::min_value(Board* state, int a, int b) {
    if (state->terminal_test()) {
        return std::make_pair(state->get_utility(), state);
    }

    std::pair<int, Board*> v;
    v.first = INT_MAX;

    if (!state->get_children().size()) {
        state->generate_children("O");
    }
    else {
        state->clear_children();
        state->generate_children("O");
    }

    for (unsigned long int i = 0; i < state->get_children().size(); ++i) {
        std::pair<int, Board*> res = this->max_value(state->get_children().at(i), a, b);

        if (v.first > res.first) {
            v = res;
        }

        if (v.first <= a) {
            return v;
        }
        else {
            b = std::min(b, v.first);
        }
    }

    return v;
}

Board* Game::alpha_beta_search() {
    std::pair<int, Board*> v;

    if (this->get_player_choice()) {
        v = this->min_value(this->get_game_state(), INT_MIN, INT_MAX);
    }
    else {
        v = this->max_value(this->get_game_state(), INT_MIN, INT_MAX);
    }

    return this->get_action(this->game_state, v.second);
}

void Game::ai_move(int turn) {
    if (!this->get_player_choice() && turn == 0) {
        int x = rand() % 3 + 1;
        int y = rand() % 3 + 1;

        this->game_state->make_move(x, y, "X");
    }
    else {
        this->update_game_state(this->alpha_beta_search());
    }
}

bool Game::check_game_end() const {
    if (!this->game_state->x_wins() && !this->game_state->o_wins() && this->game_state->terminal_test()) {
        std::cout << std::endl;
        std::cout << "\t    Draw" << std::endl;
        std::cout << std::endl;

        return true;
    }
    else {
        return false;
    }
}

void Game::end_game(char c) const {
    this->print_logo();
    this->print_state();

    std::cout << std::endl;
    if (this->get_player_choice()) {
        if (c == 'X') {
            std::cout << "\tThe Player Won" << std::endl;
        }
        else {
            std::cout << "\tThe AI Won" << std::endl;
        }
    }
    else {
        if (c == 'X') {
            std::cout << "\tThe AI Won" << std::endl;
        }
        else {
            std::cout << "\tThe Player Won" << std::endl;
        }
    }
    std::cout << std::endl;
}

void Game::copy_game_obj(const Game& game) {
    this->player_starts = game.get_player_choice();
    this->game_state = new Board(game.get_game_state());
}

void Game::clear() {
    delete this->game_state;
}

void Game::print_logo() const {
    std::cout << "\tTIC-TAC-TOE\t" << std::endl;
    std::cout << std::endl;
}

void Game::print_error_msg() const {
    std::cout << "The Game ended prematurely" << std::endl;
}

void Game::print_state() const {
    this->game_state->print_state();
}

Game::Game() {
    this->player_starts = false;
    this->game_state = new Board();
}

Game::Game(const Game& game) {
    this->copy_game_obj(game);
}

Game& Game::operator=(const Game& game) {
    if (this != &game) {
        this->clear();
        this->copy_game_obj(game);
    }

    return *this;
}

Game::~Game() {
    this->clear();
}

void Game::play() {
    if (std::system("clear") == 0) {
        this->print_logo();
        int player;

        if (this->player_first()) {
            player = 0;
        }
        else {
            player = 1;
        }

        int itr = 0;
        while (itr < 10) {
            if (std::system("clear") == 0) {
                if (this->game_state->x_wins()) {
                    this->game_state->cross_x();
                    this->end_game('X');
                    break;
                }
                else if (this->game_state->o_wins()) {
                    this->game_state->cross_o();
                    this->end_game('O');
                    break;
                }

                this->print_logo();
                this->print_state();

                if (this->check_game_end()) {
                    break;
                }

                if (itr % 2 == player) {
                    if (!this->player_move()) {
                        this->print_error_msg();
                        break;
                    }
                }
                else {
                    this->ai_move(itr);
                }
                ++itr;
            }
            else {
                this->print_error_msg();
                break;
            }
        }
    }
    else {
        this->print_error_msg();
    }
}
