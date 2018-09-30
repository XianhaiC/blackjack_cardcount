#ifndef SPRITES_H
#define SPRITES_H

#define SPR_SKELETON_X 0
#define SPR_SKELETON_Y 0
#define SPR_SKELETON_W 80
#define SPR_SKELETON_H 24

#define SPR_SKELETON {\
    "+---------+----------------------------------------------+---------------------+",\
    "| DEALER  |                                              |                     |",\
    "+---------+                                              |                     |",\
    "|    ^    |                                              |                     |",\
    "|    W    |                                              |                     |",\
    "| < A D > |                                              |                     |",\
    "|    S    |                                              |                     |",\
    "|    v    |                                              |                     |",\
    "|         |                                              +---------------------+",\
    "| H select|                                              |                     |",\
    "| J done  |                                              |                     |",\
    "|         |                                              |                     |",\
    "|         |                                              |                     |",\
    "+---------+                                              |                     |",\
    "|  YOU    |                                              |                     |",\
    "+---------+----------------------------------------------+---------------------+",\
    "|                                                                              |",\
    "|                                                                              |",\
    "|                                                                              |",\
    "|                                                                              |",\
    "|                                                                              |",\
    "|                                                                              |",\
    "|                                                                              |",\
    "+------------------------------------------------------------------------------+"\
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
#define SPR_ACTION_H 3

#define SPR_ACTION {\
    "",\
    " Choose an action",\
    ""\
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

#define SPR_ACTION_CLR_H 7
#define SPR_ACTION_CLR {\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    "\
}

#define SPR_STATS_CLR_H 6
#define SPR_STATS_CLR {\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    ",\
    "                    "\
}

#define SPR_COLLECTION_CLR_H 7
#define SPR_COLLECTION_CLR {\
    "                                                                              ",\
    "                                                                              ",\
    "                                                                              ",\
    "                                                                              ",\
    "                                                                              ",\
    "                                                                              ",\
    "                                                                              "\
}

#define SPR_TABLE_CLR_H 13
#define SPR_TABLE_CLR {\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          ",\
    "                                          "\
}

#define SPR_NOTI_BETS_X 15
#define SPR_NOTI_BETS_Y 3
#define SPR_NOTI_BETS_H 10
#define SPR_NOTI_BETS {\
    "+------------------------------------+",\
    "|          PLACE YOUR BET            |",\
    "|          ~~~~~~~~~~~~~~            |",\
    "|     Hover over cards with 'WASD'   |",\
    "|     Select those to bet with 'H'   |",\
    "|           Confirm with 'J'         |",\
    "|                                    |",\
    "|       Minimum bet: %d cards         |",\
    "|                                    |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_ROUND_LOST_X 15
#define SPR_NOTI_ROUND_LOST_Y 6
#define SPR_NOTI_ROUND_LOST_H 4
#define SPR_NOTI_ROUND_LOST {\
    "+------------------------------------+",\
    "|        You LOST the round!         |",\
    "|     Press any key to continue      |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_ROUND_WON_X 15
#define SPR_NOTI_ROUND_WON_Y 6
#define SPR_NOTI_ROUND_WON_H 4
#define SPR_NOTI_ROUND_WON {\
    "+------------------------------------+",\
    "|        You WON the round!!!        |",\
    "|     Press any key to continue      |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_ROUND_TIE_X 15
#define SPR_NOTI_ROUND_TIE_Y 6
#define SPR_NOTI_ROUND_TIE_H 4
#define SPR_NOTI_ROUND_TIE {\
    "+------------------------------------+",\
    "|                PUSH                |",\
    "|  It's a tie. Your bet is returned  |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_GAME_LOST_X 15
#define SPR_NOTI_GAME_LOST_Y 6
#define SPR_NOTI_GAME_LOST_H 4
#define SPR_NOTI_GAME_LOST {\
    "+------------------------------------+",\
    "|    YOU'VE LOST ALL YOUR CARDS!     |",\
    "|  ^C to exit or any key to replay   |",\
    "+------------------------------------+",\
}

#define SPR_NOTI_GAME_WON_X 15
#define SPR_NOTI_GAME_WON_Y 6
#define SPR_NOTI_GAME_WON_H 4
#define SPR_NOTI_GAME_WON {\
    "+------------------------------------+",\
    "|       YOU'VE WON THE DECK!!!       |",\
    "|  ^C to exit or any key to replay   |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_TURN_PLAYER_X 15
#define SPR_NOTI_TURN_PLAYER_Y 6
#define SPR_NOTI_TURN_PLAYER_H 4
#define SPR_NOTI_TURN_PLAYER {\
    "+------------------------------------+",\
    "|          It's your turn!           |",\
    "|    Get ready to choose an action   |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_TURN_DEALER_X 15
#define SPR_NOTI_TURN_DEALER_Y 6
#define SPR_NOTI_TURN_DEALER_H 4
#define SPR_NOTI_TURN_DEALER {\
    "+------------------------------------+",\
    "|       It's the Dealer's turn!      |",\
    "|   Sit tight and watch his draws    |",\
    "+------------------------------------+"\
}

#define SPR_NOTI_BJ_X 15
#define SPR_NOTI_BJ_Y 6
#define SPR_NOTI_BJ_H 4
#define SPR_NOTI_BJ {\
    "+------------------------------------+",\
    "|          BLACK JACK!!!!!!          |",\
    "|         The payout is 3:2          |",\
    "+------------------------------------+"\
}

#endif
