#ifndef SPRITES_H
#define SPRITES_H

#define SPR_SKELETON_X 0
#define SPR_SKELETON_Y 0
#define SPR_SKELETON_W 80
#define SPR_SKELETON_H 24

#define SPR_SKELETON {\
    "################################################################################",\
    "# DEALER #                                               #                     #",\
    "##########                                               #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #######################",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "#                                                        #                     #",\
    "##########                                               #                     #",\
    "#  YOU   #                                               #                     #",\
    "################################################################################",\
    "#                                                                              #",\
    "#                                                                              #",\
    "#                                                                              #",\
    "#                                                                              #",\
    "#                                                                              #",\
    "#                                                                              #",\
    "#                                                                              #",\
    "################################################################################"\
} 

#define SPR_CARD_W 7
#define SPR_CARD_H 6

#define SPR_CARD {\
    " _____ ",\
    "|%s    |",\
    "|     |",\
    "|  %s  |",\
    "|     |",\
    "|____%s|"\
}

#define SPR_CARD_TEN {\
    " _____ ",\
    "|%s   |",\
    "|     |",\
    "|  %s  |",\
    "|     |",\
    "|___%s|"\
}

#define SPR_CARD_NULL {\
    " _____ ",\
    "|* * *|",\
    "| * * |",\
    "|* * *|",\
    "| * * |",\
    "|*_*_*|"\
}

#define SPR_ACTION_X 58
#define SPR_ACTION_Y 1
#define SPR_ACTION_W 20
#define SPR_ACTION_H 2

#define SPR_ACTION {\
    "",\
    " Choose an action"\
}

#define SPR_STATS_X 58
#define SPR_STATS_Y 9
#define SPR_STATS_W 20
#define SPR_STATS_H 5

#define SPR_STATS {\
    "",\
    " Dealer's Total: %d",\
    " Your Total:     %d",\
    " Min Bet:        %d",\
    " Deck Left:      %d"\
}

#define SPR_COLLECTION_X 1
#define SPR_COLLECTION_Y 16
#define SPR_COLLECTION_W 78
#define SPR_COLLECTION_H 2
#define SPR_COLLECTION_ROWS 4

#define SPR_COLLECTION {\
    "                                Cards you own",\
    ""\
}


#endif
