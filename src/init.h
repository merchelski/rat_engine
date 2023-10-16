#ifndef INIT_H
#define INIT_H

// file: init.h

#include "rng.h"
#include "position.h"

extern int64_t piece_keys_random[NUMBER_OF_PIECES][NUMBER_OF_BOARD_SQUARES];
extern int64_t side_to_move_key_random[2];
extern int64_t castling_rights_key_random[16];

void init_keys_random(void);
void init_all(void);

#endif
