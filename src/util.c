#include "util.h"

int mod(int x, int m) {
    return (x%m + m)%m;
}

// modifies a string since the value 10 is two chars
void resolve_card_val(char *val, int len_val, int card) {
    int val_index = card % SUIT_SIZE;
    char *vals_all[] = CARD_TO_VAL;
    
    memset(val, 0, len_val);
    strncpy(val, vals_all[val_index], strlen(vals_all[val_index]));
}

// sets the value of passed in string to be the suit
void resolve_card_suit(char *suit, int len_suit, int card) {
    int suit_index = card / SUIT_SIZE;
    char *suits_all[] = CARD_TO_SUIT;

    memset(suit, 0, len_suit);
    strncpy(suit, suits_all[suit_index], strlen(suits_all[suit_index]));
}
