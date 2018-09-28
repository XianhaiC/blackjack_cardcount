#include "util.h"

// modifies a string since the value 10 is two chars
void resolve_card_val(char *val, int len_val, int card) {
    int val_index = card % DECK_SIZE;
    char *vals_all[] = CARD_TO_VAL;
    
    memset(val, 0, len_val);
    strncpy(val, vals_all[val_index], strlen(vals_all[val_index]));
}

// returns the type of the card as a char
void resolve_card_suit(char *suit, int card) {
    int suit_index = card / DECK_SUITS;
    char suits_all[] = CARD_TO_SUIT;
    


    return suits_all[suit_index];
}
