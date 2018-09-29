#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h"

void init_game(game_info *info);
void process_gameplay(game_info *info);
void play_round(game_info *info);
void process_betting(game_info *info);
void evaluate_game_status();

#endif
