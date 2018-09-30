#ifndef MACROS_H
#define MACROS_H

#include <ncurses.h>

// game setting macros
#define DECK_SIZE 52
#define DECK_SUITS 4
#define SUIT_SIZE 13
#define POINTS_FACE 10
#define POINTS_ACE_HARD 11
#define POINTS_ACE_SOFT 1
#define POINTS_MAX 21
#define DEALER_HIT_MAX 16
#define PLAYER_START_CARDS 10
#define BET_MIN_INITIAL 1
#define DECK_REMAINING_MIN 5
#define HAND_MAX_SIZE 6
#define HAND_BJ_SIZE 2
#define BJ_PAYOUT 1.5f
#define SEL_NONE -1
#define SEL_STAND 0
#define SEL_HIT 1
#define ROUND_START_CARD_AMT 2

// drawing macros
#define COLLECTION_PAD "    "
#define COLLECTION_PAD_MIN "   "
#define COLLECTION_BLANK "__"

#define TABLE_MAX_CARDS 6
#define TABLE_DEALER_X 13
#define TABLE_DEALER_Y 1
#define TABLE_PLAYER_X 13
#define TABLE_PLAYER_Y 8

#define ACTION_OPTION_PAD_L 3
#define ACTION_OPTION_NUM 2
#define ACTION_STAND "STAND"
#define ACTION_HIT "HIT"

#define COLLECTION_ROWS 4
#define COLLECTION_PAD_L 1
#define COLLECTION_ITEM_W 6
#define COLLECTION_CURSOR "> "
#define COLLECTION_CURSOR_BLANK "  "
#define COLLECTION_CURSOR_LEN 2
#define COLLECTION_HL_NONE -1

#define CARD_NULL -1
#define CARD_ACE 0

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

// delay macros
#define DELAY_DEALER_PLAY 3000000
#define DELAY_CARD_REVEAL 500000
#define DELAY_TURN_PLAYER 3000000
#define DELAY_TURN_DEALER 3000000
#define DELAY_BJ 3000000
#define DELAY_ACTION 500000
#define DELAY_ROUND_END 1000000

#endif
