#include "blackjack.h"

int main() {
    // holds information for the games
    game_info info;

    initscr();
    noecho();
    curs_set(FALSE);

    // seed rng with time
    srand(time(0));

    // main game loop
    while (1) {
        
        // resets the game to the beggining
        init_game(&info);
        // game functions happen here
        process_gameplay(&info);
        // gameover
        //process_gameover();
    }
    endwin();
}

void init_game(game_info *info) {
    int i;
    int rand_num;

    // reset to default game info
    game_info_reset(info);

    // give the player the random starting cards to bet with
    for (i = 0; i < PLAYER_START_CARDS; i++) {
        // loop until non repeating num is obtained
        while (1) {
            rand_num = rand() % DECK_SIZE;   
            // if the deck's value at the random index is 0, then the card is
            // already possessed by the player
            if (info->deck[rand_num] == 0) {
                continue;
            }
            else {
                game_info_give_player_card(info, rand_num);
                break;
            }
        }
    }

    // draw the initial board
    draw_skeleton();
    draw_collection(info->player_cards, COLLECTION_HL_NONE, info->bet_sel);
}

void process_gameplay(game_info *info) {

    // play rounds until the player wins or loses
    while (1) {
        // play a round
        play_round(info);
        // determine if the game has ended
        if (info->game_is_over) {
            break;
        }
    }
}

void play_round(game_info *info) {
    int i;
    int rand_card;
    int hand_dealer_facedown[DECK_SIZE];
    int hand_dealer_facedown_size = 0;
    int hand_dealer_facedown_val = 0;


    memset(hand_dealer_facedown, 0, 
            DECK_SIZE * sizeof(hand_dealer_facedown[0]));

    memset(info->hand_dealer, 0, DECK_SIZE * sizeof(info->hand_dealer[0]));
    memset(info->hand_player, 0, DECK_SIZE * sizeof(info->hand_player[0]));
    info->hand_dealer_size = 0;
    info->hand_player_size = 0;
    info->sum_dealer = 0;
    info->sum_player = 0;
    info->last_action = -1;

    // clear the board
    draw_table(
            info->hand_dealer,
            info->hand_dealer_size,
            info->hand_player,
            info->hand_player_size);
    refresh();
    
    // betting phase
    process_betting(info);

    usleep(DELAY_CARD_REVEAL);
    
    for (i = 0; i < ROUND_START_CARD_AMT; i++) {
        rand_card = game_info_random_card(info);
        if (i == ROUND_START_CARD_AMT - 1) {
            hand_dealer_facedown[hand_dealer_facedown_size] = CARD_NULL;
        }
        else {
            hand_dealer_facedown[hand_dealer_facedown_size] = rand_card;
        }
        hand_dealer_facedown_size++;
        
        game_info_hand_dealer_add(info, rand_card);
        game_info_hand_player_add(info, game_info_random_card(info));
    }

    hand_dealer_facedown_val = hand_dealer_facedown[0] % SUIT_SIZE == 0 ?
        POINTS_ACE_HARD :
        resolve_card_points(hand_dealer_facedown[0]);
    
    // draw initial delt cards with one of the dealer's facedown
    draw_table(
            hand_dealer_facedown,
            hand_dealer_facedown_size,
            info->hand_player,
            info->hand_player_size);
    
    // draw initial stats with the sum of only the dealer's faceup card
    draw_stats(
            hand_dealer_facedown_val, 
            info->sum_player,
            info->bet_min, info->deck_remaining);
    refresh();

    if (!game_info_hand_bj(info->hand_player, info->hand_player_size)) {
        // give players initial cards
        while (1) {

            // process a player action
            process_action(info);

            if (info->last_action == SEL_STAND) {
                break;
            }
            else if (info->last_action == SEL_HIT) {
                rand_card = game_info_random_card(info);
                game_info_hand_player_add(info, rand_card);

            }

            draw_table(
                    hand_dealer_facedown,
                    hand_dealer_facedown_size,
                    info->hand_player,
                    info->hand_player_size);

            draw_stats(
                    hand_dealer_facedown_val, 
                    info->sum_player,
                    info->bet_min, info->deck_remaining);

            if (info->sum_player > POINTS_MAX) {
                // player loses round
                break;
            }
        }

        // dealer plays if the player has not busted
        if (info->sum_player <= POINTS_MAX) {
            process_dealer_play(info);    
            draw_table(
                    info->hand_dealer,
                    info->hand_dealer_size,
                    info->hand_player,
                    info->hand_player_size);
        }

        // winner determination
        if (info->sum_player <= POINTS_MAX) {
            if (info->sum_dealer <= POINTS_MAX) {
                // player has won
                if (info->sum_dealer < info->sum_player) {
                    process_bet_winnings(info, 0);
                }
                // loss
                else if (info->sum_dealer > info->sum_player) {
                    process_bet_loss(info);
                }
                // push
                else {
                    //notice_tie();
                }
            }
            else {
                process_bet_winnings(info, 0);
            }
        }
        else {
            process_bet_loss(info);
        }
    }
    else {
        process_bet_winnings(info, 1);
    }

    draw_collection(info->player_cards, COLLECTION_HL_NONE, info->bet_sel);
    draw_stats(
            info->sum_dealer, 
            info->sum_player,
            info->bet_min, info->deck_remaining);
    refresh();

    getch();
}

void process_bet_loss(game_info *info) {
    int i;
    
    // if the player loses all his betting cards then end the game
    if (info->player_cards_remaining - info->bet_amt <= 0) {
        info->game_is_over = 1;
        return;
    }

    for (i = 0; i < DECK_SIZE; i++) {
        if (info->bet_sel[i] == 1) {
            game_info_give_deck_card(info, i);
        }
    }
}

void process_bet_winnings(game_info *info, int bj) {
    int i;
    int rand_card;
    int bet_amt;

    // multiply winnings by blackjack payout if bj set
    if (bj) {
        bet_amt = (int) (info->bet_amt * BJ_PAYOUT);
    }
    else {
        bet_amt = info->bet_amt;
    }

    // the game is won
    if (info->deck_remaining - bet_amt < DECK_REMAINING_MIN) {
        info->game_is_over = 1;
        return;
    }

    // otherwise give the player their winnings
    for (i = 0; i < bet_amt; i++) {
        rand_card = game_info_random_card(info);
        game_info_give_player_card(info, rand_card);        
    }
}

void process_betting(game_info *info) {
    int i = 0;
    int sel;
    int highlight_x;
    int highlight_y;
    int highlight_index;

    int betting_done = 0;

    // reset bet info
    memset(info->bet_sel, 0, DECK_SIZE * sizeof(info->bet_sel[0]));
    info->bet_amt = 0;

    while (info->player_cards[i] != 1) {
        i++;
    }

    highlight_index = i;
    highlight_x = i % SUIT_SIZE;
    highlight_y = i / SUIT_SIZE;

    draw_collection(info->player_cards, highlight_index, info->bet_sel);
    refresh();

    while (betting_done == 0) {
        sel = getch();
        switch (sel) {
            case KIN_UP:
                // decrease value since y increases downwards
                highlight_y--;
                highlight_y = mod(highlight_y, DECK_SUITS);
                break;
            case KIN_DOWN:
                // increase value since y increases downwards
                highlight_y++;
                highlight_y = mod(highlight_y, DECK_SUITS);
                break;
            case KIN_LEFT:
                highlight_x--;
                highlight_x = mod(highlight_x, SUIT_SIZE);
                break;
            case KIN_RIGHT:
                highlight_x++;
                highlight_x = mod(highlight_x, SUIT_SIZE);
                break;
            case KIN_SELECT:
                // do nothing if the card selected is not possesed by the 
                // player
                if (info->player_cards[highlight_index] == 0) {
                    break;
                }

                // toggle the selection of the highlighted card
                game_info_bet_sel_toggle(info, highlight_index);
                break;
            case KIN_CONFIRM:
                if (info->bet_amt < info->bet_min) {
                    //notice_min_bet_required();
                    break;
                }
                else {
                    betting_done = 1;
                }
                break;
            default:
                break;
        }
        
        // calculate the new index for the cursor
        if (betting_done == 0) {
            highlight_index = highlight_y * SUIT_SIZE + highlight_x;
        }
        else {
            // hide the cursor when done
            highlight_index = COLLECTION_HL_NONE;
        }

        draw_collection(info->player_cards, highlight_index, info->bet_sel);
        refresh();
    }
}

void process_action(game_info *info) {
    int sel;
    int highlight = 0;
    char *options[ACTION_OPTION_NUM];
    int options_used = 0;
    int rand_card;
    int action_done = 0;

    options[options_used] = ACTION_STAND;
    options_used++;

    // add hit option only if there are still hards to be drawn and there
    // is room in the hand
    if (game_info_can_hit(info)) {
        options[options_used] = ACTION_HIT;
        options_used++;
    }

    draw_action(options, options_used, highlight);
    refresh();

    while (action_done == 0) {
        sel = getch();

        switch (sel) {
            case KIN_UP:
                // decrease value since y increases downwards
                highlight--;
                highlight = mod(highlight, options_used);
                break;
            case KIN_DOWN:
                // increase value since y increases downwards
                highlight++;
                highlight = mod(highlight, options_used);
                break;
            case KIN_SELECT:
            case KIN_CONFIRM:
                if (highlight == SEL_STAND) {
                    info->last_action = SEL_STAND;
                }
                else if (highlight == SEL_HIT) {
                    info->last_action = SEL_HIT;
                }
                action_done = 1;
                break;
            default:
                break;
        }

        draw_action(options, options_used, highlight);
        refresh();
    } 
}

void process_dealer_play(game_info *info) {
    usleep(DELAY_DEALER_PLAY);
    // flip over facedown card
    draw_table(
            info->hand_dealer,
            info->hand_dealer_size,
            info->hand_player,
            info->hand_player_size);
    
    draw_stats(
            info->sum_dealer, 
            info->sum_player,
            info->bet_min, info->deck_remaining);

    refresh();
    usleep(DELAY_DEALER_PLAY);

    while (info->sum_dealer <= DEALER_HIT_MAX 
            && info->hand_dealer_size < HAND_MAX_SIZE) {
        game_info_hand_dealer_add(info, game_info_random_card(info));

        // redraw table
        draw_table(
                info->hand_dealer,
                info->hand_dealer_size,
                info->hand_player,
                info->hand_player_size);

        draw_stats(
                info->sum_dealer, 
                info->sum_player,
                info->bet_min, info->deck_remaining);

        refresh();
        usleep(DELAY_DEALER_PLAY);
    }
}
