/*
 * This file contains functions related to drawing sprites and communicating
 * with the ncurses library
 */

void draw_skeleton() {

    char **skeleton = SPR_SKELETON;
    
    draw_sprite(
            SPR_SKELETON_Y,
            SPR_SKELETON_X,
            skeleton,
            SPR_SKELETON_H);
}

void draw_card(int y, int x, int card) {
     
}

void draw_sprite(int y, int x, char **sprite, int len_sprite) {
    int i;
    for (i = 0; sprite[i] != NULL; i++) {
        mvprintw(y + i, x, sprite[i]);
    }
}
