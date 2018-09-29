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
                info->deck[rand_num] = 0;
                info->player_cards[rand_num] = 1;
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
    // player actions phase
    // dealer actions phase
    // winner determination
    // bet distribution phase
}

void process_betting(game_info *info) {
    int i;
    int sel;
    int highlight_x;
    int highlight_y;
    int highlight_index;
    int highlight_num = 0;

    int betting_done = 0;

    // reset bet selections
    memset(info->bet_sel, 0, DECK_SIZE * sizeof(info->bet_sel[0]));

    while (info->player_cards[i] != 1) {
        i++;
    }

    highlight_index = i;
    highlight_x = i % SUIT_SIZE;
    highlight_y = i / SUIT_SIZE;

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

                // set the selected card
                if (info->bet_sel[highlight_index] == 0) {
                    info->bet_sel[highlight_index] = 1;
                    highlight_num++;
                }
                else {
                    info->bet_sel[highlight_index] = 0;
                    highlight_num--;
                }

                break;
            case KIN_CONFIRM:
                if (highlight_num < info->bet_min) {
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
        highlight_index = highlight_y * SUIT_SIZE + highlight_x;
        draw_collection(info->player_cards, highlight_index, info->bet_sel);
        refresh();
    }
}

void evaluate_game_status() {
    // game is over if player has no cards or the deck has less than four cards
}

void game_info_reset(game_info *info) {
    // the deck will initially hold all the cards
    memset(info->deck, 1, DECK_SIZE * sizeof(info->deck[0]));
    // the player will initially own no cards
    memset(info->player_cards, 0, DECK_SIZE * sizeof(info->player_cards[0]));
    // no cards are selected for betting
    memset(info->bet_sel, 0, DECK_SIZE * sizeof(info->bet_sel[0]));

    info->game_is_over = 0;
    info->round_state = 0;
    info->bet_min = BET_MIN_INITIAL;
}
