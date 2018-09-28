#include <ncurses.h>
#include <unistd.h>

#include "draw.h"

int main(int argc, char *argv[]) {
    char *options[] = {"EAT SHIT", "DIE", "FUCK OFF"};
    int player_cards[52];
    initscr();
    noecho();
    curs_set(FALSE);
    
    player_cards[0] = 1;
    player_cards[1] = 1;
    player_cards[2] = 1;
    player_cards[3] = 1;
    player_cards[4] = 1;
    player_cards[5] = 1;
    player_cards[6] = 1;
    player_cards[7] = 1;
    player_cards[8] = 1;
    player_cards[9] = 1;
    player_cards[10] = 1;
    player_cards[11] = 1;
    player_cards[12] = 1;


    draw_skeleton();
    draw_stats(20, 69, 2, 30);
    draw_action(options, 3);
    draw_collection(player_cards);

    refresh();
    sleep(3);
    endwin();

    // main game loop
}



