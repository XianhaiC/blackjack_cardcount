/*
 * This file contains functions related to drawing sprites and communicating
 * with the ncurses library
 */

#include "draw.h"


void draw_sprite(int y, int x, char **sprite, int len_sprite) {
    int i;

    for (i = 0; sprite[i] != NULL; i++) {
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

void draw_collection(int *player_cards) {
    int i;
    int card_val;
    int card_index;
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    int spr_h = SPR_COLLECTION_H + SPR_COLLECTION_ROWS;

    char buf_sprite[SPR_COLLECTION_W];
    // add space in each row for null terminator
    // holds the chars for the sprite on stack
    char sprite_arr[spr_h][SPR_COLLECTION_W + 1]; 
    // this array holds the pointers to each string in sprite_arr
    char *sprite[spr_h];
    char *txt_collection[] = SPR_COLLECTION;
    int x = SPR_COLLECTION_X;
    int y = SPR_COLLECTION_Y;

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
            SPR_COLLECTION_H);
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
            sprite[i] = options[i - SPR_ACTION_H];
        }
    }

    draw_sprite(SPR_ACTION_Y, SPR_ACTION_X, sprite, len_sprite);
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
