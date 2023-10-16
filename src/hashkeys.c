// file: hashkeys.c

#include <stdint.h>
#include "position.h"
#include "init.h"

uint64_t generate_position_key(const struct POSITION* pos)
{
	int piece;
	uint64_t final_key = 0;
	
	// hash all pieces
	for(int sq = 0; sq < NUMBER_OF_BOARD_SQUARES; sq++)
	{
		piece = pos->board_mb[sq];
		if(piece != EMPTY)
		{
			ASSERT(piece >= WHITE_PAWN && piece <= BLACK_KING);
			final_key ^= piece_keys_random[piece][sq];
		}
	}
	
	// hash side to move
	final_key ^= side_to_move_key_random[pos->side_to_move];
	
	// hash the en passant square
	if(pos->en_passant_square != NO_SQ)
	{
		ASSERT(pos->en_passant_square >= A1 && pos->en_passant_square <= H8);
		final_key ^= piece_keys_random[EMPTY][pos->en_passant_square];
	}
	
	ASSERT(pos->castling_rights >= 0 && pos->castling_rights <= 15);
	
	// hash castling rights
	final_key ^= castling_rights_key_random[pos->castling_rights];
	
	return final_key;
	
}
