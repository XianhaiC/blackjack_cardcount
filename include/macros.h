#ifndef MACROS_H
#define MACROS_H

#define DECK_SIZE 52
#define DECK_SUITS 4
#define SUIT_SIZE 13
#define PLAYER_STARTING_CARDS 10
#define DECK_LEFTOVER_WIN 3
#define NULL_CARD -1
#define BUFSIZ_VAL 8
#define BUFSIZ_SUIT 8

// drawing macros
#define COLLECTION_PAD "    "
#define COLLECTION_PAD_MIN "   "
#define COLLECTION_BLANK "__"

#define TABLE_MAX_CARDS 6
#define TABLE_DEALER_X 12
#define TABLE_DEALER_Y 1
#define TABLE_PLAYER_X 12
#define TABLE_PLAYER_Y 8

// util macros
#define CARD_TO_VAL {\
    "A", "2", "3", "4", "5",\
    "6", "7", "8", "9", "10",\
    "J", "Q", "K"\
}
#define CARD_TO_SUIT {"^", "&", "@", "+"}

#endif
