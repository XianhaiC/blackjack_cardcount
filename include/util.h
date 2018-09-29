#ifndef UTIL_H
#define UTIL_H

#include <string.h>

#include "macros.h"

typedef struct {
    // holds boolean mask
    int deck[DECK_SIZE];
    int deck_remaining;
    int player_cards[DECK_SIZE];
    int player_cards_remaining;
    int bet_sel[DECK_SIZE];
    int bet_amt;
    int bet_min;
    // holds card index values
    int hand_dealer[DECK_SIZE];
    int hand_dealer_size;
    int hand_player[DECK_SIZE];
    int hand_player_size;
    int sum_dealer;
    int sum_player;
    // boolean denoting if the game is over
    int game_is_over;
    // value indicates the move the player made
    int last_action;
} game_info;

void game_info_reset(game_info *info);

int mod(int x, int m);
void resolve_card_val(char *val, int len_val, int card);
void resolve_card_suit(char *suit, int len_suit, int card);

#endif
