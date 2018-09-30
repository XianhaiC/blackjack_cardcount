/*
 * This file contains miscellaneous functions that operate on the game_info
 * struct as well as others that help with identifying cards
 */

#include "util.h"

/*
 * reset game_info struct to default parameters
 * info - game info
 */
void game_info_reset(game_info *info) {
    // the deck will initially hold all the cards
    memset(info->deck, 1, DECK_SIZE * sizeof(info->deck[0]));
    info->deck_remaining = DECK_SIZE;

    // the player will initially own no cards
    memset(info->player_cards, 0, DECK_SIZE * sizeof(info->player_cards[0]));
    info->player_cards_remaining = 0;

    // no cards are selected for betting
    memset(info->bet_sel, 0, DECK_SIZE * sizeof(info->bet_sel[0]));
    info->bet_amt = 0;

    // the dealer will have no cards
    memset(info->hand_dealer, 0, DECK_SIZE * sizeof(info->hand_dealer[0]));
    info->hand_dealer_size = 0;

    // the player will have no cards
    memset(info->hand_player, 0, DECK_SIZE * sizeof(info->hand_player[0]));
    info->hand_player_size = 0;

    info->bet_min = BET_MIN_INITIAL;
    info->game_is_over = 0;
    info->last_action = SEL_NONE;
}

/*
 * moves a card from the deck to the player's collection
 * info - game info
 * card - the card to give
 */
void game_info_give_player_card(game_info *info, int card) {
    info->deck[card] = 0;
    (info->deck_remaining)--;
    info->player_cards[card] = 1;
    (info->player_cards_remaining)++;
}

/*
 * moves a card from the player's collection to the deck
 * info - game info
 * card - the card to give
 */
void game_info_give_deck_card(game_info *info, int card) {
    info->deck[card] = 1;
    (info->deck_remaining)++;
    info->player_cards[card] = 0;
    (info->player_cards_remaining)--;
}

/*
 * toggle the selection of the player's cards for betting
 * info - game info
 * card - the card to toggle
 */
void game_info_bet_sel_toggle(game_info *info, int card) {
    if (info->bet_sel[card] == 0) {
        info->bet_sel[card] = 1;
        (info->bet_amt)++;
    }
    else {
        info->bet_sel[card] = 0;
        (info->bet_amt)--;
    }
}

/*
 * add a card the the player's hand
 * info - game info
 * card - the card to give
 */
void game_info_hand_player_add(game_info *info, int card) {
    // update player info
    info->hand_player[info->hand_player_size] = card;
    (info->hand_player_size)++;

    // calculate new sum
    info->sum_player = game_info_hand_sum(
            info->hand_player, 
            info->hand_player_size);
}

/*
 * add a card to the dealer's hand
 * info - game info
 * card - the card to give
 */
void game_info_hand_dealer_add(game_info *info, int card) {
    // update player info
    info->hand_dealer[info->hand_dealer_size] = card;
    (info->hand_dealer_size)++;

    // calculate new sum
    info->sum_dealer = game_info_hand_sum(
            info->hand_dealer, 
            info->hand_dealer_size);
}

/*
 * calculate the sume of the hand
 * hand - list of ints of card indices
 * len_hand - size of hand
 */
int game_info_hand_sum(int *hand, int len_hand) {
    int i;
    int sum = 0;
    int points;
    
    // loop through and sum all non aces
    for (i = 0; i < len_hand; i++) {
        if (hand[i] % SUIT_SIZE == CARD_ACE) {
            continue;
        }

        points = resolve_card_points(hand[i]);
        sum += points;
    }

    // loop through again and count aces depending on the current sum
    for (i = 0; i < len_hand; i++) {
        // now sum the aces
        if (hand[i] % SUIT_SIZE != CARD_ACE) {
            continue;
        }

        points = sum + POINTS_ACE_HARD > POINTS_MAX ? 
            POINTS_ACE_SOFT : POINTS_ACE_HARD;
        sum += points;
    }

    return sum;
}

/*
 * check if a hand is a black jack or not
 * hand - list of ints of card indices
 * len_hand - size of hand
 */
int game_info_hand_bj(int *hand, int len_hand) {
    int i;
    int contains_ace = 0;
    int contains_face = 0;

    // must be only 2 cards
    if (len_hand != HAND_BJ_SIZE) {
        return 0;
    }

    // make sure there's an ace and a face
    for (i = 0; i < len_hand; i++) {
        if (hand[i] % SUIT_SIZE == 0) {
            contains_ace = 1;
        }
        else if (resolve_card_points(hand[i]) == POINTS_FACE) {
            contains_face = 1;
        }
    }

    return contains_ace && contains_face;
}

/*
 * check if conditions are met for a hit
 * info - game info
 */
int game_info_can_hit(game_info *info) {
    int cards_to_draw = 
        info->deck_remaining 
        - info->hand_player_size
        - info->hand_dealer_size;

    // must have enough cards in deck and player cannot exceed max hand size
    return (cards_to_draw > 0 && info->hand_player_size < HAND_MAX_SIZE);
}

/*
 * obtain a random card from the deck not in either player's hand
 * info - game info
 */
int game_info_random_card(game_info *info) {
    int i, j;
    int already_dealt;
    int cards_to_draw[DECK_SIZE];
    int cards_to_draw_size = 0;
    int rand_card;

    // loop through all cards in deck
    for (i = 0; i < DECK_SIZE; i++) {
        // skip if deck doesnt have it
        if (info->deck[i] == 0) {
            continue;
        }
        
        // check if the player already has it 
        already_dealt = 0;
        for (j = 0; j < info->hand_player_size; j++) {
            if (i == info->hand_player[j]) {
                already_dealt = 1;
                break;
            }
        }

        // check if the dealer already has it
        if (already_dealt == 0) {
            for (j = 0; j < info->hand_dealer_size; j++) {
                if (i == info->hand_dealer[j]) {
                    already_dealt = 1;
                    break;
                }
            }
        }

        // add to potential cards to draw
        if (already_dealt == 0) {
            cards_to_draw[cards_to_draw_size] = i;
            cards_to_draw_size++;
        }
    }

    // return a random card
    rand_card = rand() % cards_to_draw_size;
    return cards_to_draw[rand_card];
}

/*
 * mods x by m
 * x - mod-ee
 * m - mod-er
 */
int mod(int x, int m) {
    return (x%m + m)%m;
}

/*
 * resolves the value of a card given its card index
 */
void resolve_card_val(char *val, int len_val, int card) {
    int val_index = card % SUIT_SIZE;
    char *vals_all[] = CARD_TO_VAL;
    
    memset(val, 0, len_val);
    strncpy(val, vals_all[val_index], strlen(vals_all[val_index]));
}

/*
 * resolves the suit of a card given its card index
 */
void resolve_card_suit(char *suit, int len_suit, int card) {
    int suit_index = card / SUIT_SIZE;
    char *suits_all[] = CARD_TO_SUIT;

    memset(suit, 0, len_suit);
    strncpy(suit, suits_all[suit_index], strlen(suits_all[suit_index]));
}

/*
 * resolves the point word of a card index
 */
int resolve_card_points(int card) {
    // reduces to int between 1-13 inclusive
    int card_val = card % SUIT_SIZE + 1;
    if (card_val >= POINTS_FACE) {
        card_val = POINTS_FACE;
    }
    return card_val;
}
