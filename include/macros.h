#ifndef MACROS_H
#define MACROS_H

#include <ncurses.h>

// game setting macros
#define DECK_SIZE 52
#define DECK_SUITS 4
#define SUIT_SIZE 13
#define PLAYER_START_CARDS 10
#define BET_MIN_INITIAL 1
#define DECK_LEFTOVER_WIN 3

// drawing macros
#define COLLECTION_PAD "    "
#define COLLECTION_PAD_MIN "   "
#define COLLECTION_BLANK "__"

#define TABLE_MAX_CARDS 6
#define TABLE_DEALER_X 12
#define TABLE_DEALER_Y 1
#define TABLE_PLAYER_X 12
#define TABLE_PLAYER_Y 8

#define ACTION_OPTION_PAD_L 3

#define COLLECTION_ROWS 4
#define COLLECTION_PAD_L 1
#define COLLECTION_ITEM_W 6
#define COLLECTION_CURSOR "> "
#define COLLECTION_CURSOR_BLANK "  "
#define COLLECTION_CURSOR_LEN 2
#define COLLECTION_HL_NONE -1

#define NULL_CARD -1

// util macros
#define CARD_TO_VAL {\
    "A", "2", "3", "4", "5",\
    "6", "7", "8", "9", "10",\
    "J", "Q", "K"\
}
#define CARD_TO_SUIT {"^", "&", "@", "+"}
#define BUFSIZ_VAL 8
#define BUFSIZ_SUIT 8

// control macros
#define KIN_UP 'w'
#define KIN_DOWN 's'
#define KIN_LEFT 'a'
#define KIN_RIGHT 'd'
#define KIN_SELECT 'h'
#define KIN_CONFIRM 'j'

#endif
