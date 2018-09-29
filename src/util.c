#include "util.h"

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

    memset(info->hand_dealer, 0, DECK_SIZE * sizeof(info->hand_dealer[0]));
    info->hand_dealer_size = 0;

    memset(info->hand_player, 0, DECK_SIZE * sizeof(info->hand_player[0]));
    info->hand_player_size = 0;

    info->bet_min = BET_MIN_INITIAL;
    info->game_is_over = 0;
    info->last_action = SEL_NONE;
}

void game_info_give_player_card(game_info *info, int card) {
    info->deck[card] = 0;
    (info->deck_remaining)--;
    info->player_cards[card] = 1;
    (info->player_cards_remaining)++;
}

void game_info_give_deck_card(game_info *info, int card) {
    info->deck[card] = 1;
    (info->deck_remaining)++;
    info->player_cards[card] = 0;
    (info->player_cards_remaining)--;
}

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

void game_info_hand_player_add(game_info *info, int card) {
    int points;
    if (card % SUIT_SIZE == CARD_ACE) {
        points = info->sum_player + POINTS_ACE_HARD > POINTS_MAX ? 
            POINTS_ACE_SOFT : POINTS_ACE_HARD;
    }
    else {
        points = resolve_points(card);
    }
    
    // update player info
    info->sum_player += points;
    info->hand_player[info->hand_player_size] = card;
    (info->hand_player_size)++;
}

void game_info_hand_dealer_add(game_info *info, int card) {
    int points;
    if (card % SUIT_SIZE == CARD_ACE) {
        points = info->sum_dealer + POINTS_ACE_HARD > POINTS_MAX ? 
            POINTS_ACE_SOFT : POINTS_ACE_HARD;
    }
    else {
        points = resolve_points(card);
    }
    
    // update player info
    info->sum_dealer += points;
    info->hand_dealer[info->hand_dealer_size] = card;
    (info->hand_dealer_size)++;
}

// checks if the player can still hit a card
void game_info_can_hit(game_info *info) {
    int cards_to_draw = 
        info->deck_remaining 
        - info->hand_player_size
        - info->hand_dealer_size;

    return (cards_to_draw > 0 && info->hand_player_size < HAND_MAX_SIZE);
}

int game_info_random_card(game_info *info) {
    int i, j;
    int already_dealt;
    int cards_to_draw[DECK_SIZE];
    int cards_to_draw_size = 0;
    int rand_card;

    for (i = 0; i < DECK_SIZE; i++) {
        if (info->deck[i] == 0) {
            continue;
        }
        
        already_dealt = 0;
        for (j = 0; j < info->hand_player_size; j++) {
            if (i == info->hand_player[j]) {
                already_dealt = 1;
                break;
            }
        }

        if (already_dealt == 0) {
            for (j = 0; j < info->hand_dealer_size; j++) {
                if (i == info->hand_dealer[j]) {
                    already_dealt = 1;
                    break;
                }
            }
        }

        if (already_dealt == 0) {
            cards_to_draw[cards_to_draw_size] = i;
            cards_to_draw_size++;
        }
    }

    rand_card = rand() % cards_to_draw_size;
    return cards_to_draw[rand_card];
}

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

// the ace returns a value of 1, handle that seperately
int resolve_card_points(int card) {
    return (card % SUIT_SIZE / POINTS_TEN_INDEX) * POINTS_TEN;
}
