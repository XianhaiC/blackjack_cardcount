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
        //evaluate_game_status();
        // break if game is over
    }
}

void play_round(game_info *info) {
    // betting phase
    process_betting(info);
    while (1) {
        // process a player action
        process_action(info);

        if (info->last_action == SEL_STAND) {
            break;
        }
        else if (info->last_action == SEL_HIT) {
            if (info->sum_player > POINTS_MAX) {
                // player loses round
            }
        }
    }

    // dealer plays if the player has not busted
    if (info->sum_player <= POINTS_MAX) {
        process_dealer_play(info);    
    }

    // winner determination
    if (info->sum_player <= POINTS_MAX) {
        // player has won
        if (info->sum_dealer < info->sum_player) {
            process_bet_return(info);
            process_bet_winnings(info);
        }
        // tie
        else if (info->sum_dealer == info->sum_player) {
            process_bet_return(info);
        }
        // loss
        else {
            process_bet_loss(info);
        }
    }
    else {
        process_bet_loss(info);
    }
}

void process_betting(game_info *info) {
    int i;
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
            highlight_index = COLLECTION_HL_NONE
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
                    rand_card = game_info_random_card(info);
                    game_info_hand_player_add(info, rand_card);
                    info->last_action = SEL_HIT;
                }
                action_done = 1;
                break;
            case default:
                break;
        }

        draw_action(options, options_used, highlight);
        refresh();
    } 
}

void process_dealer_play(game_info *info) {
    // flip over facedown card
    while (info->sum_dealer <= DEALER_HIT_MAX 
            && info->dealer_hand_size < HAND_MAX_SIZE) {
        game_info_hand_dealer_add(info, game_info_random_card(info));
        // redraw table
        draw_table(
                info->hand_dealer,
                info->hand_dealer_len,
                info->hand_player,
                info->hand_player_len);
    }
}

void evaluate_game_status() {
    // game is over if player has no cards or the deck has less than four cards
}

