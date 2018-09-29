#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h"

typedef struct {
    int deck[DECK_SIZE];
    int player_cards[DECK_SIZE];
    int bet_sel[DECK_SIZE];
    int bet_min;
    // boolean denoting if the game is over
    int game_is_over;
    // value indicates which state the round is in
    int round_state;
} game_info;

void game_info_reset(game_info *info);
void init_game(game_info *info);
void process_gameplay(game_info *info);
void play_round(game_info *info);
void process_betting(game_info *info);
void evaluate_game_status();

#endif
