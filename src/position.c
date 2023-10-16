// file: position.c

#include "position.h"
#include "string.h"

void reset_position(struct POSITION* pos)
{
	memset(pos->move_history, 0, sizeof(struct UNDO) * MAX_NUMBER_OF_MOVES);
	
	pos->position_key = 0ULL;
	
	pos->pawns_bb = 0ULL;
	pos->knights_bb = 0ULL;
	pos->bishops_bb = 0ULL;
	pos->rooks_bb = 0ULL;
	pos->queens_bb = 0ULL;
	pos->kings_bb = 0ULL;
	pos->white_pieces_bb = 0ULL;
	pos->black_pieces_bb = 0ULL;
	
	pos->ply = 0;
	pos->history_ply = 0;
	
	for(int piece = EMPTY; piece <= BLACK_KING; piece++)
	{
		pos->piece_counts[piece] = 0;
	}
	
	pos->side_to_move = BOTH;
	pos->en_passant_square = NO_SQ;
	pos->fifty_move_rule = 0;
	pos->castling_rights = 0;
	
	for(int sq = 0; sq < NUMBER_OF_BOARD_SQUARES; sq++)
	{
		pos->board_mb[sq] = EMPTY;
	}
}
