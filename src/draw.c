/*
 * This file contains functions related to drawing sprites and communicating
 * with the ncurses library
 */

#include "draw.h"


void draw_sprite(int y, int x, char **sprite, int len_sprite) {
    int i;

    for (i = 0; i < len_sprite; i++) {
        mvprintw(y + i, x, sprite[i]);
    }
}

void draw_skeleton() {

    char *sprite[] = SPR_SKELETON;
    
    draw_sprite(
            SPR_SKELETON_Y,
            SPR_SKELETON_X,
            sprite,
            SPR_SKELETON_H);
}

void draw_card(int y, int x, int card) {
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    if (card == NULL_CARD) {
        char *sprite[] = SPR_CARD_NULL;
        draw_sprite(y, x, sprite, SPR_CARD_H);
    }
    else {
        // obtain the value and suit of the card
        resolve_card_val(value, BUFSIZ_VAL, card);
        resolve_card_suit(suit, BUFSIZ_SUIT, card);

        // value is null terminated by resolve_card_val
        // get the correct sprite format
        if (strlen(value) > 1) {
            char *sprite[] = SPR_CARD_TEN;
            // print out the card, formatting the value and suit in
            mvprintw(y, x, sprite[0]);
            mvprintw(y + 1, x, sprite[1], value);
            mvprintw(y + 2, x, sprite[2]);
            mvprintw(y + 3, x, sprite[3], suit);
            mvprintw(y + 4, x, sprite[4]);
            mvprintw(y + 5, x, sprite[5], value);
        }
        else {
            char *sprite[] = SPR_CARD;
            // print out the card, formatting the value and suit in
            mvprintw(y, x, sprite[0]);
            mvprintw(y + 1, x, sprite[1], value);
            mvprintw(y + 2, x, sprite[2]);
            mvprintw(y + 3, x, sprite[3], suit);
            mvprintw(y + 4, x, sprite[4]);
            mvprintw(y + 5, x, sprite[5], value);
        }
    }
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

void draw_collection(int *player_cards, int highlight_current, int *highlight_all) {
    int i, j;
    int card_index;
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    // temporary buf used to build the printed strings
    char buf_item[SPR_COLLECTION_W];
    char *sprite[] = SPR_COLLECTION;
    int x_items = SPR_COLLECTION_X;
    int y_items = SPR_COLLECTION_Y + SPR_COLLECTION_H;

    draw_sprite(SPR_COLLECTION_Y,
            SPR_COLLECTION_X,
            sprite,
            SPR_COLLECTION_H);

    
    refresh();
    for (i = 0; i < COLLECTION_ROWS; i++) {
        for (j = 0; j < SUIT_SIZE; j++) {
            card_index = i * SUIT_SIZE + j;
            
            // print the cursor
            if (card_index == highlight_current) {
                mvprintw(
                        y_items + i, 
                        x_items + COLLECTION_PAD_L + j * COLLECTION_ITEM_W,
                        COLLECTION_CURSOR);
            }
            else {
                mvprintw(
                        y_items + i, 
                        x_items + COLLECTION_PAD_L + j * COLLECTION_ITEM_W,
                        COLLECTION_CURSOR_BLANK);
            }
            
            // print blank and continue if the player does not own the card
            if (player_cards[card_index] == 0) {
                mvprintw(
                        y_items + i, 
                        x_items + COLLECTION_PAD_L + j * COLLECTION_ITEM_W 
                        + COLLECTION_CURSOR_LEN,
                        COLLECTION_BLANK);

                continue;
            }

            resolve_card_val(value, BUFSIZ_VAL, card_index);
            resolve_card_suit(suit, BUFSIZ_SUIT, card_index);
            
            memset(buf_item, 0, SPR_COLLECTION_W);
            
            strcat(buf_item, value);
            strcat(buf_item, suit);

            if (highlight_all[card_index] == 1) {
                attron(A_REVERSE); 
                mvprintw(
                        y_items + i, 
                        x_items + COLLECTION_PAD_L + j * COLLECTION_ITEM_W 
                        + COLLECTION_CURSOR_LEN,
                        buf_item);
                attroff(A_REVERSE); 
            }
            else {
                mvprintw(
                        y_items + i, 
                        x_items + COLLECTION_PAD_L + j * COLLECTION_ITEM_W 
                        + COLLECTION_CURSOR_LEN,
                        buf_item);
            }
        }
    }
/*
    memset(sprite_arr, 0, spr_h * (SPR_COLLECTION_W + 1) * sizeof(char));

    for (i = 0; i < spr_h; i++) {
        if (i < SPR_COLLECTION_H) {
            strncpy(sprite_arr[i], txt_collection[i], strlen(txt_collection[i]));
        }
        else {
            // loop through each card that appears in the row
            for (card_val = 0; card_val < SUIT_SIZE; card_val++) {
                // calculate its card index in the deck
                card_index = card_val + (i - SPR_COLLECTION_H) * SUIT_SIZE;

                // if the player owns the card
                if (player_cards[card_index] == 1) {
                    resolve_card_val(value, BUFSIZ_VAL, card_index);
                    resolve_card_suit(suit, BUFSIZ_SUIT, card_index);

                    // the first and 10th item need less padding, so the strcat
                    // needs to be different
                    if (card_val == 0 || card_val == 9) {
                        strcat(sprite_arr[i], COLLECTION_PAD_MIN); 
                    }
                    else {
                        strcat(sprite_arr[i], COLLECTION_PAD);
                    }
                    
                    // append the card values
                    strcat(sprite_arr[i], value);
                    strcat(sprite_arr[i], suit);
                }
                else {
                    if (card_val == 0) {
                        strcat(sprite_arr[i], COLLECTION_PAD_MIN);
                    }
                    else {
                        strcat(sprite_arr[i], COLLECTION_PAD);
                    }

                    strcat(sprite_arr[i], COLLECTION_BLANK);
                }
            }
        }

        // null terminate last char in row
        sprite_arr[i][SPR_COLLECTION_W] = '\0';
        sprite[i] = sprite_arr[i];
    }

    draw_sprite(
            SPR_COLLECTION_Y,
            SPR_COLLECTION_X,
            sprite,
            spr_h);
            */
}

void draw_action(char *options[], int len_options, int highlight) {
    int i;
    int x = SPR_ACTION_X;
    int y = SPR_ACTION_Y;
    int len_sprite = SPR_ACTION_H + len_options;
    char *sprite[] = SPR_ACTION;

    draw_sprite(SPR_ACTION_Y, SPR_ACTION_X, sprite, SPR_ACTION_H);

    for (i = 0; i < len_options; i++) {
        if (i == highlight) {
            attron(A_REVERSE);
            mvprintw(
                    SPR_ACTION_Y + SPR_ACTION_H + i,
                    SPR_ACTION_X + ACTION_OPTION_PAD_L,
                    options[i]);
            attroff(A_REVERSE);
        }
        else {
            mvprintw(
                    SPR_ACTION_Y + SPR_ACTION_H + i,
                    SPR_ACTION_X + ACTION_OPTION_PAD_L,
                    options[i]);
        }
    }
}

void draw_table(int *dealer_hand, int len_dealer, int *player_hand, int len_player) {
    int i;
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    for (i = 0; i < len_dealer && i < TABLE_MAX_CARDS; i++) {
        draw_card(
                TABLE_DEALER_Y,
                TABLE_DEALER_X + SPR_CARD_W * i,
                dealer_hand[i]);
    }

    for (i = 0; i < len_player && i < TABLE_MAX_CARDS; i++) {
        draw_card(
                TABLE_PLAYER_Y,
                TABLE_PLAYER_X + SPR_CARD_W * i,
                player_hand[i]);
    }
}
