/*
 * This file contains functions related to drawing sprites and communicating
 * with the ncurses library
 */

void draw_skeleton() {

    char *sprite[] = SPR_SKELETON;
    
    draw_sprite(
            SPR_SKELETON_Y,
            SPR_SKELETON_X,
            sprite,
            SPR_SKELETON_H);
}

void draw_card(int y, int x, int card) {
    char *sprite[];
    char value[BUFSIZ_VAL];
    char suit;

    // obtain the value and suit of the card
    resolve_card_val(value, BUFSIZ_VAL, card);
    suit = resolve_card_type(card);

    // value is null terminated by resolve_card_val
    // get the correct sprite format
    if (strlen(value) > 1) {
        sprite = SPR_CARD_TEN;
    }
    else {
        sprite = SPR_CARD;
    }

    // print out the card, formatting the value and suit in
    mvprintw(y, x, sprite[0]);
    mvprintw(y + 1, x, sprite[1], value);
    mvprintw(y + 2, x, sprite[2]);
    mvprintw(y + 3, x, sprite[3], suit);
    mvprintw(y + 4, x, sprite[4]);
    mvprintw(y + 5, x, sprite[5], value);
}

void draw_stats(int total_dealer, int total_player, int min_bet, int deck_left) {
    char *sprite[] = SPR_STATS;
    int x = SPR_STATS_X;
    int y = SPR_STATS_Y;

    mvprintw(y, x, sprite[0]);
    mvprintw(y + 1, x, sprite[1], total_dealer);
    mvprintw(y + 2, x, sprite[2], total_player);
    mvprintw(y + 3, x, sprite[3], min_bet);
    mvprintw(y + 4, x, sprite[4], deck_left);
}

void draw_collection(int *player_cards) {
    int i;
    int suit;
    int card_index;
    char value[BUFSIZ_VAL];
    char suit;

    char buf_sprite[SPR_COLLECTION_W];
    char sprite[SPR_COLLECTION_H][SPR_COLLECTION_W];
    char *txt_collection[] = SPR_COLLECTION;
    int x = SPR_COLLECTION_X;
    int y = SPR_COLLECTION_Y;

    memset(sprite, 0, SPR_COLLECTION_W * SPR_COLLECTION_H * SIZEOF(char));

    for (i = 0; i < SPR_COLLECTION_ROWS ; i++) {
        if (i < SPR_COLLECTION_H) {
            strncpy(sprite[i], txt_collection[i], strlen(txt_collection[i]));
        }
        else {
            for (suit = 0; suit < SUIT_SIZE; suit++) {
                card_index = suit + i * SUIT_SIZE;
                if (player_cards[card_index] == 1) {
                    resolve_card_val(value, BUFSIZ_VAL, card_index);
                    suit = resolve_card_type(card_index);
                    
                }
                else {
                    
                }
            }
        }
    }

}

void draw_action(char *options[], int len_options) {
    int i;
    int len_sprite = SPR_ACTION_H + len_options;
    char *txt_action[] = SPR_ACTION;
    char *sprite[len_sprite];

    for (i = 0; i < len_sprite; i++) {
        if (i < SPR_ACTION_H) {
            sprite[i] = txt_action[i];
        }
        else {
            sprite[i] = options[i];
        }
    }

    draw_sprite(SPR_ACTION_Y, SPR_ACTION_X, sprite, len_sprite);
}

void draw_sprite(int y, int x, char **sprite, int len_sprite) {
    int i;
    for (i = 0; sprite[i] != NULL; i++) {
        mvprintw(y + i, x, sprite[i]);
    }
}
