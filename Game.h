#include <iostream>

#include <stdlib.h>

#include <random>
#include <climits>
#include <algorithm>

#include "Board.h"

#ifndef GAME_H
#define GAME_H

class Game {
private:
    bool player_starts;
    Board* game_state;

    bool get_player_choice() const;
    Board* get_game_state() const;
    void update_game_state(Board*);

    bool player_first();
    bool player_move();
    Board* get_action(Board*, Board*);
    std::pair<int, Board*> max_value(Board*, int, int);
    std::pair<int, Board*> min_value(Board*, int, int);
    Board* alpha_beta_search();
    void ai_move(int);

    bool check_game_end() const;
    void end_game(char) const;
    void copy_game_obj(const Game&);
    void clear();

    void print_logo() const;
    void print_error_msg() const;
    void print_state() const;

public:
    Game();
    Game(const Game&);
    Game& operator=(const Game&);
    ~Game();

    void play();
};

#endif
