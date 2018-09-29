#ifndef UTIL_H
#define UTIL_H

#include <string.h>

#include "macros.h"


int mod(int x, int m);
void resolve_card_val(char *val, int len_val, int card);
void resolve_card_suit(char *suit, int len_suit, int card);

#endif
