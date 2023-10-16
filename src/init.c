// file: init.c

#include "init.h"
#include "rng.h"
#include "position.h"

int64_t piece_keys_random[NUMBER_OF_PIECES][NUMBER_OF_BOARD_SQUARES];
int64_t side_to_move_key_random[2];
int64_t castling_rights_key_random[16];

void init_keys_random(void)
{
	// set keys each side to move
	side_to_move_key_random[WHITE] = generate_random_u64();
	side_to_move_key_random[BLACK] = generate_random_u64();
	
	// set keys for pieces
	for(int i = 0; i < NUMBER_OF_PIECES; i++)
	{
		for(int j = 0; j < NUMBER_OF_BOARD_SQUARES; j++)
		{
			piece_keys_random[i][j] = generate_random_u64();
		}
	}	
	
	// set keys for each permutation of castling rights
	for(int i = 0; i < 16; i++)
	{
		castling_rights_key_random[i] = generate_random_u64();
	}
}

void init_all(void)
{
	init_keys_random();
}
