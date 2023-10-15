#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>
#include <inttypes.h>

#include "misc.h"

/* MACROS START */
#define NUMBER_OF_BOARD_SQUARES (64)
#define NUMBER_OF_PIECES (13)
#define MAX_NUMBER_OF_MOVES (5949) // max theoretical is 5949
#define NUM_RANKS (8)
#define NUM_FILES (8)

#define FILE_RANK_TO_SQUARE(file, rank) (((NUM_RANKS) * (rank)) + (file))
/* MACROS END */

/* FUNCTIONS START */
/* FUNCTIONS END */

enum enum_piece
{	
	EMPTY, 
	WHITE_PAWN, 
	WHITE_KNIGHT, 
	WHITE_BISHOP,
	WHITE_ROOK, 
	WHITE_QUEEN,
	WHITE_KING,
	BLACK_PAWN,
	BLACK_KNIGHT,
	BLACK_BISHOP,
	BLACK_ROOK,
	BLACK_QUEEN,
	BLACK_KING
};

enum enum_file
{
	FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H
};

enum enum_rank
{
	RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

enum enum_color
{
	WHITE, BLACK, BOTH
};
	
enum enum_square
{
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

enum enum_castling
{
	WHITE_KINGSIDE_CASTLING_RIGHTS_MASK = 1,
	WHITE_QUEENSIDE_CASTLING_RIGHTS_MASK = 2,
	BLACK_KINGSIDE_CASTLING_RIGHTS_MASK = 4,
	BLACK_QUEENSIDE_CASTLING_RIGHTS_MASK = 8
};

struct UNDO
{
	uint64_t position_key;
	uint8_t move;
	uint8_t castling_rights;
	uint8_t en_passant_square;
	uint8_t fifty_move_rule;
};

// _bb stands for bitboard
// _mb stands for mailbox
struct POSITION
{	
	struct UNDO move_history[MAX_NUMBER_OF_MOVES];
	
	uint64_t position_key;
	
	uint64_t pawns_bb;
	uint64_t knights_bb;
	uint64_t bishops_bb;
	uint64_t rooks_bb;
	uint64_t queens_bb;
	uint64_t kings_bb;
	uint64_t white_pieces_bb;
	uint64_t black_pieces_bb;
	
	uint16_t ply;
	uint16_t history_ply;
	
	uint8_t piece_counts[NUMBER_OF_PIECES];
	
	uint8_t side_to_move;
	uint8_t en_passant_square;
	uint8_t fifty_move_rule;
	uint8_t castling_rights;
	
	uint8_t board_mb[NUMBER_OF_BOARD_SQUARES];
};

#endif
