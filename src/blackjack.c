#include "engine.h"

typedef struct {
    int deck[DECK_SIZE];
    int player_cards[DECK_SIZE];
    // boolean denoting if the game is over
    int game_is_over;
    // value indicates which state the round is in
    int round_state;
} game_info;

void game_info_reset(game_info *info) {
    // the deck will initially hold all the cards
    memset(info->deck, 1, DECK_SIZE * sizeof(info->deck[0]));
    // the player will initially own no cards
    memset(info->player_cards, 0, DECK_SIZE * sizeof(info->player_cards[0]));

    info->game_is_over = 0;
    info->round_state = 0;
}
int main() {
    // holds information for the games
    game_info info;

    // seed rng with time
    srand(time(0));

    // main game loop
    while (1) {
        
        // resets the game to the beggining
        init_game(&game_info);
        // game functions happen here
        process_gameplay();
        // gameover
        process_gameover();
    }
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
    draw_collection(info->player_cards);
}

void process_gameplay(game_info *info) {

    // play rounds until the player wins or loses
    while (1) {
        // play a round
        play_round(info);
        // determine if the game has ended
        evaluate_game_status();
        // break if game is over
    }
}

void play_round() {
    // betting phase
    process_betting();
    // player actions phase
    // dealer actions phase
    // winner determination
    // bet distribution phase
}

void process_betting() {
    while 
}

void evaluate_game_status() {
    // game is over if player has no cards or the deck has less than four cards
}
