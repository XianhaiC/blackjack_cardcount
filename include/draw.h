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
void draw_collection(int *player_cards);
void draw_action(char *options[], int len_options, int highlight);
void draw_table(int *dealer_hand, int len_dealer, int *player_hand, int len_player);

#endif
