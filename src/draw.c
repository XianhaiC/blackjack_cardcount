/*
 * This file contains functions related to drawing sprites and communicating
 * with the ncurses library
 */

#include "draw.h"

/*
 * draws a sprite from an array of strings
 * y - the y coord
 * x - the x coord
 * sprite - array of strings
 * len_sprite - length of sprite
 */
void draw_sprite(int y, int x, char **sprite, int len_sprite) {
    int i; 

    // loop through each string and print it
    for (i = 0; i < len_sprite; i++) {
        mvprintw(y + i, x, sprite[i]);
    }
}

/*
 * draws the skeleton frame of the game board
 */
void draw_skeleton() {
    char *sprite[] = SPR_SKELETON;
    
    // draw the sprite
    draw_sprite(
            SPR_SKELETON_Y,
            SPR_SKELETON_X,
            sprite,
            SPR_SKELETON_H);

    refresh();
}

/*
 * draws a given card with value and type
 * y - the y coord
 * x - the x coord
 */
void draw_card(int y, int x, int card) {
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    // draw a facedown card
    if (card == CARD_NULL) {
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

/*
 * draws the stats of the current round
 * total_dealer - the sum of the dealer's cards
 * total_player - the sum of the player's cards
 * min_bet - the minimun bet
 * deck_left - cards left in the deck
 */
void draw_stats(int total_dealer, int total_player, int min_bet, int deck_left) {
    char *sprite[] = SPR_STATS;
    char *sprite_clr[] = SPR_STATS_CLR;
    int x = SPR_STATS_X;
    int y = SPR_STATS_Y;
    
    // clear the area
    draw_sprite(y, x, sprite_clr, SPR_STATS_CLR_H);

    // draw the sprite
    mvprintw(y, x, sprite[0]);
    mvprintw(y + 1, x, sprite[1], total_dealer);
    mvprintw(y + 2, x, sprite[2], total_player);
    mvprintw(y + 3, x, sprite[3], min_bet);
    mvprintw(y + 4, x, sprite[4], deck_left);
    refresh();
}

/*
 * draws the player's card collection
 * player_cards - the list of cards
 * highlight_current - on which card index the cursor is
 * highlight_all - the selected cards
 */
void draw_collection(int *player_cards, int highlight_current, int *highlight_all) {
    int i, j;
    int card_index;
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];

    // temporary buf used to build the printed strings
    char buf_item[SPR_COLLECTION_W];
    char *sprite[] = SPR_COLLECTION;
    char *sprite_clr[] = SPR_COLLECTION_CLR;
    int x_items = SPR_COLLECTION_X;
    int y_items = SPR_COLLECTION_Y + SPR_COLLECTION_H;

    // clear the area
    draw_sprite(
            SPR_COLLECTION_Y,
            SPR_COLLECTION_X,
            sprite_clr,
            SPR_COLLECTION_CLR_H);

    // draw the text at the top
    draw_sprite(
            SPR_COLLECTION_Y,
            SPR_COLLECTION_X,
            sprite,
            SPR_COLLECTION_H);

    // loop through every row of cards
    for (i = 0; i < COLLECTION_ROWS; i++) {
        // loop through each card in a suit
        for (j = 0; j < SUIT_SIZE; j++) {
            // calculate its card index used for identifying its val and suit
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

            // get the val and suit into strings
            resolve_card_val(value, BUFSIZ_VAL, card_index);
            resolve_card_suit(suit, BUFSIZ_SUIT, card_index);
            memset(buf_item, 0, SPR_COLLECTION_W);
            strcat(buf_item, value);
            strcat(buf_item, suit);

            // highlight the selected cards
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

    refresh();
}

/*
 * draws the action menu
 * options - the options availible to the player
 * len_options - the length of options
 * highlight - the highlighted option
 */
void draw_action(char *options[], int len_options, int highlight) {
    int i;
    int x = SPR_ACTION_X;
    int y = SPR_ACTION_Y;
    int len_sprite = SPR_ACTION_H + len_options;
    char *sprite[] = SPR_ACTION;
    char *sprite_clr[] = SPR_ACTION_CLR;

    // clear and draw the top part
    draw_sprite(SPR_ACTION_Y, SPR_ACTION_X, sprite_clr, SPR_ACTION_CLR_H);
    draw_sprite(SPR_ACTION_Y, SPR_ACTION_X, sprite, SPR_ACTION_H);

    // draw each option
    for (i = 0; i < len_options; i++) {
        // highlight the selected option
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

    refresh();
}

/*
 * draw the cards on the table
 * hand_dealer - the dealer's cards
 * len_dealer - the length of the dealer's card array
 * hand_player - the player's cards
 * len_player - the length of the player's card array
 */
void draw_table(int *hand_dealer, int len_dealer, int *hand_player, int len_player) {
    int i;
    char value[BUFSIZ_VAL];
    char suit[BUFSIZ_SUIT];
    char *sprite_clr[] = SPR_TABLE_CLR;

    // clear the area
    draw_sprite(
            TABLE_DEALER_Y,
            TABLE_DEALER_X,
            sprite_clr,
            SPR_TABLE_CLR_H);

    // loop through and print the dealer's cards
    for (i = 0; i < len_dealer && i < TABLE_MAX_CARDS; i++) {
        draw_card(
                TABLE_DEALER_Y,
                TABLE_DEALER_X + SPR_CARD_W * i,
                hand_dealer[i]);
    }

    // loop through and print the player's cards
    for (i = 0; i < len_player && i < TABLE_MAX_CARDS; i++) {
        draw_card(
                TABLE_PLAYER_Y,
                TABLE_PLAYER_X + SPR_CARD_W * i,
                hand_player[i]);
    }

    refresh();
}

/*
 * clear the action area
 */            
void draw_action_clear() {
    char *sprite_clr[] = SPR_ACTION_CLR;
    draw_sprite(
            SPR_ACTION_Y,
            SPR_ACTION_X,
            sprite_clr,
            SPR_ACTION_CLR_H);
}

/*
 * clear the stats area
 */
void draw_stats_clear() {
    char *sprite_clr[] = SPR_STATS_CLR;
    draw_sprite(
            SPR_STATS_Y,
            SPR_STATS_X,
            sprite_clr,
            SPR_STATS_CLR_H);
}

/*
 * clear the table area
 */
void draw_table_clear() {
    char *sprite_clr[] = SPR_TABLE_CLR;
    draw_sprite(
            TABLE_DEALER_Y,
            TABLE_DEALER_X,
            sprite_clr,
            SPR_TABLE_CLR_H);
}

/*
 * draw a notice for betting
 * bet_min - the current minimum bet
 */
void draw_notice_bet(int bet_min) {
    int i;
    char *sprite[] = SPR_NOTI_BETS;
    
    // print out the sprite
    for (i = 0; i < SPR_NOTI_BETS_H; i++) {
        // the line that has the bet number
        if (i == 7) {
            mvprintw(
                    SPR_NOTI_BETS_Y + i,
                    SPR_NOTI_BETS_X,
                    sprite[i],
                    bet_min);
        }
        else {
            mvprintw(
                    SPR_NOTI_BETS_Y + i,
                    SPR_NOTI_BETS_X,
                    sprite[i]);
        }
    }

    refresh();
}

/*
 * draw a notice board for when a round is lost
 */
void draw_notice_round_lost() {
    char *sprite[] = SPR_NOTI_ROUND_LOST;
    
    draw_sprite(
            SPR_NOTI_ROUND_LOST_Y,
            SPR_NOTI_ROUND_LOST_X,
            sprite,
            SPR_NOTI_ROUND_LOST_H);

    refresh();
}

/*
 * draw a notice board for when a round is won
 */
void draw_notice_round_won() {
    int i;
    char *sprite[] = SPR_NOTI_ROUND_WON;
    
    draw_sprite(
            SPR_NOTI_ROUND_WON_Y,
            SPR_NOTI_ROUND_WON_X,
            sprite,
            SPR_NOTI_ROUND_WON_H);

    refresh();
}

/*
 * draw a notice board for when a round is tied
 */
void draw_notice_round_tie() {
    int i;
    char *sprite[] = SPR_NOTI_ROUND_TIE;
    
    draw_sprite(
            SPR_NOTI_ROUND_TIE_Y,
            SPR_NOTI_ROUND_TIE_X,
            sprite,
            SPR_NOTI_ROUND_TIE_H);

    refresh();
}

/*
 * draw a notice board for when a game is lost
 */
void draw_notice_game_lost() {
    int i;
    char *sprite[] = SPR_NOTI_GAME_LOST;
    
    draw_sprite(
            SPR_NOTI_GAME_LOST_Y,
            SPR_NOTI_GAME_LOST_X,
            sprite,
            SPR_NOTI_GAME_LOST_H);

    refresh();
}

/*
 * draw a notice board for when a game is won
 */
void draw_notice_game_won() {
    int i;
    char *sprite[] = SPR_NOTI_GAME_WON;
    
    draw_sprite(
            SPR_NOTI_GAME_WON_Y,
            SPR_NOTI_GAME_WON_X,
            sprite,
            SPR_NOTI_GAME_WON_H);

    refresh();
}

/*
 * draw a notice board for when it's the player's turn
 */
void draw_notice_turn_player() {
    int i;
    char *sprite[] = SPR_NOTI_TURN_PLAYER;
    
    draw_sprite(
            SPR_NOTI_TURN_PLAYER_Y,
            SPR_NOTI_TURN_PLAYER_X,
            sprite,
            SPR_NOTI_TURN_PLAYER_H);

    refresh();
}

/*
 * draw a notice board for when it's the dealer's turn
 */
void draw_notice_turn_dealer() {
    int i;
    char *sprite[] = SPR_NOTI_TURN_DEALER;

    draw_sprite(
            SPR_NOTI_TURN_DEALER_Y,
            SPR_NOTI_TURN_DEALER_X,
            sprite,
            SPR_NOTI_TURN_DEALER_H);

    refresh();
}

/*
 * draw a notice board for when a black jack appears
 */
void draw_notice_bj() {
    int i;
    char *sprite[] = SPR_NOTI_BJ;
    
    draw_sprite(
            SPR_NOTI_BJ_Y,
            SPR_NOTI_BJ_X,
            sprite,
            SPR_NOTI_BJ_H);

    refresh();
}
