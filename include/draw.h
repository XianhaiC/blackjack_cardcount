#ifndef DRAW_H
#define DRAW_H

#include <string.h>
#include <ncurses.h>

#include "macros.h"
#include "sprites.h"
#include "util.h"

void draw_sprite(int y, int x, char **sprite, int len_sprite);
void draw_skeleton();
void draw_card(int y, int x, int card);
void draw_stats(int total_dealer, int total_player, int min_bet, int deck_left);
void draw_collection(int *player_cards, int highlight_current, int *highlight_all);
void draw_action(char *options[], int len_options, int highlight);
void draw_table(int *dealer_hand, int len_dealer, int *player_hand, int len_player);
void draw_action_clear();
void draw_stats_clear();
void draw_table_clear();
void draw_notice_bet(int bet_min);
void draw_notice_round_lost();
void draw_notice_round_won();
void draw_notice_round_tie();
void draw_notice_game_lost();
void draw_notice_game_won();
void draw_notice_turn_player();
void draw_notice_turn_dealer();
void draw_notice_bj();

#endif
