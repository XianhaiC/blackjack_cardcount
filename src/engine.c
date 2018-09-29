#include <ncurses.h>
#include <unistd.h>

#include "draw.h"

int main(int argc, char *argv[]) {
    char *options[] = {"EAT SHIT", "DIE", "FUCK OFF"};
    int player_cards[DECK_SIZE];
    int highlight_all[DECK_SIZE];
    initscr();
    noecho();
    curs_set(FALSE);
    
    memset(player_cards, 1, DECK_SIZE * sizeof(int));
    memset(highlight_all, 0, DECK_SIZE * sizeof(int));


    highlight_all[5] = 1;
    highlight_all[6] = 1;
    highlight_all[7] = 1;

    draw_skeleton();
    draw_stats(20, 69, 2, 30);
    draw_action(options, 3, 0);
    draw_collection(player_cards, 26, highlight_all);
    draw_card(TABLE_DEALER_Y, TABLE_DEALER_X, 9);
    draw_card(TABLE_DEALER_Y, TABLE_DEALER_X + SPR_CARD_W, 51);
    draw_card(TABLE_DEALER_Y, TABLE_DEALER_X + 2 * SPR_CARD_W, -1);
    draw_card(TABLE_PLAYER_Y, TABLE_DEALER_X, 9);
    draw_card(TABLE_PLAYER_Y, TABLE_DEALER_X + SPR_CARD_W, 51);
    draw_card(TABLE_PLAYER_Y, TABLE_DEALER_X + 2 *SPR_CARD_W, -1);

    refresh();
    sleep(3);
    endwin();

    // main game loop
}



